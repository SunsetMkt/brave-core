/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/account/account_util.h"

#include "base/notreached.h"
#include "base/types/cxx23_to_underlying.h"
#include "brave/components/brave_ads/core/internal/settings/settings.h"

namespace brave_ads {

bool CanDeposit(AdType ad_type, ConfirmationType confirmation_type) {
  if (UserHasJoinedBraveRewards()) {
    // Always allow deposits for users who are part of Brave Rewards.
    return true;
  }

  switch (ad_type) {
    case AdType::kInlineContentAd:
    case AdType::kPromotedContentAd: {
      // Deposits are always allowed because a user can join Brave News without
      // needing Brave Rewards.
      return true;
    }

    case AdType::kNewTabPageAd: {
      // Only allow deposits if it's a conversion for users who have not yet
      // joined Brave Rewards.
      return confirmation_type == ConfirmationType::kConversion;
    }

    case AdType::kNotificationAd: {
      // Never allow deposits because users cannot opt into notification ads
      // without Brave Rewards.
      return false;
    }

    case AdType::kSearchResultAd: {
      // Only allow deposits if it's a conversion for users who have not yet
      // joined Brave Rewards.
      return confirmation_type == ConfirmationType::kConversion;
    }

    case AdType::kUndefined: {
      break;
    }
  }

  NOTREACHED_NORETURN() << "Unexpected value for AdType: "
                        << base::to_underlying(ad_type);
}

}  // namespace brave_ads
