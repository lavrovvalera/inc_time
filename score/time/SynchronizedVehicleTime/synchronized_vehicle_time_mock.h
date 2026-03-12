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
#ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SYNCHRONIZED_VEHICLE_TIME_MOCK_H
#define SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SYNCHRONIZED_VEHICLE_TIME_MOCK_H

#include "score/time/SynchronizedVehicleTime/synchronized_vehicle_time.h"

#include <gmock/gmock.h>

namespace score
{
namespace time
{

///
/// \brief Class mocking the functionality of SynchronizedVehicleTime.
///
class SynchronizedVehicleTimeMock : public SynchronizedVehicleTime
{
  public:
    SynchronizedVehicleTimeMock();
    SynchronizedVehicleTimeMock& operator=(const SynchronizedVehicleTimeMock&) noexcept = delete;
    SynchronizedVehicleTimeMock& operator=(SynchronizedVehicleTimeMock&&) noexcept = delete;
    SynchronizedVehicleTimeMock(const SynchronizedVehicleTimeMock&) noexcept = delete;
    SynchronizedVehicleTimeMock(SynchronizedVehicleTimeMock&&) noexcept = delete;
    virtual ~SynchronizedVehicleTimeMock() noexcept;

    MOCK_METHOD(bool,
                WaitUntilAvailable,
                (const score::cpp::stop_token& token, const std::chrono::time_point<std::chrono::steady_clock> until),
                (const, override));

    MOCK_METHOD(bool, IsAvailable, (), (const, override));

    MOCK_METHOD(void,
                SetTimeSlaveSyncDataReceivedCallback,
                (TimeSlaveSyncDataReceivedCallback && callback),
                (noexcept, override));
    MOCK_METHOD(void, UnsetTimeSlaveSyncDataReceivedCallback, (), (noexcept, override));

    MOCK_METHOD(void,
                SetPDelayMeasurementFinishedCallback,
                (PDelayMeasurementFinishedCallback && callback),
                (noexcept, override));
    MOCK_METHOD(void, UnsetPDelayMeasurementFinishedCallback, (), (noexcept, override));

    MOCK_METHOD(TimeStatus, Now, (), (noexcept, override));

    MOCK_METHOD(double, GetRateDeviation, (), (noexcept, override));
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SYNCHRONIZED_VEHICLE_TIME_MOCK_H
