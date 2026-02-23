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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_FACTORY_MOCK_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_FACTORY_MOCK_H

#include "score/time/HighPrecisionLocalSteadyClock/factory.h"

#include <gmock/gmock.h>

namespace score
{
namespace time
{

///
/// \brief Mock class for factory providing HighPrecisionLocalSteadyClock objects.
///
class HighPrecisionLocalSteadyClockFactoryMock : public HighPrecisionLocalSteadyClock::Factory
{
  public:
    HighPrecisionLocalSteadyClockFactoryMock();
    HighPrecisionLocalSteadyClockFactoryMock(HighPrecisionLocalSteadyClockFactoryMock&&) noexcept = delete;
    HighPrecisionLocalSteadyClockFactoryMock(const HighPrecisionLocalSteadyClockFactoryMock&) noexcept = delete;
    HighPrecisionLocalSteadyClockFactoryMock& operator=(HighPrecisionLocalSteadyClockFactoryMock&&) noexcept = delete;
    HighPrecisionLocalSteadyClockFactoryMock& operator=(const HighPrecisionLocalSteadyClockFactoryMock&) noexcept =
        delete;
    virtual ~HighPrecisionLocalSteadyClockFactoryMock() noexcept;

    MOCK_METHOD(std::unique_ptr<HighPrecisionLocalSteadyClock>,
                CreateHighPrecisionLocalSteadyClock,
                (),
                (const, override));
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_FACTORY_MOCK_H
