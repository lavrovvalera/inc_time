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
#include "score/time/hpls_time/details/system_clock/hpls_time_impl.h"

#include <gtest/gtest.h>
#include <thread>

namespace score
{
namespace time
{
namespace hpls_time
{
namespace sys_time
{
namespace test
{

class HplsTimeImplTest : public ::testing::Test
{
};

TEST_F(HplsTimeImplTest, TimePointIsNotNegative)
{
    RecordProperty("Description",
                   "Verifies that HplsTimeImpl::Now() returns a non-negative time point "
                   "and that the clock is strictly monotonically increasing.");
    RecordProperty("Verifies", "score::time::hpls_time::sys_time::HplsTimeImpl::Now()");
    RecordProperty("TestType", "Interface test");
    RecordProperty("DerivationTechnique", "Error guessing based on knowledge or experience");
    RecordProperty("ASIL", "QM");

    HplsTimeImpl clock;
    const auto snapshot = clock.Now();

    ASSERT_GE(snapshot.TimePointNs().count(), 0);

    std::this_thread::sleep_for(std::chrono::milliseconds{50});

    EXPECT_GT(clock.Now().TimePoint(), snapshot.TimePoint());
}

}  // namespace test
}  // namespace sys_time
}  // namespace hpls_time
}  // namespace time
}  // namespace score
