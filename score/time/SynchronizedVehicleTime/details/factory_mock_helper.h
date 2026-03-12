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
#include "score/time/SynchronizedVehicleTime/factory_mock.h"

namespace score
{
namespace time
{

struct SynchronizedVehicleTimeStaticFactoryMock
{
    ///
    /// \brief Implementation to obtain static Factory mock in case dependency injection is not used, but when the
    /// factory object is
    ///        used directly and there is a need to mock ObtainSynchronizedSlaveTimebase() and inject
    ///        SynchronizedVehicleTimeMock implicitly. This is not recommended to use! Instead use dependency injection
    ///        pattern.
    ///
    static SynchronizedVehicleTimeFactoryMock& Get()
    {
        static SynchronizedVehicleTimeFactoryMock factory;
        return factory;
    }
};

}  // namespace time
}  // namespace score
