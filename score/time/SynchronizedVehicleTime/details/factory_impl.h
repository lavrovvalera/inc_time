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
#ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_DETAILS_FACTORY_IMPL_H
#define SCORE_TIME_SYNCHRONIZEDVEHICLETIME_DETAILS_FACTORY_IMPL_H

#include "score/time/SynchronizedVehicleTime/factory.h"

#include <memory>
#include <mutex>

namespace score
{
namespace time
{

///
/// \brief Implementation of score::time::SynchronizedVehicleTime::Factory which provides
///        the configured implementation objects for score::time::SynchronizedVehicleTime.
///        Such configuration is contained in the BUILD file.
///
class SynchronizedVehicleTime::FactoryImpl final : public SynchronizedVehicleTime::Factory
{
  public:
    FactoryImpl() noexcept = default;
    FactoryImpl(FactoryImpl&&) noexcept = delete;
    FactoryImpl(const FactoryImpl&) noexcept = delete;
    FactoryImpl& operator=(FactoryImpl&&) & noexcept = delete;
    FactoryImpl& operator=(const FactoryImpl&) & noexcept = delete;
    ~FactoryImpl() noexcept final = default;

    std::shared_ptr<SynchronizedVehicleTime> ObtainSynchronizedSlaveTimebase() const override;

  private:
    mutable std::weak_ptr<SynchronizedVehicleTime> weak_timebase_instance_;
    mutable std::mutex mutex_;
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_DETAILS_FACTORY_IMPL_H
