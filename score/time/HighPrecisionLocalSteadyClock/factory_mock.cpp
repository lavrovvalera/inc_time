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
#include "score/time/HighPrecisionLocalSteadyClock/factory_mock.h"

#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock_mock.h"

namespace score
{
namespace time
{

HighPrecisionLocalSteadyClockFactoryMock::HighPrecisionLocalSteadyClockFactoryMock()
{
    ON_CALL(*this, CreateHighPrecisionLocalSteadyClock()).WillByDefault(::testing::Invoke([]() {
        return std::make_unique<HighPrecisionLocalSteadyClockMock>();
    }));
}

HighPrecisionLocalSteadyClockFactoryMock::~HighPrecisionLocalSteadyClockFactoryMock() noexcept = default;

}  // namespace time
}  // namespace score
