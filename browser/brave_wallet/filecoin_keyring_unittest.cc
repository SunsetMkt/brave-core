/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_wallet/browser/filecoin_keyring.h"

#include "base/base64.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/test/bind.h"
#include "base/test/task_environment.h"
#include "brave/components/brave_wallet/browser/keyring_service.h"
#include "brave/components/services/brave_wallet/public/cpp/test_support/in_process_third_party_service_test_environment.h"
#include "brave/components/services/brave_wallet/public/cpp/third_party_service.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace brave_wallet {

class FilecoinKeyringUnitTest : public testing::Test {
 public:
  FilecoinKeyringUnitTest() : keyring_(brave_wallet::mojom::kFilecoinTestnet) {}
  ~FilecoinKeyringUnitTest() override = default;

  absl::optional<std::string> ImportFilecoinAccount(
      const std::vector<uint8_t>& private_key,
      mojom::FilecoinAddressProtocol protocol) {
    absl::optional<std::string> address_out;
    base::RunLoop run_loop;
    keyring_.ImportFilecoinAccount(
        private_key, protocol,
        base::BindLambdaForTesting(
            [&run_loop, &address_out](absl::optional<std::string> address) {
              address_out = address;
              run_loop.Quit();
            }));
    run_loop.Run();
    return address_out;
  }

  absl::optional<std::string> SignTransaction(const std::string& address,
                                              const FilTransaction* tx) {
    absl::optional<std::string> signature;
    base::RunLoop run_loop;
    keyring_.SignTransaction(
        address, tx,
        base::BindLambdaForTesting([&](absl::optional<std::string> v) {
          signature = v;
          run_loop.Quit();
        }));
    run_loop.Run();
    return signature;
  }

 protected:
  base::test::TaskEnvironment task_environment_;
  InProcessThirdPartyServiceTestEnvironment in_proc_third_party_service_env_;
  FilecoinKeyring keyring_;
};

TEST_F(FilecoinKeyringUnitTest, DecodeImportPayload) {
  std::string payload_hex;
  std::vector<uint8_t> private_key;
  mojom::FilecoinAddressProtocol protocol;
  // zero key
  ASSERT_FALSE(
      FilecoinKeyring::DecodeImportPayload(payload_hex, nullptr, &protocol));
  // zero protocol
  ASSERT_FALSE(
      FilecoinKeyring::DecodeImportPayload(payload_hex, &private_key, nullptr));
  EXPECT_TRUE(private_key.empty());

  ASSERT_FALSE(
      FilecoinKeyring::DecodeImportPayload("", &private_key, &protocol));
  EXPECT_TRUE(private_key.empty());

  // broken json
  ASSERT_FALSE(FilecoinKeyring::DecodeImportPayload(
      "7b2254797065223a22626c73222c22507269766174654b6579223a2270536e7752332f38"
      "55616b53516f777858742b345a75393257586d424d526e74716d6448696136724853453d"
      "22",
      &private_key, &protocol));
  EXPECT_TRUE(private_key.empty());

  // no type in json
  ASSERT_FALSE(FilecoinKeyring::DecodeImportPayload(
      "7b22507269766174654b6579223a2270536e7752332f3855616b53516f777858742b345a"
      "75393257586d424d526e74716d6448696136724853453d22207d",
      &private_key, &protocol));
  EXPECT_TRUE(private_key.empty());

  // no private key in json
  ASSERT_FALSE(FilecoinKeyring::DecodeImportPayload(
      "7b2254797065223a22626c73227d", &private_key, &protocol));
  EXPECT_TRUE(private_key.empty());

  // type empty
  ASSERT_FALSE(FilecoinKeyring::DecodeImportPayload(
      "7b2254797065223a22222c22507269766174654b6579223a2270536e7752332f3855616b"
      "53516f777858742b345a75393257586d424d526e74716d6448696136724853453d227d",
      &private_key, &protocol));
  EXPECT_TRUE(private_key.empty());

  // private key empty
  ASSERT_FALSE(FilecoinKeyring::DecodeImportPayload(
      "7b2254797065223a22626c73222c22507269766174654b6579223a22227d",
      &private_key, &protocol));
  EXPECT_TRUE(private_key.empty());

  // private key with broken encoding
  ASSERT_FALSE(FilecoinKeyring::DecodeImportPayload(
      "7b2254797065223a22626c73222c22507269766174654b6579223a227053227d",
      &private_key, &protocol));
  EXPECT_TRUE(private_key.empty());
  // valid payload
  payload_hex =
      "7b2254797065223a22626c73222c22507269766174654b6579223a2270536e7752332f38"
      "55616b53516f777858742b345a75393257586d424d526e74716d6448696136724853453d"
      "227d";
  ASSERT_TRUE(FilecoinKeyring::DecodeImportPayload(payload_hex, &private_key,
                                                   &protocol));
  EXPECT_EQ(base::Base64Encode(private_key),
            "pSnwR3/8UakSQowxXt+4Zu92WXmBMRntqmdHia6rHSE=");
  EXPECT_EQ(protocol, mojom::FilecoinAddressProtocol::BLS);
}

