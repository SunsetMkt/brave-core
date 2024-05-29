/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/webui/brave_rewards/rewards_page_top_ui.h"

#include <utility>

#include "brave/browser/brave_rewards/rewards_service_factory.h"
#include "brave/browser/ui/webui/brave_rewards/rewards_page_data_source.h"
#include "brave/browser/ui/webui/brave_rewards/rewards_page_handler.h"
#include "chrome/browser/profiles/profile.h"

namespace brave_rewards {

namespace {

class RewardsPageBubbleDelegate : public RewardsPageHandler::BubbleDelegate {
 public:
  RewardsPageBubbleDelegate(
      base::WeakPtr<TopChromeWebUIController::Embedder> embedder)
      : embedder_(embedder) {}

  void ShowUI() override {
    if (embedder_) {
      embedder_->ShowUI();
    }
  }

 private:
  base::WeakPtr<TopChromeWebUIController::Embedder> embedder_;
};

}  // namespace

RewardsPageTopUI::RewardsPageTopUI(content::WebUI* web_ui,
                                   const std::string& host)
    : TopChromeWebUIController(web_ui) {
  CreateAndAddRewardsPageDataSource(*web_ui, host);
}

RewardsPageTopUI::~RewardsPageTopUI() = default;

void RewardsPageTopUI::BindInterface(
    mojo::PendingReceiver<RewardsPageHandlerFactory> receiver) {
  factory_receiver_.reset();
  factory_receiver_.Bind(std::move(receiver));
}

void RewardsPageTopUI::CreatePageHandler(
    mojo::PendingRemote<mojom::RewardsPage> page,
    mojo::PendingReceiver<mojom::RewardsPageHandler> handler) {
  DCHECK(page);

  handler_ = std::make_unique<RewardsPageHandler>(
      std::move(page), std::move(handler),
      std::make_unique<RewardsPageBubbleDelegate>(embedder()),
      RewardsServiceFactory::GetForProfile(Profile::FromWebUI(web_ui())));
}

WEB_UI_CONTROLLER_TYPE_IMPL(RewardsPageTopUI)

}  // namespace brave_rewards
