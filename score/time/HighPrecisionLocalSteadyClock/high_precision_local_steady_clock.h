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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_HIGH_PRECISION_LOCAL_STEADY_CLOCK_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_HIGH_PRECISION_LOCAL_STEADY_CLOCK_H

#include <chrono>

namespace score
{
namespace time
{

///
/// \brief Interface definition for HighPrecisionLocalSteadyClock functionality.
///
class HighPrecisionLocalSteadyClock
{
  public:
    class Factory;      // mockable, lightweight interface
    class FactoryImpl;  // actual implementation which links the configured HPLSC, cf. directory 'details'

    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<HighPrecisionLocalSteadyClock, duration>;

    HighPrecisionLocalSteadyClock() noexcept;
    HighPrecisionLocalSteadyClock& operator=(const HighPrecisionLocalSteadyClock&) noexcept = delete;
    HighPrecisionLocalSteadyClock& operator=(HighPrecisionLocalSteadyClock&&) noexcept = delete;
    HighPrecisionLocalSteadyClock(const HighPrecisionLocalSteadyClock&) noexcept = delete;
    HighPrecisionLocalSteadyClock(HighPrecisionLocalSteadyClock&&) noexcept = delete;
    virtual ~HighPrecisionLocalSteadyClock() noexcept;

    /// \brief Method for obtaining the current clock value of the underlying timebase.
    ///
    /// \return current clock value of the underlying timebase
    ///
    virtual time_point Now() noexcept = 0;
};

}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_HIGH_PRECISION_LOCAL_STEADY_CLOCK_H
