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
#ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_FACTORY_MOCK_H
#define SCORE_TIME_SYNCHRONIZEDVEHICLETIME_FACTORY_MOCK_H

#include "score/time/SynchronizedVehicleTime/factory.h"

#include <gmock/gmock.h>

namespace score
{
namespace time
{

///
/// \brief Mock class for factory providing SynchronizedVehicleTime objects.
///
class SynchronizedVehicleTimeFactoryMock : public SynchronizedVehicleTime::Factory
{
  public:
    SynchronizedVehicleTimeFactoryMock();
    SynchronizedVehicleTimeFactoryMock(SynchronizedVehicleTimeFactoryMock&&) noexcept = delete;
    SynchronizedVehicleTimeFactoryMock(const SynchronizedVehicleTimeFactoryMock&) noexcept = delete;
    SynchronizedVehicleTimeFactoryMock& operator=(SynchronizedVehicleTimeFactoryMock&&) noexcept = delete;
    SynchronizedVehicleTimeFactoryMock& operator=(const SynchronizedVehicleTimeFactoryMock&) noexcept = delete;
    virtual ~SynchronizedVehicleTimeFactoryMock() noexcept;

    MOCK_METHOD(std::shared_ptr<SynchronizedVehicleTime>, ObtainSynchronizedSlaveTimebase, (), (const, override));
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_FACTORY_MOCK_H
