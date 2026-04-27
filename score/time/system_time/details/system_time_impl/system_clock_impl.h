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
#ifndef SCORE_TIME_SYSTEM_TIME_DETAILS_SYSTEM_TIME_IMPL_SYSTEM_CLOCK_IMPL_H
#define SCORE_TIME_SYSTEM_TIME_DETAILS_SYSTEM_TIME_IMPL_SYSTEM_CLOCK_IMPL_H

// Internal header — include ONLY from system_time_impl/system_clock_impl.cpp.

#include "score/time/system_time/system_clock_iface.h"
#include "score/time/clock/no_status.h"

#include <chrono>

namespace score
{
namespace time
{
namespace detail
{

/// @brief Production backend for the system-clock domain.
///
/// Delegates directly to std::chrono::system_clock::now().
class SystemClockImpl final : public SystemClockIface
{
  public:
    SystemClockImpl() noexcept                           = default;
    ~SystemClockImpl() noexcept override                 = default;
    SystemClockImpl(const SystemClockImpl&)              = delete;
    SystemClockImpl& operator=(const SystemClockImpl&)   = delete;
    SystemClockImpl(SystemClockImpl&&)                   = delete;
    SystemClockImpl& operator=(SystemClockImpl&&)        = delete;

    ClockSnapshot<std::chrono::system_clock::time_point, NoStatus> Now() const noexcept override
    {
        return ClockSnapshot<std::chrono::system_clock::time_point, NoStatus>{
            std::chrono::system_clock::now(), NoStatus{}};
    }
};

}  // namespace detail
}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_SYSTEM_TIME_DETAILS_SYSTEM_TIME_IMPL_SYSTEM_CLOCK_IMPL_H
