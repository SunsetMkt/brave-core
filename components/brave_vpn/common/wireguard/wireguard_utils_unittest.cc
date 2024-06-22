/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_vpn/common/wireguard/wireguard_utils.h"

#include <string>

#include "base/base64.h"
#include "base/json/json_reader.h"
#include "base/logging.h"
#include "base/strings/utf_string_conversions.h"
#include "base/test/scoped_feature_list.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

TEST(BraveVPNWireGuardUtilsUnitTest, ValidateKey) {
  // Invalid.
  // > empty
  EXPECT_FALSE(
      brave_vpn::wireguard::ValidateKey(L"", "public_key").has_value());
  // > not base64 encoded
  EXPECT_FALSE(brave_vpn::wireguard::ValidateKey(L"abcdefghi", "public_key")
                   .has_value());
  // > not 32 bytes
  std::wstring key_str = base::UTF8ToWide(base::Base64Encode("abcdefghi"));
  EXPECT_FALSE(brave_vpn::wireguard::ValidateKey(key_str.c_str(), "public_key")
                   .has_value());
  // > has CR/LF in encoded value
  EXPECT_FALSE(brave_vpn::wireguard::ValidateKey(LR"(MsdIM8m7Ee13QbjFe3
fbFtShscNPxYrqQZHvXFnAago=)",
                                                 "public_key")
                   .has_value());

  // Valid.
  key_str =
      base::UTF8ToWide(base::Base64Encode("01234567890123456789012345678901"));
  EXPECT_TRUE(brave_vpn::wireguard::ValidateKey(key_str.c_str(), "public_key")
                  .has_value());

  EXPECT_TRUE(brave_vpn::wireguard::ValidateKey(
                  L"MsdIM8m7Ee13QbjFe3fbFtShscNPxYrqQZHvXFnAago=", "public_key")
                  .has_value());
}

TEST(BraveVPNWireGuardUtilsUnitTest, ValidateAddress) {
  // Invalid.
  EXPECT_FALSE(brave_vpn::wireguard::ValidateAddress(L"").has_value());
  EXPECT_FALSE(brave_vpn::wireguard::ValidateAddress(L"a.b.c.d").has_value());
  // IPv6 not allowed.
  EXPECT_FALSE(
      brave_vpn::wireguard::ValidateAddress(L"fe80::1ff:fe23:4567:890a")
          .has_value());
  EXPECT_FALSE(brave_vpn::wireguard::ValidateAddress(L"1.1.1.1.1").has_value());
  EXPECT_FALSE(brave_vpn::wireguard::ValidateAddress(L"300.1.1.1").has_value());
  // Spaces are not stripped out.
  // Removed call to base::TrimWhitespaceASCII.
  EXPECT_FALSE(
      brave_vpn::wireguard::ValidateAddress(L"  192.168.1.1   ").has_value());

  // Valid.
  auto response = brave_vpn::wireguard::ValidateAddress(L"192.168.1.1");
  EXPECT_TRUE(response.has_value());
  // Verify parsing worked.
  EXPECT_EQ(response.value(), "192.168.1.1");
}

TEST(BraveVPNWireGuardUtilsUnitTest, ValidateEndpoint) {
  // Invalid.
  EXPECT_FALSE(brave_vpn::wireguard::ValidateEndpoint(L"").has_value());
  EXPECT_FALSE(
      brave_vpn::wireguard::ValidateEndpoint(L"192.168.1.1").has_value());
  EXPECT_FALSE(brave_vpn::wireguard::ValidateEndpoint(
                   L"toronto-ipsec-8.not-guardianapp.com")
                   .has_value());
  EXPECT_FALSE(brave_vpn::wireguard::ValidateEndpoint(LR"(france-ipsec-1
.sudosecuritygroup.com)")
                   .has_value());
  EXPECT_FALSE(brave_vpn::wireguard::ValidateEndpoint(
                   L"france-ipsec-1 .sudosecuritygroup.com")
                   .has_value());
  // Unicode will fail because of base::WideToUTF8.
  // Hostnames realistically should be punycode encoded.
  EXPECT_FALSE(
      brave_vpn::wireguard::ValidateEndpoint(L"汉字.sudosecuritygroup.com")
          .has_value());

  // Valid.
  EXPECT_TRUE(
      brave_vpn::wireguard::ValidateEndpoint(L"toronto-ipsec-8.guardianapp.com")
          .has_value());
  EXPECT_TRUE(brave_vpn::wireguard::ValidateEndpoint(
                  L"france-ipsec-1.sudosecuritygroup.com")
                  .has_value());
}
