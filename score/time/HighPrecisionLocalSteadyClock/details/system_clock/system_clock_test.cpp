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
#include "score/time/HighPrecisionLocalSteadyClock/details/system_clock/system_clock.h"

#include <gtest/gtest.h>
#include <thread>

namespace score
{
namespace time
{
namespace details
{
namespace sys_time
{
namespace test
{

class TestSystemClock : public ::testing::Test
{
};

TEST_F(TestSystemClock, TimePointIsNotNegative)
{
    RecordProperty("Description",
                   "This test verifies if HighPrecisionLocalSteadyClock::Now() is not returning negative hours and the "
                   "clock is increasing");
    RecordProperty("Verifies", "::score::time::details::HighPrecisionLocalSteadyClock::Now()");
    RecordProperty("TestType", "Interface test");
    RecordProperty("DerivationTechnique", "Error guessing based on knowledge or experience");
    RecordProperty("ASIL", "QM");

    SystemClock system_clock;
    const auto time_point = system_clock.Now();

    // Verify if hours is not negative
    ASSERT_GE(time_point.time_since_epoch().count(), 0);

    std::this_thread::sleep_for(std::chrono::milliseconds{50});

    EXPECT_GT(system_clock.Now(), time_point);
}

}  // namespace test
}  // namespace sys_time
}  // namespace details
}  // namespace time
}  // namespace score
