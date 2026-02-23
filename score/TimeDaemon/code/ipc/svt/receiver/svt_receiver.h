/********************************************************************************
 * Copyright (c) 2025 Contributors to the Eclipse Foundation
 *
 * See the NOTICE file(s) distributed with this work for additional
 * information regarding copyright ownership.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/
#ifndef SCORE_TIMEDAEMON_CODE_IPC_SVT_SVT_RECEIVER_H
#define SCORE_TIMEDAEMON_CODE_IPC_SVT_SVT_RECEIVER_H

#include "score/TimeDaemon/code/ipc/receiver.h"
#include "score/TimeDaemon/code/ipc/svt/svt_time_info.h"

namespace score
{
namespace td
{

/**
 * @brief Receiver interface alias
 */
using SvtReceiver = Receiver<svt::TimeBaseSnapshot>;

}  // namespace td
}  // namespace score

#endif  // SCORE_TIMEDAEMON_CODE_IPC_SVT_SVT_RECEIVER_H
