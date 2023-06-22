/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/leaked_credentials/leaked_credentials_api.h"

#include "brave/components/leaked_credentials/rs/cxx/src/lib.rs.h"
#include "third_party/rust/cxx/v1/crate/include/cxx.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace leaked_credentials {

TEST(LeakedCredentialsUnittest, TestHelloCPlusPlus) {
  // EXPECT_EQ(expected, actual)
  EXPECT_EQ(42, leaked_credentials::HelloCPlusPlus());
}

} // namespace leaked_credentials
