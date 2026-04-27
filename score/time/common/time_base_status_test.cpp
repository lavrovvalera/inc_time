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
    TimeBaseStatus<StatusFlag> time_base_status{StatusFlag::kSynchronized, StatusFlag::kSynchToGateway};

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive({StatusFlag::kTimeOut, StatusFlag::kUnknown}));
}

TEST_F(TestTimeBaseStatus, FlagsAppendedCorrectly)
{
    TimeBaseStatus<StatusFlag> time_base_status{};

    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive(
        {StatusFlag::kSynchToGateway, StatusFlag::kTimeOut, StatusFlag::kSynchronized, StatusFlag::kUnknown}));

    time_base_status.AddFlag(StatusFlag::kSynchToGateway);
    time_base_status.AddFlag(StatusFlag::kTimeOut);

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive({StatusFlag::kSynchronized, StatusFlag::kUnknown}));

    time_base_status.AddFlag(StatusFlag::kUnknown);
    time_base_status.AddFlag(StatusFlag::kSynchronized);

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kUnknown));
}

TEST_F(TestTimeBaseStatus, FlagAppendedMoreThanOnce)
{
    TimeBaseStatus<StatusFlag> time_base_status{StatusFlag::kSynchronized};
    EXPECT_FALSE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));

    time_base_status.AddFlag(StatusFlag::kSynchToGateway);
    time_base_status.AddFlag(StatusFlag::kSynchToGateway);

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_FALSE(time_base_status.IsAnyOfFlagsActive({StatusFlag::kTimeOut, StatusFlag::kUnknown}));

    time_base_status.AddFlag(StatusFlag::kTimeOut);
    time_base_status.AddFlag(StatusFlag::kTimeOut);

    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_FALSE(time_base_status.IsFlagActive(StatusFlag::kUnknown));
}

TEST_F(TestTimeBaseStatus, StatusSerializedCorrectlyToFlagsContainer)
{
    TimeBaseStatus<StatusFlag> time_base_status{StatusFlag::kSynchToGateway, StatusFlag::kTimeOut};
    const auto status_container = time_base_status.ToUnderlying();

    TimeBaseStatus<StatusFlag> deserialized_status{};
    deserialized_status.FromUnderlying(status_container);

    EXPECT_TRUE(deserialized_status.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(deserialized_status.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_FALSE(deserialized_status.IsAnyOfFlagsActive({StatusFlag::kSynchronized, StatusFlag::kUnknown}));

    std::uint8_t max_container_uint8 = std::numeric_limits<uint8_t>::max();
    TimeBaseStatus<StatusFlag> status_uint8{};
    status_uint8.FromUnderlying(max_container_uint8);

    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(status_uint8.IsFlagActive(StatusFlag::kUnknown));

    // FromUnderlying truncates to the underlying type (uint8_t) on narrowing.
    std::uint32_t max_container_uint32 = std::numeric_limits<uint32_t>::max();
    TimeBaseStatus<StatusFlag> status_uint32{};
    status_uint32.FromUnderlying(max_container_uint32);

    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kSynchToGateway));
    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kTimeOut));
    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kSynchronized));
    EXPECT_TRUE(status_uint32.IsFlagActive(StatusFlag::kUnknown));
}

TEST_F(TestTimeBaseStatus, StatusSerializedFromInvalidStatusFlagEnum)
{
    enum class StatusFlagOutOfRange : StatusFlagType
    {
        kTimeOut        = 0x0,
        kSynchronized   = 0x1,
        kSynchToGateway = 200,
        kUnknown        = 255
    };
    TimeBaseStatus<StatusFlagOutOfRange> time_base_status{};

    time_base_status.AddFlag(StatusFlagOutOfRange::kSynchronized);
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlagOutOfRange::kSynchronized));

    ASSERT_DEATH(time_base_status.AddFlag(StatusFlagOutOfRange::kSynchToGateway), "");

    time_base_status.AddFlag(StatusFlagOutOfRange::kTimeOut);
    EXPECT_TRUE(time_base_status.IsFlagActive(StatusFlagOutOfRange::kTimeOut));

    ASSERT_DEATH(time_base_status.IsFlagActive(StatusFlagOutOfRange::kUnknown), "");
}

}  // namespace time
}  // namespace score
