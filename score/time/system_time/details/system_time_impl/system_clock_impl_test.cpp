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
#include "score/time/system_time/details/system_time_impl/system_clock_impl.h"

#include <gtest/gtest.h>

#include <thread>

namespace score
{
namespace time
{
namespace detail
{
namespace test
{

class SystemClockImplTest : public ::testing::Test
{
};

TEST_F(SystemClockImplTest, NowReturnsPositiveUnixEpochTime)
{
    SystemClockImpl clock;
    const auto snapshot = clock.Now();

    // Any timestamp after 2000-01-01 00:00:00 UTC (946684800 s) is valid.
    constexpr auto kYear2000Ns = 946684800LL * 1'000'000'000LL;
    EXPECT_GT(snapshot.TimePointNs().count(), kYear2000Ns);
}

TEST_F(SystemClockImplTest, NowIsMonotonicallyIncreasing)
{
    SystemClockImpl clock;
    const auto first = clock.Now();

    std::this_thread::sleep_for(std::chrono::milliseconds{10});

    EXPECT_GT(clock.Now().TimePoint(), first.TimePoint());
}

TEST_F(SystemClockImplTest, NowSnapshotCarriesNoStatus)
{
    SystemClockImpl clock;
    const auto snapshot = clock.Now();

    // NoStatus is an empty struct — verify it is accessible (compile + link check).
    const NoStatus status = snapshot.Status();
    (void)status;
    SUCCEED();
}

}  // namespace test
}  // namespace detail
}  // namespace time
}  // namespace score
