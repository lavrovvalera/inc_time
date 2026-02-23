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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_TICK_PROVIDER_MOCK_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_TICK_PROVIDER_MOCK_H

#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/tick_provider.h"

#include <gmock/gmock.h>
#include <mutex>

namespace score
{
namespace time
{
namespace details
{
namespace qtime
{

class TickProviderMock
{
  public:
    MOCK_METHOD(std::uint64_t, GetClockCyclesPerSec, (), ());

    MOCK_METHOD(std::uint64_t, ClockCycles, (), ());

    static TickProviderMock& GetMockInstance() noexcept
    {
        const std::lock_guard<std::mutex> guard{mutex};
        assert(mock_instance.operator bool());
        return *mock_instance;
    }
    static void CreateMockInstance()
    {
        const std::lock_guard<std::mutex> guard{mutex};
        mock_instance = std::make_unique<TickProviderMock>();
    }
    static void DestroyMockInstance() noexcept
    {
        const std::lock_guard<std::mutex> guard{mutex};
        testing::Mock::VerifyAndClearExpectations(mock_instance.get());
        mock_instance.reset();
    }

  private:
    static std::unique_ptr<TickProviderMock> mock_instance;
    static std::mutex mutex;
};

}  // namespace qtime
}  // namespace details
}  // namespace time
}  // namespace score

#endif  // #define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_TICK_PROVIDER_MOCK_H
