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
#include "score/time/SynchronizedVehicleTime/slave_timebase_notification_types.h"
#include "score/time/SynchronizedVehicleTime/synchronized_vehicle_time.h"

#include <gtest/gtest.h>

#include <chrono>
#include <sstream>

namespace score
{
namespace time
{
namespace
{

using namespace std::chrono_literals;

class TestSynchronizedSlaveTimebaseTypes : public ::testing::Test
{
  public:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSynchronizedSlaveTimebaseTypes, TimeSlaveSyncDataPrintToStream)
{
    std::ostringstream os;

    // Given the following TimeSlaveSyncData
    TimeSlaveSyncData<SynchronizedVehicleTime> sync_data{SynchronizedVehicleTime::Timepoint{123ns},
                                                         SynchronizedVehicleTime::Timepoint{456ns},
                                                         LocalPTPDeviceTimerValue{789ns},
                                                         LocalPTPDeviceTimerValue{123ns},
                                                         45,
                                                         67,
                                                         89ns,
                                                         {12345, 6789}};

    // When printing it to an output stream via PrintTo()
    PrintTo(sync_data, &os);

    // Then the stringstream must contain the following content
    EXPECT_STREQ("[123, 456, 789, 123, 45 / 0x10000, 67, 89, (12345, 6789)]", os.str().c_str());
}

TEST_F(TestSynchronizedSlaveTimebaseTypes, TimeSlaveSyncDataOperatorToStream)
{
    std::stringstream os;

    // Given the following TimeSlaveSyncData
    TimeSlaveSyncData<SynchronizedVehicleTime> sync_data{SynchronizedVehicleTime::Timepoint{123ns},
                                                         SynchronizedVehicleTime::Timepoint{456ns},
                                                         LocalPTPDeviceTimerValue{789ns},
                                                         LocalPTPDeviceTimerValue{123ns},
                                                         45,
                                                         67,
                                                         89ns,
                                                         {12345, 6789}};

    // When printing it to an output stream via operator<<
    os << sync_data;

    // Then the stringstream must contain the following content
    EXPECT_STREQ("[123, 456, 789, 123, 45 / 0x10000, 67, 89, (12345, 6789)]", os.str().c_str());
}

TEST_F(TestSynchronizedSlaveTimebaseTypes, PDelayMeasurementDataPrintToStream)
{
    std::ostringstream os;

    // Given the following PDelayMeasurement
    PDelayMeasurementData<SynchronizedVehicleTime> pdelay_data{LocalPTPDeviceTimerValue{12ns},
                                                               MasterPTPDeviceTimerValue{34ns},
                                                               MasterPTPDeviceTimerValue{56ns},
                                                               LocalPTPDeviceTimerValue{78ns},
                                                               SynchronizedVehicleTime::Timepoint{90ns},
                                                               LocalPTPDeviceTimerValue{123ns},
                                                               456,
                                                               789ns,
                                                               {123, 45},
                                                               {678, 90}};

    // When printing it to an output stream via PrintTo()
    PrintTo(pdelay_data, &os);

    // Then the stringstream must contain the following content
    EXPECT_STREQ("[12, 34, 56, 78, 90, 123, 456, 789, (123, 45), (678, 90)]", os.str().c_str());
}

TEST_F(TestSynchronizedSlaveTimebaseTypes, PDelayMeasurementDataOperatorToStream)
{
    std::stringstream os;

    // Given the following PDelayMeasurementData
    PDelayMeasurementData<SynchronizedVehicleTime> pdelay_data{LocalPTPDeviceTimerValue{12ns},
                                                               MasterPTPDeviceTimerValue{34ns},
                                                               MasterPTPDeviceTimerValue{56ns},
                                                               LocalPTPDeviceTimerValue{78ns},
                                                               SynchronizedVehicleTime::Timepoint{90ns},
                                                               LocalPTPDeviceTimerValue{123ns},
                                                               456,
                                                               789ns,
                                                               {123, 45},
                                                               {678, 90}};

    // When printing it to an output stream via operator<<
    os << pdelay_data;

    // Then the stringstream must contain the following content
    EXPECT_STREQ("[12, 34, 56, 78, 90, 123, 456, 789, (123, 45), (678, 90)]", os.str().c_str());
}

}  // namespace
}  // namespace time
}  // namespace score
