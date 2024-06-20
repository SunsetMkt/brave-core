// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/ai_chat/core/browser/engine/engine_consumer_oai.h"

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "base/containers/fixed_flat_set.h"
#include "base/containers/flat_set.h"
#include "base/functional/bind.h"
#include "base/i18n/time_formatting.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/pattern.h"
#include "base/strings/strcat.h"
#include "base/strings/string_split.h"
#include "base/strings/string_tokenizer.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/types/expected.h"
#include "brave/components/ai_chat/core/browser/constants.h"
#include "brave/components/ai_chat/core/browser/engine/engine_consumer.h"
#include "brave/components/ai_chat/core/browser/engine/remote_completion_client.h"
#include "brave/components/ai_chat/core/common/features.h"
#include "brave/components/ai_chat/core/common/mojom/ai_chat.mojom-forward.h"
#include "brave/components/ai_chat/core/common/mojom/ai_chat.mojom.h"
#include "components/grit/brave_components_strings.h"
#include "net/http/http_status_code.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"
#include "ui/base/l10n/l10n_util.h"

namespace {
constexpr char kQuestionPrompt[] =
    "Propose up to 3 very short questions that a reader may ask about the "
    "content. Wrap each in <question> tags.";
}  // namespace

namespace ai_chat {

namespace {

using mojom::CharacterType;
using mojom::ConversationTurn;

base::Value::List BuildMessages(
    const std::string& human_input,
    const std::string& page_content,
    const std::optional<std::string>& selected_text,
    const bool& is_video,
    const EngineConsumer::ConversationHistory& conversation_history) {
  const std::string prompt_segment_article =
      page_content.empty()
          ? ""
          : base::StrCat(
                {base::ReplaceStringPlaceholders(
                     l10n_util::GetStringUTF8(
                         is_video ? IDS_AI_CHAT_LLAMA2_VIDEO_PROMPT_SEGMENT
                                  : IDS_AI_CHAT_LLAMA2_ARTICLE_PROMPT_SEGMENT),
                     {page_content}, nullptr),
                 "\n\n"});

  std::string date_and_time_string =
      base::UTF16ToUTF8(TimeFormatFriendlyDateAndTime(base::Time::Now()));
  std::string system_message = base::StrCat(
      {prompt_segment_article,
       base::ReplaceStringPlaceholders(
           l10n_util::GetStringUTF8(IDS_AI_CHAT_LLAMA2_SYSTEM_MESSAGE_GENERIC),
           {date_and_time_string}, nullptr)});

  // build
  base::Value::List messages;

  // append system message
  {
    base::Value::Dict message;
    message.Set("role", "system");
    message.Set("content", system_message);
    messages.Append(std::move(message));
  }

  for (const mojom::ConversationTurnPtr& turn : conversation_history) {
    base::Value::Dict message;
    message.Set("role", turn->character_type == CharacterType::HUMAN
                            ? "user"
                            : "assistant");
    message.Set("content", turn->text);
    messages.Append(std::move(message));
  }

  return messages;
}

}  // namespace

EngineConsumerOAIRemote::EngineConsumerOAIRemote(
    const mojom::CustomModelOptions& model_options,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory) {
  model_options_ = model_options;
  max_page_content_length_ = kCustomModelMaxPageContentLength;
  api_ = std::make_unique<OAIAPIClient>(url_loader_factory);
}

EngineConsumerOAIRemote::~EngineConsumerOAIRemote() = default;

void EngineConsumerOAIRemote::ClearAllQueries() {
  api_->ClearAllQueries();
}

bool EngineConsumerOAIRemote::SupportsDeltaTextResponses() const {
  return true;
}

void EngineConsumerOAIRemote::GenerateRewriteSuggestion(
    std::string text,
    const std::string& question,
    GenerationDataCallback received_callback,
    GenerationCompletedCallback completed_callback) {
  base::Value::List messages;

  {
    base::Value::Dict message;
    message.Set("role", "user");
    message.Set("content", base::StrCat({text, question}));
    messages.Append(std::move(message));
  }

  {
    base::Value::Dict message;
    message.Set("role", "assistant");
    message.Set("content",
                "This is an excerpt user selected to be rewritten. Put your "
                "rewritten of the excerpt in <response></response> tags.");
    messages.Append(std::move(message));
  }

  api_->PerformRequest(model_options_, std::move(messages),
                       std::move(received_callback),
                       std::move(completed_callback));
}

void EngineConsumerOAIRemote::GenerateQuestionSuggestions(
    const bool& is_video,
    const std::string& page_content,
    SuggestedQuestionsCallback callback) {
  const std::string& truncated_page_content =
      page_content.substr(0, max_page_content_length_);
  std::string content_segment = base::ReplaceStringPlaceholders(
      l10n_util::GetStringUTF8(is_video
                                   ? IDS_AI_CHAT_CLAUDE_VIDEO_PROMPT_SEGMENT
                                   : IDS_AI_CHAT_CLAUDE_ARTICLE_PROMPT_SEGMENT),
      {truncated_page_content}, nullptr);

  base::Value::List messages;

  {
    base::Value::Dict message;
    message.Set("role", "user");
    message.Set("content", base::StrCat({content_segment, kQuestionPrompt}));
    messages.Append(std::move(message));
  }

  {
    base::Value::Dict message;
    message.Set("role", "assistant");
    message.Set("content",
                "Here are three questions the user may ask about the content "
                "in <question> tags:\n");
    messages.Append(std::move(message));
  }

  api_->PerformRequest(
      model_options_, std::move(messages), base::NullCallback(),
      base::BindOnce(
          &EngineConsumerOAIRemote::OnGenerateQuestionSuggestionsResponse,
          weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
}

void EngineConsumerOAIRemote::OnGenerateQuestionSuggestionsResponse(
    SuggestedQuestionsCallback callback,
    GenerationResult result) {
  if (!result.has_value() || result->empty()) {
    // Query resulted in error
    LOG(ERROR) << "Error getting question suggestions.";
    std::move(callback).Run(base::unexpected(std::move(result.error())));
    return;
  }

  constexpr char kStartTag[] = "<question>";
  constexpr char kEndTag[] = "</question>";

  base::StringTokenizer tokenizer(*result, "\n");
  std::vector<std::string> questions;

  while (tokenizer.GetNext()) {
    std::string token = tokenizer.token();

    if (!(base::StartsWith(token, kStartTag) &&
          base::EndsWith(token, kEndTag))) {
      return;
    }

    auto count = (token.length() - strlen(kStartTag) - strlen(kEndTag)) - 1;
    auto question = token.substr(strlen(kStartTag), count);
    questions.push_back(question);
  }

  std::move(callback).Run(std::move(questions));
}

void EngineConsumerOAIRemote::GenerateAssistantResponse(
    const bool& is_video,
    const std::string& page_content,
    const ConversationHistory& conversation_history,
    const std::string& human_input,
    GenerationDataCallback data_received_callback,
    GenerationCompletedCallback completed_callback) {
  if (conversation_history.empty()) {
    std::move(completed_callback).Run(base::unexpected(mojom::APIError::None));
    return;
  }

  const mojom::ConversationTurnPtr& last_turn = conversation_history.back();
  if (last_turn->character_type != CharacterType::HUMAN) {
    std::move(completed_callback).Run(base::unexpected(mojom::APIError::None));
    return;
  }

  std::optional<std::string> selected_text = std::nullopt;
  if (last_turn->selected_text.has_value()) {
    selected_text =
        last_turn->selected_text->substr(0, max_page_content_length_);
  }
  const std::string& truncated_page_content = page_content.substr(
      0, selected_text ? max_page_content_length_ - selected_text->size()
                       : max_page_content_length_);
  base::Value::List messages =
      BuildMessages(human_input, truncated_page_content, selected_text,
                    is_video, conversation_history);
  api_->PerformRequest(model_options_, std::move(messages),
                       std::move(data_received_callback),
                       std::move(completed_callback));
}

void EngineConsumerOAIRemote::SanitizeInput(std::string& input) {}

}  // namespace ai_chat
