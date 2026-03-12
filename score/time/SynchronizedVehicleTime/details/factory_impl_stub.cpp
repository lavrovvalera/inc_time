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
#include "score/time/SynchronizedVehicleTime/details/factory_impl.h"
#include "score/time/SynchronizedVehicleTime/details/factory_mock_helper.h"

namespace score
{
namespace time
{

std::shared_ptr<SynchronizedVehicleTime> SynchronizedVehicleTime::FactoryImpl::ObtainSynchronizedSlaveTimebase() const
{
    return SynchronizedVehicleTimeStaticFactoryMock::Get().ObtainSynchronizedSlaveTimebase();
}

}  // namespace time
}  // namespace score
