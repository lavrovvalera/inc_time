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
#include "score/time/common/time_base_status.h"
#include "score/time/SynchronizedVehicleTime/synchronized_vehicle_time.h"

#include <gtest/gtest.h>

#include <type_traits>

namespace score
{
namespace time
{
namespace test
{

class TestTimeBaseStatusImplForSVT : public ::testing::Test
{
};

TEST_F(TestTimeBaseStatusImplForSVT, IsSynchronizedReturnsTrueIfCorrectFlagsSet)
{
    // Create TimeBaseStatus object without active status flags
    TimeBaseStatus<SynchronizedVehicleTime::StatusFlag> time_base_status{};

    // Check that it should not be synchronized
    EXPECT_FALSE(time_base_status.IsSynchronized());

    // Append all flags from SynchronizedVehicleTime except kSynchronized and kTimeOut
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchToGateway);
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kUnknown);
    // Then status should not be synchronized
    EXPECT_FALSE(time_base_status.IsSynchronized());

    // Append kSynchronized status flag and verify IsSynchronized() returns true
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchronized);
    EXPECT_TRUE(time_base_status.IsSynchronized());

    // Then after adding kTimeOut TimeBaseStatus should not be in synchronized state
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeOut);
    EXPECT_FALSE(time_base_status.IsSynchronized());
}

TEST_F(TestTimeBaseStatusImplForSVT, IsValidReturnsTrueIfCorrectFlagsSetWithLeapPast)
{
    // Create TimeBaseStatus object without active status flags
    TimeBaseStatus<SynchronizedVehicleTime::StatusFlag> time_base_status{};
    // no flag is set: expect status invalid
    EXPECT_FALSE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchToGateway);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchronized);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeLeapPast);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeOut);
    EXPECT_TRUE(time_base_status.IsValid());
}

TEST_F(TestTimeBaseStatusImplForSVT, IsValidReturnsTrueIfCorrectFlagsSetWithLeapFuture)
{
    // Create TimeBaseStatus object without active status flags
    TimeBaseStatus<SynchronizedVehicleTime::StatusFlag> time_base_status{};
    // no flag is set: expect status invalid
    EXPECT_FALSE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchToGateway);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchronized);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeLeapFuture);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeOut);
    EXPECT_TRUE(time_base_status.IsValid());
}

TEST_F(TestTimeBaseStatusImplForSVT, IsValidReturnsFalseForUnknownFlag)
{
    // Create TimeBaseStatus object without active status flags
    TimeBaseStatus<SynchronizedVehicleTime::StatusFlag> time_base_status{};
    // no flag is set: expect status invalid
    EXPECT_FALSE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchToGateway);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchronized);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeLeapPast);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeOut);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append Unknown flag, isValid shall return false
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kUnknown);
    EXPECT_FALSE(time_base_status.IsValid());
}

TEST_F(TestTimeBaseStatusImplForSVT, IsValidReturnsFalseForLeapFlags)
{
    // Create TimeBaseStatus object without active status flags
    TimeBaseStatus<SynchronizedVehicleTime::StatusFlag> time_base_status{};
    // no flag is set: expect status invalid
    EXPECT_FALSE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchToGateway);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append one flag and verify that TimeBaseStatus should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kSynchronized);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeLeapPast);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append more flags and verify that TimeBaseStatus still should be valid
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeOut);
    EXPECT_TRUE(time_base_status.IsValid());

    // Append another leap flag, isValid shall return false
    time_base_status.AddFlag(SynchronizedVehicleTime::StatusFlag::kTimeLeapFuture);
    EXPECT_FALSE(time_base_status.IsValid());
}

TEST_F(TestTimeBaseStatusImplForSVT, TimeBaseStatusIsPrintedInCorrectFormat)
{
    // Create TimeBaseStatus object
    TimeBaseStatus<SynchronizedVehicleTime::StatusFlag> time_base_status{SynchronizedVehicleTime::StatusFlag::kSynchToGateway};

    // Create output stream object and print TimeBaseStatus using << operator
    std::ostringstream os;
    os << time_base_status;

    // Verify correct flags are set to true and output log has correct format
    EXPECT_STREQ(
        "[kTimeOut: false, kSynchronized: false, kSynchToGateway: true, kTimeLeapFuture: false, kTimeLeapPast: false, "
        "kUnknown: false, ]",
        os.str().c_str());
}

}  // namespace test
}  // namespace time
}  // namespace score
