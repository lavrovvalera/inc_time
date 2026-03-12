/********************************************************************************
 * Copyright (c) 2026 Contributors to the Eclipse Foundation
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
#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock_mock.h"

namespace score
{
namespace time
{

HighPrecisionLocalSteadyClockMock::HighPrecisionLocalSteadyClockMock()
{
    using ::testing::Invoke;

    // By default when called HighPrecisionLocalSteadyClockMock::Now() for unit testing, mock will
    // return high_resolution_clock values mapped to local time_point. In case of unit tests where
    // from HighPrecisionLocalSteadyClock it is expected that nanoseconds time_point is returned (without
    // any explicit values), there is no need to invoke mock to return std::chrono::high_resolution_clock time_point.
    ON_CALL(*this, Now()).WillByDefault(Invoke([]() {
        return HighPrecisionLocalSteadyClock::time_point{
            std::chrono::duration_cast<HighPrecisionLocalSteadyClock::time_point::duration>(
                std::chrono::high_resolution_clock::now().time_since_epoch())};
    }));
}

HighPrecisionLocalSteadyClockMock::~HighPrecisionLocalSteadyClockMock() noexcept = default;

}  // namespace time
}  // namespace score
