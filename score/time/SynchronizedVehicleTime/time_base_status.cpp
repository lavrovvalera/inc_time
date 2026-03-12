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
#include "score/time/SynchronizedVehicleTime/synchronized_vehicle_time.h"

#include <map>
#include <sstream>

namespace score
{
namespace time
{

/// \brief Specialization for method TimeBaseStatus<>::IsSynchronized()
template <>
bool TimeBaseStatus<SynchronizedVehicleTime::StatusFlag>::IsSynchronized() const
{
    return (IsFlagActive(SynchronizedVehicleTime::StatusFlag::kSynchronized) and
            (not(IsAnyOfFlagsActive({SynchronizedVehicleTime::StatusFlag::kTimeOut,
                                     SynchronizedVehicleTime::StatusFlag::kTimeLeapFuture,
                                     SynchronizedVehicleTime::StatusFlag::kTimeLeapPast}))));
}

/// \brief Specialization for method TimeBaseStatus<>::IsValid()
template <>
bool TimeBaseStatus<SynchronizedVehicleTime::StatusFlag>::IsValid() const
{
    bool is_valid{false};

    if ((not(IsFlagActive(SynchronizedVehicleTime::StatusFlag::kUnknown))) &&
        (IsAnyOfFlagsActive({SynchronizedVehicleTime::StatusFlag::kTimeOut,
                             SynchronizedVehicleTime::StatusFlag::kSynchronized,
                             SynchronizedVehicleTime::StatusFlag::kSynchToGateway,
                             SynchronizedVehicleTime::StatusFlag::kTimeLeapFuture,
                             SynchronizedVehicleTime::StatusFlag::kTimeLeapPast})))
    {
        if (not((IsFlagActive(SynchronizedVehicleTime::StatusFlag::kTimeLeapFuture)) and
                (IsFlagActive(SynchronizedVehicleTime::StatusFlag::kTimeLeapPast))))
        {
            // kUnknown flag is not set, and both leaps flags are not set
            is_valid = true;
        }
    }

    return is_valid;
}

namespace
{
/// \brief Map of all statuses and strings
const std::map<SynchronizedVehicleTime::StatusFlag, std::string> status_flag_base = {
    {SynchronizedVehicleTime::StatusFlag::kTimeOut, "kTimeOut"},
    {SynchronizedVehicleTime::StatusFlag::kSynchronized, "kSynchronized"},
    {SynchronizedVehicleTime::StatusFlag::kSynchToGateway, "kSynchToGateway"},
    {SynchronizedVehicleTime::StatusFlag::kTimeLeapFuture, "kTimeLeapFuture"},
    {SynchronizedVehicleTime::StatusFlag::kTimeLeapPast, "kTimeLeapPast"},
    {SynchronizedVehicleTime::StatusFlag::kUnknown, "kUnknown"}};
}  // namespace

/// \brief Specialization for method TimeBaseStatus<>::PrintTo()
template <>
std::ostringstream TimeBaseStatus<SynchronizedVehicleTime::StatusFlag>::PrintTo() const
{
    std::ostringstream output_stream;
    output_stream << "[";
    std::string isActive{""};
    for (const auto& flag : status_flag_base)
    {
        isActive = IsFlagActive(flag.first) ? "true" : "false";
        output_stream << flag.second << ": ";
        output_stream << isActive;
        output_stream << ", ";
    }
    output_stream << "]";

    return output_stream;
}

}  // namespace time
}  // namespace score
