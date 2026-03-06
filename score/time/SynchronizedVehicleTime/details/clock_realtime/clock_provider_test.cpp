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
#include "score/time/SynchronizedVehicleTime/details/clock_realtime/clock_provider.h"
#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock_mock.h"

#include <gtest/gtest.h>
#include <chrono>

namespace score
{
namespace time
{
namespace details
{
namespace clock_realtime
{

using ::testing::_;
using ::testing::Return;

using namespace std::chrono_literals;

using StatusFlag = SynchronizedVehicleTime::StatusFlag;

score::time::HighPrecisionLocalSteadyClock::time_point GetTimepoint()
{
    return score::time::HighPrecisionLocalSteadyClock::time_point{
        std::chrono::duration_cast<score::time::HighPrecisionLocalSteadyClock::time_point::duration>(
            std::chrono::high_resolution_clock::now().time_since_epoch())};
}

class TestClockProvider : public ::testing::Test
{
};

TEST_F(TestClockProvider, Destruction)
{
    // Given an instance via base-class pointer
    std::unique_ptr<SynchronizedVehicleTime> slave_base = std::make_unique<ClockProvider>();
    // When being reset
    slave_base.reset();
    // Then it gets destructed

    // Given an instance via direct pointer
    auto slave_impl = std::make_unique<ClockProvider>();
    // When being reset
    slave_impl.reset();
    // Then it gets destructed

    {
        // Given an instance via object on stack
        ClockProvider timebase{};
        // When going out of scope
        (void)timebase;
    }
    // Then it gets destructed
}

TEST_F(TestClockProvider, GetCurrentTimeAndStatusSynchronized)
{
    auto hplsc_mock = std::make_unique<HighPrecisionLocalSteadyClockMock>();
    auto hplsc_mock_raw_ptr = hplsc_mock.get();

    // Given a ClockProvider instance
    ClockProvider timebase{std::move(hplsc_mock)};

    // Get timepoint value from high_precision_clock
    const auto expect_time{GetTimepoint()};

    EXPECT_CALL(*hplsc_mock_raw_ptr, Now()).WillOnce(Return(expect_time));

    // When calling Now()
    const auto current_timebase{timebase.Now()};

    // Then timebase status shall be synchronized and time is equal to expect_time
    EXPECT_EQ(current_timebase.getTimepoint().time_since_epoch().count(), expect_time.time_since_epoch().count());

    EXPECT_TRUE(current_timebase.getTimepointStatus().IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_FALSE(current_timebase.getTimepointStatus().IsAnyOfFlagsActive({StatusFlag::kUnknown,
                                                                           StatusFlag::kTimeOut,
                                                                           StatusFlag::kTimeLeapPast,
                                                                           StatusFlag::kSynchToGateway,
                                                                           StatusFlag::kTimeLeapFuture}));
    EXPECT_TRUE(current_timebase.getTimepointStatus().IsSynchronized());
}

TEST_F(TestClockProvider, GetCurrentRateDeviation)
{
    // Given a ClockProvider instance
    ClockProvider timebase{};

    // Then GetRateDeviation should return expected rate_deviation
    EXPECT_EQ(timebase.GetRateDeviation(), 0.0);
}

TEST_F(TestClockProvider, WaitUntilAvailableSucceeds)
{
    // For given a Receiver instance
    ClockProvider timebase{};

    // When its method WaitUntilAvailable() gets called with a timepoint in the future, then true must be returned
    const auto current_time = std::chrono::steady_clock::now();
    EXPECT_TRUE(timebase.WaitUntilAvailable(score::cpp::stop_source{}.get_token(), current_time + 3s));

    // When its method WaitUntilAvailable() gets called again with a timepoint in the future, then true must be returned
    EXPECT_TRUE(timebase.WaitUntilAvailable(score::cpp::stop_source{}.get_token(), current_time + 7s));
}

TEST_F(TestClockProvider, IsAvailableSucceeds)
{
    // Given a Receiver instance
    ClockProvider timebase{};

    // When its method IsAvailable(), true must be returned
    EXPECT_TRUE(timebase.IsAvailable());
}

TEST_F(TestClockProvider, CallAllEmptyMethods)
{
    // Given a Receiver instance
    ClockProvider timebase{};

    // When its methods ar called, nothing is returned
    timebase.SetTimeSlaveSyncDataReceivedCallback([](TimeSlaveSyncData<SynchronizedVehicleTime>) {});
    timebase.UnsetTimeSlaveSyncDataReceivedCallback();
    timebase.SetPDelayMeasurementFinishedCallback([](PDelayMeasurementData<SynchronizedVehicleTime>) {});
    timebase.UnsetPDelayMeasurementFinishedCallback();
}

}  // namespace clock_realtime
}  // namespace details
}  // namespace time
}  // namespace score
