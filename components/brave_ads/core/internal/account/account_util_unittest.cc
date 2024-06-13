/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// npm run test -- brave_unit_tests --filter=BraveAds*

#include "brave/components/brave_ads/core/internal/account/account_util.h"

#include "brave/components/brave_ads/core/internal/common/unittest/unittest_base.h"
#include "brave/components/brave_ads/core/internal/settings/settings_unittest_util.h"
#include "brave/components/brave_ads/core/public/account/confirmations/confirmation_type.h"

namespace brave_ads {

class BraveAdsAccountUtilTest : public UnitTestBase {};

TEST_F(BraveAdsAccountUtilTest, AlwaysAllowDepositsForRewardsUser) {
  // Act & Assert
  for (auto i = 0; i < static_cast<int>(AdType::kMaxValue); ++i) {
    const auto ad_type = static_cast<AdType>(i);

    for (auto j = 0; j < static_cast<int>(ConfirmationType::kMaxValue); ++j) {
      EXPECT_TRUE(CanDeposit(ad_type, static_cast<ConfirmationType>(j)));
    }
  }
}

TEST_F(BraveAdsAccountUtilTest,
       AlwaysAllowInlineContentAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableBraveRewards();

  // Act & Assert
  for (auto j = 0; j < static_cast<int>(ConfirmationType::kMaxValue); ++j) {
    EXPECT_TRUE(
        CanDeposit(AdType::kInlineContentAd, static_cast<ConfirmationType>(j)));
  }
}

TEST_F(BraveAdsAccountUtilTest,
       AlwaysAllowPromotedContentAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableBraveRewards();

  // Act & Assert
  for (auto j = 0; j < static_cast<int>(ConfirmationType::kMaxValue); ++j) {
    EXPECT_TRUE(CanDeposit(AdType::kPromotedContentAd,
                           static_cast<ConfirmationType>(j)));
  }
}

TEST_F(BraveAdsAccountUtilTest,
       OnlyAllowNewTabPageAdConversionDepositsForNonRewardsUser) {
  // Arrange
  test::DisableBraveRewards();

  // Act & Assert
  for (auto j = 0; j < static_cast<int>(ConfirmationType::kMaxValue); ++j) {
    const auto confirmation_type = static_cast<ConfirmationType>(j);

    const bool can_deposit =
        CanDeposit(AdType::kNewTabPageAd, confirmation_type);

    if (confirmation_type == ConfirmationType::kConversion) {
      EXPECT_TRUE(can_deposit);
    } else {
      EXPECT_FALSE(can_deposit);
    }
  }
}

TEST_F(BraveAdsAccountUtilTest,
       NeverAllowNotificationAdDepositsForNonRewardsUser) {
  // Arrange
  test::DisableBraveRewards();

  // Act & Assert
  for (auto j = 0; j < static_cast<int>(ConfirmationType::kMaxValue); ++j) {
    EXPECT_FALSE(
        CanDeposit(AdType::kNotificationAd, static_cast<ConfirmationType>(j)));
  }
}

TEST_F(BraveAdsAccountUtilTest,
       OnlyAllowSearchResultAdConversionDepositsForNonRewardsUser) {
  // Arrange
  test::DisableBraveRewards();

  // Act & Assert
  for (auto j = 0; j < static_cast<int>(ConfirmationType::kMaxValue); ++j) {
    const auto confirmation_type = static_cast<ConfirmationType>(j);

    const bool can_deposit =
        CanDeposit(AdType::kSearchResultAd, confirmation_type);

    if (confirmation_type == ConfirmationType::kConversion) {
      EXPECT_TRUE(can_deposit);
    } else {
      EXPECT_FALSE(can_deposit);
    }
  }
}

}  // namespace brave_ads
