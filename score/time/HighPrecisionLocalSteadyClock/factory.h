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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_FACTORY_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_FACTORY_H

#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock.h"

#include <memory>

namespace score
{
namespace time
{
///
/// \brief Interface class for factory providing HighPrecisionLocalSteadyClock objects.
///
class HighPrecisionLocalSteadyClock::Factory
{
  public:
    constexpr Factory() noexcept = default;
    constexpr Factory(Factory&&) noexcept = delete;
    constexpr Factory(const Factory&) noexcept = delete;
    constexpr Factory& operator=(Factory&&) & noexcept = delete;
    constexpr Factory& operator=(const Factory&) & noexcept = delete;
    virtual ~Factory() noexcept;

    /// \brief Method for obtaining access to the pre-configured timebase.
    ///
    /// \return unique_ptr to the HighPrecisionLocalSteadyClock object
    ///
    virtual std::unique_ptr<HighPrecisionLocalSteadyClock> CreateHighPrecisionLocalSteadyClock() const = 0;
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_FACTORY_H
