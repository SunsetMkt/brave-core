/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/core/execution_context/navigator_base.h"

#include "third_party/blink/public/platform/web_content_settings_client.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/loader/frame_loader.h"

#define userAgent userAgent_ChromiumImpl
#include "src/third_party/blink/renderer/core/execution_context/navigator_base.cc"
#undef userAgent

namespace blink {

String NavigatorBase::userAgent() const {
  {
    ::brave_page_graph::PageGraph* page_graph =
        ::brave_page_graph::PageGraph::GetFromExecutionContext(
            *(GetExecutionContext()));
    if (page_graph != nullptr) {
      String result = DomWindow()->GetFrame()->Loader().UserAgent();
      page_graph->RegisterWebAPICall("NavigatorID.userAgent",
                                     std::vector<const String>());
      page_graph->RegisterWebAPIResult("NavigatorID.userAgent", result);
    }
  }
  if (blink::WebContentSettingsClient* settings =
          brave::GetContentSettingsClientFor(GetExecutionContext())) {
    if (!settings->AllowFingerprinting()) {
      return brave::BraveSessionCache::From(*(GetExecutionContext()))
          .FarbledUserAgent(GetExecutionContext()->UserAgent());
    }
  }

  return userAgent_ChromiumImpl();
}

}  // namespace blink
