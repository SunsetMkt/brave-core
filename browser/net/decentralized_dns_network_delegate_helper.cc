/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/net/decentralized_dns_network_delegate_helper.h"

#include <optional>
#include <utility>
#include <vector>

#include "brave/browser/brave_wallet/json_rpc_service_factory.h"
#include "brave/components/brave_wallet/browser/json_rpc_service.h"
#include "brave/components/brave_wallet/common/brave_wallet.mojom.h"
#include "brave/components/decentralized_dns/core/constants.h"
#include "brave/components/decentralized_dns/core/utils.h"
#include "chrome/browser/browser_process.h"
#include "components/base32/base32.h"
#include "content/public/browser/browser_context.h"
#include "net/base/net_errors.h"

namespace {
// Ipfs codes from multicodec table
// https://github.com/multiformats/multicodec/blob/master/table.csv
const int64_t kIpfsNSCodec = 0xE3;
const int64_t kIpnsNSCodec = 0xE5;
inline constexpr char kIPFSScheme[] = "ipfs";
inline constexpr char kIPNSScheme[] = "ipns";

// Decodes a varint from the given string piece into the given int64_t. Returns
// remaining span if the string had a valid varint (where a byte was found with
// it's top bit set).
base::span<const uint8_t> DecodeVarInt(base::span<const uint8_t> from,
                                       int64_t* into) {
  auto it = from.begin();
  int shift = 0;
  uint64_t ret = 0;
  do {
    if (it == from.end()) {
      return {};
    }

    // Shifting 64 or more bits is undefined behavior.
    DCHECK_LT(shift, 64);
    unsigned char c = *it;
    ret |= static_cast<uint64_t>(c & 0x7f) << shift;
    shift += 7;
  } while (*it++ & 0x80);
  *into = static_cast<int64_t>(ret);
  return from.subspan(it - from.begin());
}

}  // namespace

namespace decentralized_dns {

GURL ContentHashToCIDv1URL(base::span<const uint8_t> contenthash) {
  int64_t code = 0;
  contenthash = DecodeVarInt(contenthash, &code);
  if (contenthash.empty()) {
    return GURL();
  }
  if (code != kIpnsNSCodec && code != kIpfsNSCodec) {
    return GURL();
  }
  std::string encoded = base32::Base32Encode(contenthash);
  if (encoded.empty()) {
    return GURL();
  }
  std::string trimmed;
  base::TrimString(encoded, "=", &trimmed);
  std::string lowercase = base::ToLowerASCII(trimmed);
  // multibase format <base-encoding-character><base-encoded-data>
  // https://github.com/multiformats/multibase/blob/master/multibase.csv
  std::string cidv1 = "b" + lowercase;
  std::string scheme = (code == kIpnsNSCodec) ? kIPNSScheme : kIPFSScheme;
  return GURL(scheme + "://" + cidv1);
}

int OnBeforeURLRequest_DecentralizedDnsPreRedirectWork(
    const brave::ResponseCallback& next_callback,
    std::shared_ptr<brave::BraveRequestInfo> ctx) {
  DCHECK(!next_callback.is_null());

  if (!ctx->browser_context || ctx->browser_context->IsOffTheRecord() ||
      !g_browser_process) {
    return net::OK;
  }

  auto* json_rpc_service =
      brave_wallet::JsonRpcServiceFactory::GetServiceForContext(
          ctx->browser_context);
  if (!json_rpc_service) {
    return net::OK;
  }

  if (IsUnstoppableDomainsTLD(ctx->request_url.host_piece()) &&
      IsUnstoppableDomainsResolveMethodEnabled(
          g_browser_process->local_state())) {
    json_rpc_service->UnstoppableDomainsResolveDns(
        ctx->request_url.host(),
        base::BindOnce(&OnBeforeURLRequest_UnstoppableDomainsRedirectWork,
                       next_callback, ctx));

    return net::ERR_IO_PENDING;
  }

  if (IsENSTLD(ctx->request_url.host_piece()) &&
      IsENSResolveMethodEnabled(g_browser_process->local_state())) {
    json_rpc_service->EnsGetContentHash(
        ctx->request_url.host(),
        base::BindOnce(&OnBeforeURLRequest_EnsRedirectWork, next_callback,
                       ctx));

    return net::ERR_IO_PENDING;
  }

  if (IsSnsTLD(ctx->request_url.host_piece()) &&
      IsSnsResolveMethodEnabled(g_browser_process->local_state())) {
    json_rpc_service->SnsResolveHost(
        ctx->request_url.host(),
        base::BindOnce(&OnBeforeURLRequest_SnsRedirectWork, next_callback,
                       ctx));

    return net::ERR_IO_PENDING;
  }

  return net::OK;
}

void OnBeforeURLRequest_EnsRedirectWork(
    const brave::ResponseCallback& next_callback,
    std::shared_ptr<brave::BraveRequestInfo> ctx,
    const std::vector<uint8_t>& content_hash,
    bool require_offchain_consent,
    brave_wallet::mojom::ProviderError error,
    const std::string& error_message) {
  DCHECK(!next_callback.is_null());

  if (error != brave_wallet::mojom::ProviderError::kSuccess) {
    next_callback.Run();
    return;
  }

  if (require_offchain_consent) {
    ctx->pending_error = net::ERR_ENS_OFFCHAIN_LOOKUP_NOT_SELECTED;
    next_callback.Run();
    return;
  }

  GURL ipfs_uri = ContentHashToCIDv1URL(content_hash);
  if (ipfs_uri.is_valid()) {
    ctx->new_url_spec = ipfs_uri.spec();
  }

  next_callback.Run();
}

void OnBeforeURLRequest_SnsRedirectWork(
    const brave::ResponseCallback& next_callback,
    std::shared_ptr<brave::BraveRequestInfo> ctx,
    const std::optional<GURL>& url,
    brave_wallet::mojom::SolanaProviderError error,
    const std::string& error_message) {
  if (error == brave_wallet::mojom::SolanaProviderError::kSuccess && url &&
      url->is_valid()) {
    ctx->new_url_spec = url->spec();
  }

  if (!next_callback.is_null()) {
    next_callback.Run();
  }
}

void OnBeforeURLRequest_UnstoppableDomainsRedirectWork(
    const brave::ResponseCallback& next_callback,
    std::shared_ptr<brave::BraveRequestInfo> ctx,
    const std::optional<GURL>& url,
    brave_wallet::mojom::ProviderError error,
    const std::string& error_message) {
  if (error == brave_wallet::mojom::ProviderError::kSuccess && url &&
      url->is_valid()) {
    ctx->new_url_spec = url->spec();
  }

  if (!next_callback.is_null()) {
    next_callback.Run();
  }
}

}  // namespace decentralized_dns