TEST_F(FilecoinKeyringUnitTest, ImportFilecoinSECP) {
  std::string private_key_base64 =
      "rQG5jnbc+y64fckG+T0EHVwpLBmW9IgAT7U990HXcGk=";
  std::string input_key;
  ASSERT_TRUE(base::Base64Decode(private_key_base64, &input_key));
  ASSERT_FALSE(input_key.empty());
  std::vector<uint8_t> private_key(input_key.begin(), input_key.end());

  auto address = ImportFilecoinAccount(
      private_key, mojom::FilecoinAddressProtocol::SECP256K1);
  ASSERT_TRUE(address);
  EXPECT_EQ(*address, "t1lqarsh4nkg545ilaoqdsbtj4uofplt6sto26ziy");
  EXPECT_EQ(keyring_.GetImportedAccountsNumber(), size_t(1));
}

TEST_F(FilecoinKeyringUnitTest, ImportFilecoinBLS) {
  std::string private_key_hex =
      "7b2254797065223a22626c73222c22507269766174654b6579223a2270536e7752332f38"
      "55616b53516f777858742b345a75393257586d424d526e74716d6448696136724853453d"
      "227d";
  std::vector<uint8_t> private_key;
  mojom::FilecoinAddressProtocol protocol;
  ASSERT_TRUE(FilecoinKeyring::DecodeImportPayload(private_key_hex,
                                                   &private_key, &protocol));
  EXPECT_EQ(protocol, mojom::FilecoinAddressProtocol::BLS);
  auto address = ImportFilecoinAccount(private_key, protocol);
  ASSERT_TRUE(address);
  EXPECT_EQ(*address,
            "t3wwtato54ee5aod7j5uv2n75jpyn4hpwx3f2kx5cijtoxgytiul2dczrak3ghlbt5"
            "zjnj574y3snhcb5bthva");
  EXPECT_EQ(keyring_.GetImportedAccountsNumber(), size_t(1));

  // empty private key
  address = ImportFilecoinAccount({}, mojom::FilecoinAddressProtocol::BLS);
  ASSERT_FALSE(address);

  // broken private key
  private_key_hex = "6a4b3d3f3ccb3676e34e16bc07a937";
  std::vector<uint8_t> broken_private_key;
  ASSERT_TRUE(base::HexStringToBytes(private_key_hex, &broken_private_key));
  address = ImportFilecoinAccount(broken_private_key,
                                  mojom::FilecoinAddressProtocol::BLS);
  ASSERT_FALSE(address);

  std::vector<uint8_t> zero_private_key(32, 0);
  address = ImportFilecoinAccount(zero_private_key,
                                  mojom::FilecoinAddressProtocol::BLS);
  ASSERT_TRUE(address);
  EXPECT_EQ(*address,
            "t3yaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaby2smx7a");

  std::vector<uint8_t> ff_private_key(32, 255);
  address = ImportFilecoinAccount(ff_private_key,
                                  mojom::FilecoinAddressProtocol::BLS);
  ASSERT_FALSE(address);
}

TEST_F(FilecoinKeyringUnitTest, SignTransaction) {
  const std::string address = "t1lqarsh4nkg545ilaoqdsbtj4uofplt6sto26ziy";
  auto signature = SignTransaction(address, nullptr);
  EXPECT_FALSE(signature);

  auto transaction = FilTransaction::FromTxData(
      false,
      mojom::FilTxData::New("1", "2", "3", "4", "5",
                            "t1h5tg3bhp5r56uzgjae2373znti6ygq4agkx4hzq", "6"));
  signature = SignTransaction(address, &transaction.value());
  EXPECT_FALSE(signature);

  std::string private_key_base64 =
      "rQG5jnbc+y64fckG+T0EHVwpLBmW9IgAT7U990HXcGk=";
  std::string input_key;
  ASSERT_TRUE(base::Base64Decode(private_key_base64, &input_key));
  ASSERT_FALSE(input_key.empty());
  std::vector<uint8_t> private_key(input_key.begin(), input_key.end());

  auto imported_address = ImportFilecoinAccount(
      private_key, mojom::FilecoinAddressProtocol::SECP256K1);
  ASSERT_TRUE(imported_address);
  EXPECT_EQ(address, *imported_address);
  signature = SignTransaction(address, &transaction.value());
  EXPECT_TRUE(signature);
}

}  // namespace brave_wallet
