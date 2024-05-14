/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_WAYBACK_MACHINE_WAYBACK_STATE_H_
#define BRAVE_COMPONENTS_BRAVE_WAYBACK_MACHINE_WAYBACK_STATE_H_

enum class WaybackState {
  kInitial,       // Initial state.
  kNeedToCheck,   // Found current page is missing.
  kFetching,      // Asked to wayback machine.
  kLoaded,        // Wayback url is loaded.
  kNotAvailable,  // wayback url is not available.
};

#endif  // BRAVE_COMPONENTS_BRAVE_WAYBACK_MACHINE_WAYBACK_STATE_H_
