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
#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/tick_provider.h"

#include <gtest/gtest.h>

namespace score
{
namespace time
{
namespace details
{
namespace test
{

using namespace ::testing;

TEST(TickProviderTest, GetClockCyclesPerSec)
{
    RecordProperty("Description", "This test verifies whether the GetClockCyclesPerSec returns a valid value");
    RecordProperty("Verifies", "score::time::details::qtime::GetClockCyclesPerSec()");
    RecordProperty("TestType", "Interface test");
    RecordProperty("DerivationTechnique", "Error guessing based on knowledge or experience");
    RecordProperty("ASIL", "QM");
    RecordProperty("Priority", "3");

    EXPECT_TRUE(score::time::details::qtime::GetClockCyclesPerSec() > 0);
}

}  // namespace test
}  // namespace details
}  // namespace time
}  // namespace score
