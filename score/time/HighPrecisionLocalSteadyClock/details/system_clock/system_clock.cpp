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
#include "score/time/HighPrecisionLocalSteadyClock/details/system_clock/system_clock.h"

namespace score
{
namespace time
{
namespace details
{
namespace sys_time
{

SystemClock::SystemClock() noexcept = default;

SystemClock::~SystemClock() noexcept = default;

HighPrecisionLocalSteadyClock::time_point SystemClock::Now() noexcept
{
    return time_point{
        std::chrono::duration_cast<time_point::duration>(std::chrono::high_resolution_clock::now().time_since_epoch())};
}

}  // namespace sys_time
}  // namespace details
}  // namespace time
}  // namespace score
