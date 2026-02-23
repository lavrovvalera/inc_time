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
#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/qclock.h"

#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/tick_provider_mock.h"

#include "score/lib/os/mocklib/qnx/neutrino_qnx_mock.h"

#include <gtest/gtest.h>

#include "score/time/HighPrecisionLocalSteadyClock/details/factory_impl.h"
#include <gmock/gmock.h>

namespace score
{
namespace time
{
namespace details
{
namespace test
{

using namespace ::testing;

struct TestCaseParams
{
    uint64_t tickCount{};
    uint64_t tickPerSec{};
    uint64_t tickInNano{};

    friend void PrintTo(const TestCaseParams& point, std::ostream* os)
    {
        *os << "In-params: " << point.tickCount << ", " << point.tickPerSec << ", " << point.tickInNano;
    }
};

class HighPrecisionLocalSteadyClock : public ::testing::TestWithParam<TestCaseParams>
{
  public:
    using TickProviderMock = score::time::details::qtime::TickProviderMock;

    void SetUp() override
    {
        TickProviderMock::CreateMockInstance();
    }

    void TearDown() override
    {
        TickProviderMock::DestroyMockInstance();
    }
};

INSTANTIATE_TEST_SUITE_P(HighPrecisionLocalSteadyClockInstantiate,
                         HighPrecisionLocalSteadyClock,
                         ::testing::Values(
                             // TestCaseParams (inTimePoint, tickPerSec, tickInNano)
                             // Zero ticks
                             TestCaseParams{0, 19'200'000, 0},

                             // Some values
                             TestCaseParams{3'462'637'232, 19'200'000, 180'345'689'166},

                             // overflow test:
                             // ClockCycles at 960s ~= 2361000000 * 960 = 2,266,560,000,000
                             TestCaseParams{2'266'560'000'000, 2'361'000'000, 960'000'000'000},

                             // 1 hour ~  3.600.000.277.053 nano ~ 8.499.600.000.000 ticks
                             TestCaseParams{8'499'600'654'123, 2'361'000'000, 3'600'000'277'053},

                             // 24 hours ~ 203990415698952 ticks
                             TestCaseParams{203'990'415'698'952, 2'361'000'000, 86'400'006'649'280},

                             // 48 hours ~ 407980831397904 ticks
                             TestCaseParams{407'980'831'397'904, 2'361'000'000, 172'800'013'298'561},

                             // 96 hours ~ 815.961.662.795.808 ticks
                             TestCaseParams{815'961'662'795'808, 2'361'000'000, 345'600'026'597'123},

                             // 22 days ~ 4'503'599'627'370'495 ticks
                             TestCaseParams{0x000FFFFFFFFFFFFF, 2'361'000'000, 1'907'496'665'552'941},

                             // 353 days ~ 18'446'744'073'709'551'615 ticks
                             TestCaseParams{0x00FFFFFFFFFFFFFF, 2'361'000'000, 30'519'946'648'847'071},

                             // 15 years ~ 295'147'905'179'352'825'855 ticks
                             TestCaseParams{0x0FFFFFFFFFFFFFFF, 2'361'000'000, 488'319'146'381'553'144},

                             // 247 years ~  4'722'366'482'869'645'213'695 ticks
                             TestCaseParams{0xFFFFFFFFFFFFFFFF, 2'361'000'000, 7'813'106'342'104'850'324},

                             // boundry conditions check
                             TestCaseParams{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 1000000000},

                             // when result overflow it will return 0
                             TestCaseParams{0xFFFFFFFFFFFFFFFF, 1, 0},
                             TestCaseParams{0xFFFFFFFFFFFFFFFF, 1'000'000'000, 0},
                             TestCaseParams{0xFFFFFFFFF, 1, 0},

                             // Zero tick per sec
                             TestCaseParams{3462637232, 0, 0}));

TEST_P(HighPrecisionLocalSteadyClock, TimePointIsNotNegative)
{
    RecordProperty("Description",
                   "This test verifies if HighPrecisionLocalSteadyClock::Now() returns tick in nanoseconds"
                   "based on equation: time point in nano = tick count * 1e9 / tick per second");
    RecordProperty("Verifies", "28819169, 28823471");
    RecordProperty("TestType", "Requirements-based test");
    RecordProperty("DerivationTechnique", "Analysis of requirements");
    RecordProperty("ASIL", "QM");
    RecordProperty("Priority", "3");

    const auto params{GetParam()};

    score:os::qnx::NeutrinoMock neutrinoMock;
    score:os::qnx::Neutrino::set_testing_instance(neutrinoMock);

    EXPECT_CALL(neutrinoMock, ClockCycles()).Times(Exactly(1)).WillOnce(Return(params.tickCount));

    EXPECT_CALL(TickProviderMock::GetMockInstance(), GetClockCyclesPerSec())
        .Times(Exactly(1))
        .WillOnce(Return(params.tickPerSec));

    std::unique_ptr<score::time::HighPrecisionLocalSteadyClock> qclock =
        std::make_unique<score::time::details::qtime::QClock>();
    const auto time_point = qclock->Now();

    EXPECT_EQ(params.tickInNano, time_point.time_since_epoch().count());
}

TEST(HighPrecisionLocalSteadyClock, WhenClockCyclesFailToProvideValidValueShouldReturnZero)
{
    RecordProperty("Description",
                   "This test performs fault injection by simulating Neutrino::ClockCycles() returning zero "
                   "to verify that HighPrecisionLocalSteadyClock::Now() handles the system call failure gracefully "
                   "and returns a valid non-negative time point");
    RecordProperty("Verifies", "score::time::HighPrecisionLocalSteadyClock::Now()");
    RecordProperty("TestType", "Fault injection test");
    RecordProperty("DerivationTechnique", "Error guessing based on knowledge or experience");
    RecordProperty("ASIL", "QM");
    RecordProperty("Priority", "3");

    // Define constants
    constexpr uint64_t FAILURE = 0;
    constexpr uint64_t MINIMAL_VALID_CLOCK_CYCLES_PER_SEC = 10;

    using FactoryImpl = score::time::HighPrecisionLocalSteadyClock::FactoryImpl;
    using QClock = score::time::details::qtime::QClock;
    using TickProviderMock = score::time::details::qtime::TickProviderMock;

    TickProviderMock::CreateMockInstance();
    auto& tickProvider = TickProviderMock::GetMockInstance();

    score:os::qnx::NeutrinoMock neutrinoMock;
    score:os::qnx::Neutrino::set_testing_instance(neutrinoMock);

    // Simulate ClockCycles() failure → returns 0
    EXPECT_CALL(neutrinoMock, ClockCycles()).WillOnce(Return(FAILURE));
    EXPECT_CALL(tickProvider, GetClockCyclesPerSec()).WillOnce(Return(MINIMAL_VALID_CLOCK_CYCLES_PER_SEC));

    FactoryImpl factory{};
    auto clock = factory.CreateHighPrecisionLocalSteadyClock();
    ASSERT_NE(clock, nullptr);

    auto qclock = dynamic_cast<QClock*>(clock.get());
    ASSERT_NE(qclock, nullptr);

    auto time_point = qclock->Now();
    EXPECT_EQ(time_point.time_since_epoch().count(), 0U);

    TickProviderMock::DestroyMockInstance();
}

TEST(HighPrecisionLocalSteadyClock, WhenClockCyclesProvideValidValueShouldReturnValidTimePoint)
{
    // Define constants
    constexpr uint64_t VALID_CLOCK_CYCLES_PER_SECOND = 100;
    constexpr uint64_t VALID_CLOCK_CYCLES = 25;

    using FactoryImpl = score::time::HighPrecisionLocalSteadyClock::FactoryImpl;
    using QClock = score::time::details::qtime::QClock;
    using TickProviderMock = score::time::details::qtime::TickProviderMock;

    // Create TickProviderMock singleton instance
    TickProviderMock::CreateMockInstance();
    auto& tickProvider = TickProviderMock::GetMockInstance();

    // Create NeutrinoMock to simulate system ClockCycles() API
    score:os::qnx::NeutrinoMock neutrinoMock;
    score:os::qnx::Neutrino::set_testing_instance(neutrinoMock);

    // Set expectations for TickProviderMock and NeutrinoMock
    EXPECT_CALL(tickProvider, GetClockCyclesPerSec()).WillOnce(Return(VALID_CLOCK_CYCLES_PER_SECOND));
    EXPECT_CALL(neutrinoMock, ClockCycles()).WillOnce(Return(VALID_CLOCK_CYCLES));

    // Get concrete factory implementation and create the clock
    FactoryImpl factory{};
    auto clock = factory.CreateHighPrecisionLocalSteadyClock();
    ASSERT_NE(clock, nullptr);

    auto qclock = dynamic_cast<QClock*>(clock.get());
    ASSERT_NE(qclock, nullptr);

    // Call Now() and verify tick count to nanoseconds conversion
    auto time_point = qclock->Now();
    EXPECT_EQ(time_point.time_since_epoch().count(),
              VALID_CLOCK_CYCLES * 1'000'000'000U / VALID_CLOCK_CYCLES_PER_SECOND);

    // Destroy TickProviderMock to clean up singleton state
    TickProviderMock::DestroyMockInstance();
}

}  // namespace test
}  // namespace details
}  // namespace time
}  // namespace score
