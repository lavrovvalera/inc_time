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
#include "score/time/SynchronizedVehicleTime/details/clock_realtime/clock_provider.h"

#include "score/time/HighPrecisionLocalSteadyClock/details/factory_impl.h"

namespace score
{
namespace time
{
namespace details
{
namespace clock_realtime
{

using namespace std::chrono_literals;

ClockProvider::ClockProvider(std::unique_ptr<HighPrecisionLocalSteadyClock> high_precision_clock) noexcept
    : high_precision_clock_{std::move(high_precision_clock)}
{
}

bool ClockProvider::WaitUntilAvailable(const amp::stop_token& /* token */,
                                       const std::chrono::time_point<std::chrono::steady_clock> /* until */) const
{
    return true;
}

bool ClockProvider::IsAvailable() const
{
    return true;
}

void ClockProvider::SetTimeSlaveSyncDataReceivedCallback(TimeSlaveSyncDataReceivedCallback&& /* callback */) noexcept {}

void ClockProvider::UnsetTimeSlaveSyncDataReceivedCallback() noexcept {}

void ClockProvider::SetPDelayMeasurementFinishedCallback(PDelayMeasurementFinishedCallback&& /* callback */) noexcept {}

void ClockProvider::UnsetPDelayMeasurementFinishedCallback() noexcept {}

SynchronizedVehicleTime::TimeStatus ClockProvider::Now() noexcept
{
    const SynchronizedVehicleTime::Timepoint converted_time{
        std::chrono::duration_cast<SynchronizedVehicleTime::Timepoint::duration>(
            high_precision_clock_->Now().time_since_epoch())};

    return {converted_time, TimepointStatus{SynchronizedVehicleTime::StatusFlag::kSynchronized}};
}

double ClockProvider::GetRateDeviation() noexcept
{
    return 0.0;
}

}  // namespace clock_realtime
}  // namespace details
}  // namespace time
}  // namespace score
