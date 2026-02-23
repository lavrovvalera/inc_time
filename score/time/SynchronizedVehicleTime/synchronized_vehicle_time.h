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
#ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SYNCHRONIZED_VEHICLE_TIME_H
#define SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SYNCHRONIZED_VEHICLE_TIME_H

#include "score/time/SynchronizedVehicleTime/slave_timebase_notification_types.h"

#include "score/time/common/time_base_status.h"

#include <amp_callback.hpp>
#include <score/stop_token.hpp>

#include <chrono>

namespace score
{
namespace time
{

///
/// \brief Interface definition for the Synchronized Vehicle Time (not necessarily, but for example: received via PTP).
///
class SynchronizedVehicleTime
{
  public:
    ///
    /// \brief Enumeration that is used to express the state of a time base.
    /// Each label represents a flag in the status bitfields of a timebase.
    ///
    enum class StatusFlag : StatusFlagType
    {
        kTimeOut = 0x0,        /*!< TB was not synchronized within a certain time frame. */
        kSynchronized = 0x1,   /*!< The TB was synchronized at least once. */
        kSynchToGateway = 0x2, /*!< The TB is in sync with the gateway. */
        kTimeLeapFuture = 0x3, /*!< An adjustment greater than a certain threshold has been made */
        kTimeLeapPast = 0x4,   /*!< An adjustment back in time greater than a certain threshold has been made */
        kUnknown = 0x7         /*!< Unknown status */
    };

    class Factory;         // mockable, lightweight interface
    class FactoryImpl;     // actual implementation which links the configured timesync stack, cf. directory 'details'
    class FactoryShmImpl;  // shm implementation which links the introduced shared memory implementation fot testing
                           // purpose
    using Duration = std::chrono::nanoseconds;
    using Timepoint = std::chrono::time_point<SynchronizedVehicleTime, Duration>;
    using TimepointStatus = TimeBaseStatus<StatusFlag>;

    using rep = Duration::rep;
    using period = Duration::period;
    using time_point = Timepoint;

    constexpr static std::uint64_t kCallbackCapacity{64U};
    using TimeSlaveSyncDataReceivedCallback =
        amp::callback<void(const TimeSlaveSyncData<SynchronizedVehicleTime>&), kCallbackCapacity>;
    using PDelayMeasurementFinishedCallback =
        amp::callback<void(const PDelayMeasurementData<SynchronizedVehicleTime>&), kCallbackCapacity>;

    constexpr SynchronizedVehicleTime() noexcept = default;
    SynchronizedVehicleTime& operator=(const SynchronizedVehicleTime&) & noexcept = delete;
    SynchronizedVehicleTime& operator=(SynchronizedVehicleTime&&) & noexcept = delete;
    SynchronizedVehicleTime(const SynchronizedVehicleTime&) noexcept = delete;
    SynchronizedVehicleTime(SynchronizedVehicleTime&&) noexcept = delete;
    virtual ~SynchronizedVehicleTime() noexcept;
    class TimeStatus
    {
      public:
        TimeStatus() noexcept : TimeStatus(std::chrono::nanoseconds{0}, StatusFlag::kUnknown) {}

        TimeStatus(const Timepoint& tp, const TimepointStatus& ts) : current_time_{tp}, time_base_status_{ts} {}

        TimeStatus(uint64_t tp, StatusFlag ts) : current_time_{std::chrono::nanoseconds{tp}}, time_base_status_{ts} {}

        TimeStatus(std::chrono::nanoseconds tp, StatusFlag ts) : current_time_{tp}, time_base_status_{ts} {}

        TimeStatus(const TimeStatus& orig) = default;

        TimeStatus& operator=(const TimeStatus& orig) noexcept
        {
            if (this != &orig)
            {
                current_time_ = orig.current_time_;
                time_base_status_ = orig.time_base_status_;
            }

            return *this;
        }

        TimeStatus& operator=(TimeStatus&&) noexcept = default;

        TimeStatus(TimeStatus&&) noexcept = default;

        ~TimeStatus() = default;

        [[nodiscard]] const Timepoint& getTimepoint() const
        {
            return current_time_;
        }

        TimeStatus& operator+=(const Duration& duration_to_add)
        {
            current_time_ = current_time_ + duration_to_add;
            return *this;
        }

        void setTimepoint(const Timepoint& tp) noexcept
        {
            current_time_ = tp;
        }

        void setTimepoint(Timepoint&& tp) noexcept
        {
            current_time_ = std::move(tp);
        }

        [[nodiscard]] const TimepointStatus& getTimepointStatus() const
        {
            return time_base_status_;
        }

        // Added the non const getter as this object is passed as parameter to function for modifying the values.
        [[nodiscard]] TimepointStatus& getTimepointStatus()
        {
            return time_base_status_;
        }

        Timepoint current_time_;
        TimepointStatus time_base_status_;
    };

    /// \brief Method for attempting to initialize the SynchronizedVehicleTime's resource.
    ///        The operation is non-blocking and does not perform any retry.
    ///        Function is thread safe.
    ///
    /// \return true in case the SynchronizedVehicleTime's resource is available, false otherwise
    ///
    virtual bool IsAvailable() const = 0;

    /// \brief Method for waiting until the SynchronizedVehicleTime's resource is available.
    ///
    /// \param token stop_token for interrupting this wait operation from outside
    /// \param until timepoint until to wait
    ///
    /// \return true in case the SynchronizedVehicleTime's resource is available, false otherwise
    ///
    virtual bool WaitUntilAvailable(const amp::stop_token& token,
                                    const std::chrono::time_point<std::chrono::steady_clock> until) const = 0;

    /// \brief Method for setting the callback to be invoked upon retrieval of new time sync data for this timebase.
    ///
    /// \param callback the callback to be invoked
    ///
    virtual void SetTimeSlaveSyncDataReceivedCallback(TimeSlaveSyncDataReceivedCallback&& callback) noexcept = 0;

    /// \brief Method for unsetting the callback to be invoked upon retrieval of new time sync data for this timebase.
    ///
    virtual void UnsetTimeSlaveSyncDataReceivedCallback() noexcept = 0;

    /// \brief Method for setting the validation callback to be invoked after a finished pdelay measurement.
    ///
    /// \param callback the callback to be invoked
    ///
    virtual void SetPDelayMeasurementFinishedCallback(PDelayMeasurementFinishedCallback&& callback) noexcept = 0;

    /// \brief Method for unsetting the callback to be invoked when this timebase finishes a pdelay measurement.
    ///
    virtual void UnsetPDelayMeasurementFinishedCallback() noexcept = 0;

    /// \brief Method for obtaining the current clock value of the underlying timebase (e.g. ara::tsync::SynchSlaveTB)
    /// combined with timebase status.
    ///
    /// \return current clock value of the underlying timebase
    ///
    virtual TimeStatus Now() noexcept = 0;

    /// \brief Method for obtaining the current deviation rate of the underlying timebase
    ///
    /// \return rate of deviation of the underlying timebase
    ///
    virtual double GetRateDeviation() noexcept = 0;
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SYNCHRONIZED_VEHICLE_TIME_H
