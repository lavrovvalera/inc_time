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
#include "score/time/hpls_time/details/qtime/hpls_qclock.h"
#include "score/time/hpls_time/hpls_clock.h"

#include <gtest/gtest.h>

namespace score
{
namespace time
{
namespace hpls_time
{
namespace qtime
{
namespace
{

TEST(HplsQClockFactoryTest, CreateBackendReturnsNonNull)
{
    RecordProperty("Description",
                   "Verifies that detail::CreateBackend<HplsTime>() returns a valid shared_ptr.");
    RecordProperty("Verifies", "score::time::detail::CreateBackend<HplsTime>()");
    RecordProperty("TestType", "Interface test");
    RecordProperty("ASIL", "QM");

    auto backend = detail::CreateBackend<HplsTime>();
    ASSERT_NE(backend, nullptr);
}

TEST(HplsQClockFactoryTest, CreateBackendReturnsHplsQClock)
{
    RecordProperty("Description",
                   "Verifies that detail::CreateBackend<HplsTime>() returns an HplsQClock instance.");
    RecordProperty("ASIL", "QM");

    auto backend = detail::CreateBackend<HplsTime>();
    ASSERT_NE(backend, nullptr);
    EXPECT_NE(dynamic_cast<HplsQClock*>(backend.get()), nullptr);
}

}  // namespace
}  // namespace qtime
}  // namespace hpls_time
}  // namespace time
}  // namespace score
