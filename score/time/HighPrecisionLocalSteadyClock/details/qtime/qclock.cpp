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
#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/qclock.h"

#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/tick_provider.h"

#include "score/lib/os/qnx/neutrino.h"

namespace score
{
namespace time
{
namespace details
{
namespace qtime
{

HighPrecisionLocalSteadyClock::time_point QClock::Now() noexcept
{
    return HighPrecisionLocalSteadyClock::time_point{
        ClockCyclesToNanoseconds(score:os::qnx::Neutrino::instance().ClockCycles())};
}

std::chrono::nanoseconds QClock::ClockCyclesToNanoseconds(const std::uint64_t clock_cycles) const noexcept
{
    const std::uint64_t cycles_per_sec = GetClockCyclesPerSec();
    std::chrono::nanoseconds converted_thicks{0};

    if (cycles_per_sec > 0U)
    {
        constexpr auto billion = static_cast<std::uint64_t>(std::nano::den);
        constexpr auto max_value = static_cast<std::uint64_t>(std::chrono::nanoseconds::max().count());
        constexpr std::uint64_t upper_bound{max_value / billion};
        const std::uint64_t division_result{clock_cycles / cycles_per_sec};
        const std::uint64_t division_rest{clock_cycles % cycles_per_sec};
        if ((division_result <= upper_bound) && (division_rest <= upper_bound))
        {
            converted_thicks =
                std::chrono::nanoseconds{division_result * billion + division_rest * billion / cycles_per_sec};
        }
    }

    return converted_thicks;
}

}  // namespace qtime
}  // namespace details
}  // namespace time
}  // namespace score
