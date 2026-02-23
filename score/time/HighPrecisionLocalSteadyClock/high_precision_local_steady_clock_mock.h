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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_HIGH_PRECISION_LOCAL_STEADY_CLOCK_MOCK_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_HIGH_PRECISION_LOCAL_STEADY_CLOCK_MOCK_H

#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock.h"

#include <gmock/gmock.h>

namespace score
{
namespace time
{

class HighPrecisionLocalSteadyClockMock : public HighPrecisionLocalSteadyClock
{
  public:
    HighPrecisionLocalSteadyClockMock();
    HighPrecisionLocalSteadyClockMock(HighPrecisionLocalSteadyClockMock&&) noexcept = delete;
    HighPrecisionLocalSteadyClockMock(const HighPrecisionLocalSteadyClockMock&) noexcept = delete;
    HighPrecisionLocalSteadyClockMock& operator=(HighPrecisionLocalSteadyClockMock&&) noexcept = delete;
    HighPrecisionLocalSteadyClockMock& operator=(const HighPrecisionLocalSteadyClockMock&) noexcept = delete;

    virtual ~HighPrecisionLocalSteadyClockMock() noexcept;

    MOCK_METHOD(HighPrecisionLocalSteadyClock::time_point, Now, (), (noexcept, override));
};

}  // namespace time
}  // namespace score

#endif  // #define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_HIGH_PRECISION_LOCAL_STEADY_CLOCK_MOCK_H
