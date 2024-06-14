/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_vpn/common/wireguard/wireguard_utils.h"

#include <stdint.h>

#include <optional>
#include <vector>

#include "base/base64.h"
#include "base/logging.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "crypto/openssl_util.h"
#include "net/base/ip_address.h"
#include "net/base/url_util.h"
#include "third_party/boringssl/src/include/openssl/base64.h"
#include "third_party/boringssl/src/include/openssl/curve25519.h"
#include "url/url_util.h"

namespace brave_vpn {

namespace wireguard {

namespace {
std::string EncodeBase64(const std::vector<uint8_t>& in) {
  std::string res;
  size_t size = 0;
  if (!EVP_EncodedLength(&size, in.size())) {
    DCHECK(false);
    return "";
  }
  std::vector<uint8_t> out(size);
  size_t numEncBytes = EVP_EncodeBlock(&out.front(), &in.front(), in.size());
  DCHECK_NE(numEncBytes, 0u);
  res = reinterpret_cast<char*>(&out.front());
  return res;
}

constexpr char kCloudflareIPv4[] = "1.1.1.1";
// Template for wireguard config generation.
constexpr char kWireguardConfigTemplate[] = R"(
  [Interface]
  PrivateKey = {client_private_key}
  Address = {mapped_ipv4_address}
  DNS = {dns_servers}
  [Peer]
  PublicKey = {server_public_key}
  AllowedIPs = 0.0.0.0/0, ::/0
  Endpoint = {vpn_server_hostname}:51821
)";

}  // namespace

std::optional<std::string> CreateWireguardConfig(
    const std::string& client_private_key,
    const std::string& server_public_key,
    const std::string& vpn_server_hostname,
    const std::string& mapped_ipv4_address) {
  if (client_private_key.empty() || server_public_key.empty() ||
      vpn_server_hostname.empty() || mapped_ipv4_address.empty()) {
    return std::nullopt;
  }
  std::string config = kWireguardConfigTemplate;
  base::ReplaceSubstringsAfterOffset(&config, 0, "{client_private_key}",
                                     client_private_key);
  base::ReplaceSubstringsAfterOffset(&config, 0, "{server_public_key}",
                                     server_public_key);
  base::ReplaceSubstringsAfterOffset(&config, 0, "{vpn_server_hostname}",
                                     vpn_server_hostname);
  base::ReplaceSubstringsAfterOffset(&config, 0, "{mapped_ipv4_address}",
                                     mapped_ipv4_address);
  base::ReplaceSubstringsAfterOffset(&config, 0, "{dns_servers}",
                                     kCloudflareIPv4);
  return config;
}

WireguardKeyPair GenerateNewX25519Keypair() {
  crypto::EnsureOpenSSLInit();
  uint8_t pubkey[32] = {}, privkey[32] = {};
  X25519_keypair(pubkey, privkey);
  return std::make_tuple(
      EncodeBase64(std::vector<uint8_t>(pubkey, pubkey + 32)),
      EncodeBase64(std::vector<uint8_t>(privkey, privkey + 32)));
}

bool ValidateKey(const wchar_t* key,
                 std::string* output,
                 const std::string field_name) {
  if (!base::WideToUTF8(key, wcslen(key), output)) {
    VLOG(1) << "failed decoding " << field_name;
    return false;
  }

  base::TrimWhitespaceASCII(*output, base::TRIM_ALL, output);

  if ((*output).length() == 0) {
    VLOG(1) << field_name << " does not have a value";
    return false;
  }

  return true;
}

bool ValidateAddress(const wchar_t* address, std::string* output) {
  if (!base::WideToUTF8(address, wcslen(address), output)) {
    VLOG(1) << "failed decoding address";
    return false;
  }

  base::TrimWhitespaceASCII(*output, base::TRIM_ALL, output);

  auto parsed = net::IPAddress::FromIPLiteral(*output);
  if (!parsed.has_value()) {
    VLOG(1) << "failed parsing address";
    return false;
  }

  auto parsed_ip = parsed.value();
  if (!parsed_ip.IsValid()) {
    VLOG(1) << "address is not valid";
    return false;
  }

  if (!parsed_ip.IsIPv4()) {
    VLOG(1) << "address must be IPv4";
    return false;
  }

  return true;
}

bool ValidateEndpoint(const wchar_t* endpoint, std::string* output) {
  if (!base::WideToUTF8(endpoint, wcslen(endpoint), output)) {
    VLOG(1) << "failed decoding endpoint";
    return false;
  }

  base::TrimWhitespaceASCII(*output, base::TRIM_ALL, output);

  std::string parsed_host;
  int parsed_port = 0;
  if (!net::ParseHostAndPort(*output, &parsed_host, &parsed_port)) {
    VLOG(1) << "failed parsing endpoint";
    return false;
  }

  if (!url::DomainIs(parsed_host, "guardianapp.com") &&
      !url::DomainIs(parsed_host, "sudosecuritygroup.com")) {
    VLOG(1) << "endpoint is not a valid hostname";
    return false;
  }

  return true;
}

}  // namespace wireguard

}  // namespace brave_vpn
