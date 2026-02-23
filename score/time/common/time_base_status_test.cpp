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

#include <gtest/gtest.h>
#include <limits>

namespace score
{
namespace time
{

class TestTimeBaseStatus : public ::testing::Test
{
  public:
    enum class StatusFlag : StatusFlagType
    {
        kTimeOut = 0x0,
        kSynchronized = 0x1,
        kSynchToGateway = 0x2,
        kUnknown = 0x3
    };
};

TEST_F(TestTimeBaseStatus, ObjectCreatedFromFlagList)
{
    // Create TimeBaseStatus object
    TimeBaseStatus<StatusFlag> time_base_status{StatusFlag::kSynchronized, StatusFlag::kSynchToGateway};

    // Verify that correct flags are set to active
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive({StatusFlag::kTimeOut, StatusFlag::kUnknown}));
}

TEST_F(TestTimeBaseStatus, FlagsAppendedCorrectly)
{
    // Create TimeBaseStatus object
    TimeBaseStatus<StatusFlag> time_base_status{};

    // Verify that none of the flags should be active
    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive(
        {StatusFlag::kSynchToGateway, StatusFlag::kTimeOut, StatusFlag::kSynchronized, StatusFlag::kUnknown}));

    // Append status flags using AddFlag method and verify they are added correctly
    time_base_status.AddFlag(StatusFlag::kSynchToGateway);
    time_base_status.AddFlag(StatusFlag::kTimeOut);

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive({StatusFlag::kSynchronized, StatusFlag::kUnknown}));

    // Append status flags using AddFlag methods and verify they are added correctly
    time_base_status.AddFlag(StatusFlag::kUnknown);
    time_base_status.AddFlag(StatusFlag::kSynchronized);

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kUnknown));
}

TEST_F(TestTimeBaseStatus, FlagAppendedMoreThanOnce)
{
    // Create TimeBaseStatus object and verify that correct flag is set to active
    TimeBaseStatus<StatusFlag> time_base_status{StatusFlag::kSynchronized};
    EXPECT_FALSE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));

    // Append new flag twice
    time_base_status.AddFlag(StatusFlag::kSynchToGateway);
    time_base_status.AddFlag(StatusFlag::kSynchToGateway);

    // Verify correct flags are active despite adding kSynchToGateway twice
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive({StatusFlag::kTimeOut, StatusFlag::kUnknown}));

    // Append another status flag twice and verify flags
    time_base_status.AddFlag(StatusFlag::kTimeOut);
    time_base_status.AddFlag(StatusFlag::kTimeOut);

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_FALSE(time_base_status.IsFlagActive(StatusFlag::kUnknown));
}

TEST_F(TestTimeBaseStatus, StatusSerializedCorrectlyToFlagsContainer)
{
    // Create TimeBaseStatus object
    TimeBaseStatus<StatusFlag> time_base_status{StatusFlag::kSynchToGateway, StatusFlag::kTimeOut};

    // Create status container from TimeBaseStatus object
    const auto status_container = time_base_status.ToUnderlying();

    // Create TimeBaseStatus object and get active flags from status container
    TimeBaseStatus<StatusFlag> deserialized_status{};
    deserialized_status.FromUnderlying(status_container);

    // Check if correct flags are active
    EXPECT_TRUE(deserialized_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(deserialized_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_FALSE(deserialized_status.IsAnyOfFlagsActive({StatusFlag::kSynchronized, StatusFlag::kUnknown}));

    // Create TimeBaseObject status and get active flags from status container
    std::uint8_t max_container_uint8 = std::numeric_limits<uint8_t>::max();
    TimeBaseStatus<StatusFlag> status_uint8{};
    status_uint8.FromUnderlying(max_container_uint8);

    // Check if correct flags are active - all flags should be set to active
    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kUnknown));

    // Create TimeBaseObject status and get active flags from status container
    std::uint32_t max_container_uint32 = std::numeric_limits<uint32_t>::max();
    TimeBaseStatus<StatusFlag> status_uint32{};
    // Implicit conversion to uint8_t
    status_uint32.FromUnderlying(max_container_uint32);

    // Check if correct flags are active - all flags should be set to active
    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kUnknown));
}

TEST_F(TestTimeBaseStatus, StatusSerializedFromInvalidStatusFlagEnum)
{
    // Define StatusFlags with flags out of range
    enum class StatusFlagOutOfRange : StatusFlagType
    {
        kTimeOut = 0x0,
        kSynchronized = 0x1,
        kSynchToGateway = 200,
        kUnknown = 255
    };
    // Create TimeBaseStatus object
    TimeBaseStatus<StatusFlagOutOfRange> time_base_status{};

    // Add kSynchronized flag and verify it's active
    time_base_status.AddFlag(StatusFlagOutOfRange::kSynchronized);
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlagOutOfRange::kSynchronized));

    // Adding a flag should be terminated when trying to add out of range kSynchToGateway
    ASSERT_DEATH(time_base_status.AddFlag(StatusFlagOutOfRange::kSynchToGateway), "");

    // Add kTimeOut flag and verify it's active
    time_base_status.AddFlag(StatusFlagOutOfRange::kTimeOut);
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlagOutOfRange::kTimeOut));

    // Adding a flag should be terminated when trying to check if out of range kUnknown flag is active
    ASSERT_DEATH(time_base_status.IsFlagActive(StatusFlagOutOfRange::kUnknown), "");
}

}  // namespace time
}  // namespace score
