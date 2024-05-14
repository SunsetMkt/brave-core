/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_IPFS_IPFS_SERVICE_IMPL_DELEGATE_H_
#define BRAVE_BROWSER_IPFS_IPFS_SERVICE_IMPL_DELEGATE_H_

#include "base/memory/raw_ptr.h"
#include "brave/components/ipfs/ipfs_service_delegate.h"

class PrefService;

namespace ipfs {

class IpfsServiceImplDelegate : public IpfsServiceDelegate {
 public:
  explicit IpfsServiceImplDelegate(
      PrefService* local_state);
  ~IpfsServiceImplDelegate() override;
  void OnImportToIpfsFinished(IpfsService* ipfs_service) override;

 private:
  raw_ptr<PrefService> local_state_ = nullptr;
};

}  // namespace ipfs

#endif  // BRAVE_BROWSER_IPFS_IPFS_SERVICE_IMPL_DELEGATE_H_
