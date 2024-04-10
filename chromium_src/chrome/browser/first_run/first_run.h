/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_CHROME_BROWSER_FIRST_RUN_FIRST_RUN_H_
#define BRAVE_CHROMIUM_SRC_CHROME_BROWSER_FIRST_RUN_FIRST_RUN_H_

#include "components/version_info/channel.h"

#define IsMetricsReportingOptIn                                \
  IsMetricsReportingOptIn();                                   \
  bool IsMetricsReportingOptIn(version_info::Channel channel); \
  bool IsMetricsReportingOptIn_ChromiumImpl
#include "src/chrome/browser/first_run/first_run.h"
#undef IsMetricsReportingOptIn

#endif  // BRAVE_CHROMIUM_SRC_CHROME_BROWSER_FIRST_RUN_FIRST_RUN_H_
