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
#include "score/time/vehicle_time/vehicle_time.h"

#include <gtest/gtest.h>

#include <sstream>

namespace score
{
namespace time
{
namespace
{

using Flag = VehicleTime::StatusFlag;

class TestVehicleTimeStatus : public ::testing::Test
{
};

// ── IsSynchronized ────────────────────────────────────────────────────────────

TEST_F(TestVehicleTimeStatus, IsSynchronizedReturnsTrueOnlyWhenFlagSetWithoutErrorFlags)
{
    VehicleTimeStatus status{};
    EXPECT_FALSE(status.IsSynchronized());

    status.flags.AddFlag(Flag::kSynchToGateway);
    EXPECT_FALSE(status.IsSynchronized());

    status.flags.AddFlag(Flag::kSynchronized);
    EXPECT_TRUE(status.IsSynchronized());

    status.flags.AddFlag(Flag::kTimeOut);
    EXPECT_FALSE(status.IsSynchronized());
}

TEST_F(TestVehicleTimeStatus, IsSynchronizedReturnsFalseWhenTimeLeapFutureSet)
{
    VehicleTimeStatus status{};
    status.flags.AddFlag(Flag::kSynchronized);
    EXPECT_TRUE(status.IsSynchronized());

    status.flags.AddFlag(Flag::kTimeLeapFuture);
    EXPECT_FALSE(status.IsSynchronized());
}

TEST_F(TestVehicleTimeStatus, IsSynchronizedReturnsFalseWhenTimeLeapPastSet)
{
    VehicleTimeStatus status{};
    status.flags.AddFlag(Flag::kSynchronized);
    EXPECT_TRUE(status.IsSynchronized());

    status.flags.AddFlag(Flag::kTimeLeapPast);
    EXPECT_FALSE(status.IsSynchronized());
}

// ── IsValid ───────────────────────────────────────────────────────────────────

TEST_F(TestVehicleTimeStatus, IsValidReturnsFalseWhenNoFlagsSet)
{
    const VehicleTimeStatus status{};
    EXPECT_FALSE(status.IsValid());
}

TEST_F(TestVehicleTimeStatus, IsValidReturnsTrueWithSynchToGatewayAndSynchronized)
{
    VehicleTimeStatus status{};
    status.flags.AddFlag(Flag::kSynchToGateway);
    EXPECT_TRUE(status.IsValid());

    status.flags.AddFlag(Flag::kSynchronized);
    EXPECT_TRUE(status.IsValid());
}

TEST_F(TestVehicleTimeStatus, IsValidReturnsTrueWithLeapPastFlag)
{
    VehicleTimeStatus status{};
    status.flags.AddFlag(Flag::kSynchToGateway);
    status.flags.AddFlag(Flag::kSynchronized);
    EXPECT_TRUE(status.IsValid());

    status.flags.AddFlag(Flag::kTimeLeapPast);
    EXPECT_TRUE(status.IsValid());

    status.flags.AddFlag(Flag::kTimeOut);
    EXPECT_TRUE(status.IsValid());
}

TEST_F(TestVehicleTimeStatus, IsValidReturnsTrueWithLeapFutureFlag)
{
    VehicleTimeStatus status{};
    status.flags.AddFlag(Flag::kSynchToGateway);
    status.flags.AddFlag(Flag::kSynchronized);
    EXPECT_TRUE(status.IsValid());

    status.flags.AddFlag(Flag::kTimeLeapFuture);
    EXPECT_TRUE(status.IsValid());

    status.flags.AddFlag(Flag::kTimeOut);
    EXPECT_TRUE(status.IsValid());
}

TEST_F(TestVehicleTimeStatus, IsValidReturnsFalseWhenUnknownFlagSet)
{
    VehicleTimeStatus status{};
    status.flags.AddFlag(Flag::kSynchToGateway);
    status.flags.AddFlag(Flag::kSynchronized);
    status.flags.AddFlag(Flag::kTimeLeapPast);
    status.flags.AddFlag(Flag::kTimeOut);
    EXPECT_TRUE(status.IsValid());

    status.flags.AddFlag(Flag::kUnknown);
    EXPECT_FALSE(status.IsValid());
}

TEST_F(TestVehicleTimeStatus, IsValidReturnsFalseWhenBothLeapFlagsSet)
{
    VehicleTimeStatus status{};
    status.flags.AddFlag(Flag::kSynchToGateway);
    status.flags.AddFlag(Flag::kSynchronized);
    status.flags.AddFlag(Flag::kTimeLeapPast);
    EXPECT_TRUE(status.IsValid());

    status.flags.AddFlag(Flag::kTimeLeapFuture);
    EXPECT_FALSE(status.IsValid());
}

// ── PrintTo ───────────────────────────────────────────────────────────────────

TEST_F(TestVehicleTimeStatus, PrintToFormatsActiveFlagsCorrectly)
{
    ClockStatus<Flag> status{Flag::kSynchToGateway};

    std::ostringstream os;
    os << status;

    EXPECT_STREQ(
        "[kTimeOut: false, kSynchronized: false, kSynchToGateway: true, kTimeLeapFuture: false, "
        "kTimeLeapPast: false, kUnknown: false, ]",
        os.str().c_str());
}

// ── IsFlagActive convenience delegate ────────────────────────────────────────

TEST_F(TestVehicleTimeStatus, IsFlagActiveDelegatesCorrectly)
{
    VehicleTimeStatus status{};
    EXPECT_FALSE(status.IsFlagActive(Flag::kSynchronized));

    status.flags.AddFlag(Flag::kSynchronized);
    EXPECT_TRUE(status.IsFlagActive(Flag::kSynchronized));
    EXPECT_FALSE(status.IsFlagActive(Flag::kTimeOut));
}

}  // namespace
}  // namespace time
}  // namespace score
