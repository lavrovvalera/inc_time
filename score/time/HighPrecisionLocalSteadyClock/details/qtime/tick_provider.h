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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_TICK_PROVIDER_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_TICK_PROVIDER_H

#include <cstdint>

namespace score
{
namespace time
{
namespace details
{
namespace qtime
{

std::uint64_t GetClockCyclesPerSec();

}  // namespace qtime
}  // namespace details
}  // namespace time
}  // namespace score

#endif  // #define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_TICK_PROVIDER_H
