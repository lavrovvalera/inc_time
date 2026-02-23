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
#include "score/time/HighPrecisionLocalSteadyClock/details/factory_impl.h"
#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/qclock.h"

#include <gtest/gtest.h>

namespace score
{
namespace time
{
namespace details
{
namespace qtime
{
namespace
{

TEST(TestFactory, Destruction)
{
    RecordProperty("Description",
                   "This test verifies different variants of object construction and destruction for the factory");
    RecordProperty("Verifies", "score::time::HighPrecisionLocalSteadyClock::Factory");
    RecordProperty("TestType", "Interface test");
    RecordProperty("DerivationTechnique", "Error guessing based on knowledge or experience");
    RecordProperty("ASIL", "QM");
    RecordProperty("Priority", "3");

    // Given an instance via base-class pointer
    std::unique_ptr<score::time::HighPrecisionLocalSteadyClock::Factory> factory_base =
        std::make_unique<HighPrecisionLocalSteadyClock::FactoryImpl>();
    // When being reset
    factory_base.reset();
    // Then it gets destructed

    // Given an instance via direct pointer
    auto factory_impl = std::make_unique<HighPrecisionLocalSteadyClock::FactoryImpl>();
    // When being reset
    factory_impl.reset();
    // Then it gets destructed

    {
        // Given an instance via object on stack
        HighPrecisionLocalSteadyClock::FactoryImpl factory;
        // When going out of scope
        (void)factory;
    }
    // Then it gets destructed
}

TEST(TestFactory, CreateHighPrecisionLocalSteadyClock)
{
    RecordProperty("Description",
                   "This test verifies that the HighPrecisionLocalSteadyClock object is created from the factory ");
    RecordProperty("Verifies",
                   "score::time::HighPrecisionLocalSteadyClock::FactoryImpl::CreateHighPrecisionLocalSteadyClock()");
    RecordProperty("TestType", "Interface test");
    RecordProperty("DerivationTechnique", "Error guessing based on knowledge or experience");
    RecordProperty("ASIL", "QM");
    RecordProperty("Priority", "3");

    // Given a Factory instance
    HighPrecisionLocalSteadyClock::FactoryImpl factory;

    // When CreateHighPrecisionLocalSteadyClock() gets called
    auto first_instance = factory.CreateHighPrecisionLocalSteadyClock();

    // Then a valid HighPrecisionLocalSteadyClock must be returned
    ASSERT_NE(nullptr, first_instance);

    // Which must be of type qtime::QClock
    ASSERT_NE(nullptr, dynamic_cast<QClock*>(first_instance.get()));
}

}  // namespace
}  // namespace qtime
}  // namespace details
}  // namespace time
}  // namespace score
