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
#include "score/time/SynchronizedVehicleTime/details/factory_impl.h"

#include "score/time/SynchronizedVehicleTime/details/tdr/receiver.h"

#include <gtest/gtest.h>

namespace score
{
namespace time
{
namespace
{

class TestFactoryImpl : public ::testing::Test
{
};

TEST_F(TestFactoryImpl, Destruction)
{
    // Given an instance via base-class pointer
    std::unique_ptr<SynchronizedVehicleTime::FactoryImpl> factory_base =
        std::make_unique<SynchronizedVehicleTime::FactoryImpl>();
    // When being reset
    factory_base.reset();
    // Then it gets destructed

    // Given an instance via direct pointer
    auto factory_impl = std::make_unique<SynchronizedVehicleTime::FactoryImpl>();
    // When being reset
    factory_impl.reset();
    // Then it gets destructed

    {
        // Given an instance via object on stack
        SynchronizedVehicleTime::FactoryImpl factory;
        // When going out of scope
        (void)factory;
    }
    // Then it gets destructed
}

TEST_F(TestFactoryImpl, ObtainSynchronizedSlaveTimebase)
{
    // Given a FactoryImpl instance
    SynchronizedVehicleTime::FactoryImpl factory;

    // When ObtainSynchronizedSlaveTimebase() gets called
        // Then the returned object must be of type `score::time::details::tdr::Receiver`
        ASSERT_NE(dynamic_cast<details::tdr::Receiver*>(factory.ObtainSynchronizedSlaveTimebase().get()),
              nullptr)
        << "Obtained object from SynchronizedVehicleTime::FactoryImpl is not of type "
            "score::time::details::tdr::Receiver!";
}

TEST_F(TestFactoryImpl, ObtainSynchronizedSlaveTimebaseMultipleTimes)
{
    // Given a FactoryShmImpl instance
    SynchronizedVehicleTime::FactoryImpl factory;

    // When ObtainSynchronizedSlaveTimebase() gets called multiple times
    auto first = factory.ObtainSynchronizedSlaveTimebase();
    auto second = factory.ObtainSynchronizedSlaveTimebase();

    // Then both instances contains the same pointer
    ASSERT_TRUE(first == second);
}

}  // namespace
}  // namespace time
}  // namespace score
