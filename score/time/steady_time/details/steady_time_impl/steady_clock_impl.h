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
#ifndef SCORE_TIME_STEADY_TIME_DETAILS_STEADY_TIME_IMPL_STEADY_CLOCK_IMPL_H
#define SCORE_TIME_STEADY_TIME_DETAILS_STEADY_TIME_IMPL_STEADY_CLOCK_IMPL_H

// Internal header — include ONLY from steady_time_impl/steady_clock_impl.cpp.

#include "score/time/steady_time/steady_clock_iface.h"
#include "score/time/clock/no_status.h"

#include <chrono>

namespace score
{
namespace time
{
namespace detail
{

/// @brief Production backend for the steady-clock domain.
///
/// Delegates directly to std::chrono::steady_clock::now().
class SteadyClockImpl final : public SteadyClockIface
{
  public:
    SteadyClockImpl() noexcept                           = default;
    ~SteadyClockImpl() noexcept override                 = default;
    SteadyClockImpl(const SteadyClockImpl&)              = delete;
    SteadyClockImpl& operator=(const SteadyClockImpl&)   = delete;
    SteadyClockImpl(SteadyClockImpl&&)                   = delete;
    SteadyClockImpl& operator=(SteadyClockImpl&&)        = delete;

    ClockSnapshot<std::chrono::steady_clock::time_point, NoStatus> Now() const noexcept override
    {
        return ClockSnapshot<std::chrono::steady_clock::time_point, NoStatus>{
            std::chrono::steady_clock::now(), NoStatus{}};
    }
};

}  // namespace detail
}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_STEADY_TIME_DETAILS_STEADY_TIME_IMPL_STEADY_CLOCK_IMPL_H
