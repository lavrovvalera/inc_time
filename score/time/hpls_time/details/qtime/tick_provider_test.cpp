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
#include "score/time/hpls_time/details/qtime/tick_provider.h"

#include <gtest/gtest.h>

namespace score
{
namespace time
{
namespace hpls_time
{
namespace qtime
{
namespace test
{

TEST(TickProviderTest, GetClockCyclesPerSecReturnsPositiveValue)
{
    RecordProperty("Description", "Verifies that GetClockCyclesPerSec() returns a positive value on QNX.");
    RecordProperty("Verifies", "score::time::hpls_time::qtime::GetClockCyclesPerSec()");
    RecordProperty("TestType", "Interface test");
    RecordProperty("DerivationTechnique", "Error guessing based on knowledge or experience");
    RecordProperty("ASIL", "QM");

    EXPECT_GT(GetClockCyclesPerSec(), 0U);
}

}  // namespace test
}  // namespace qtime
}  // namespace hpls_time
}  // namespace time
}  // namespace score
