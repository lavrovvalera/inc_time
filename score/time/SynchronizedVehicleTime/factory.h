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
#ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_FACTORY_H
#define SCORE_TIME_SYNCHRONIZEDVEHICLETIME_FACTORY_H

#include "score/time/SynchronizedVehicleTime/synchronized_vehicle_time.h"

#include <memory>
#include <string>

namespace score
{
namespace time
{
///
/// \brief Interface class for factory providing SynchronizedVehicleTime objects.
///
class SynchronizedVehicleTime::Factory
{
  protected:
    constexpr Factory() noexcept = default;
    constexpr Factory(Factory&&) noexcept = default;
    constexpr Factory(const Factory&) noexcept = default;
    Factory& operator=(Factory&&) & noexcept = default;
    Factory& operator=(const Factory&) & noexcept = default;

  public:
    virtual ~Factory() noexcept;

    /// \brief Method for obtaining access to the pre-configured slave timebase which takes care of continously
    ///        receiving the latest value of Synchronized Vehicle Time (not necessarily, but for example: via PTP).
    ///
    /// \return shared_ptr to the SynchronizedVehicleTime object
    ///
    virtual std::shared_ptr<SynchronizedVehicleTime> ObtainSynchronizedSlaveTimebase() const = 0;
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_FACTORY_H
