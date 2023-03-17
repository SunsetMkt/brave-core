/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_FEDERATED_ADAPTERS_FLOWER_HELPER_H_
#define BRAVE_COMPONENTS_BRAVE_FEDERATED_ADAPTERS_FLOWER_HELPER_H_

#include <string>

#include "brave/components/brave_federated/task/typing.h"
#include "brave/third_party/flower/src/proto/flwr/proto/fleet.pb.h"
#include "brave/third_party/flower/src/proto/flwr/proto/transport.pb.h"

namespace brave_federated {

TaskList ParseTaskListFromResponseBody(const std::string& response_body);
std::string BuildGetTasksPayload();

std::string BuildPostTaskResultsPayload(TaskResult result);
}  // namespace brave_federated

#endif  // BRAVE_COMPONENTS_BRAVE_FEDERATED_ADAPTERS_FLOWER_HELPER_H_
