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
#ifndef SCORE_TIME_HPLS_TIME_DETAILS_HPLSCIMPL_QTIME_HPLS_QCLOCK_H
#define SCORE_TIME_HPLS_TIME_DETAILS_HPLSCIMPL_QTIME_HPLS_QCLOCK_H

#include "score/time/hpls_time/hpls_clock_iface.h"
#include "score/time/clock/no_status.h"

#include <cstdint>

namespace score
{
namespace time
{
namespace hpls_time
{
namespace qtime
{

///
/// \brief QNX production backend for HplsTime.
///
/// Reads the current time from the QNX hardware clock via @c Neutrino::ClockCycles()
/// and converts the raw cycle count to nanoseconds using @c GetClockCyclesPerSec().
///
class HplsQClock final : public HplsClockIface
{
  public:
    HplsQClock() noexcept                          = default;
    HplsQClock(const HplsQClock&) noexcept         = delete;
    HplsQClock& operator=(const HplsQClock&)       = delete;
    HplsQClock(HplsQClock&&) noexcept              = delete;
    HplsQClock& operator=(HplsQClock&&)            = delete;
    ~HplsQClock() noexcept override                = default;

    /// \brief Returns the current HPLS snapshot from the QNX hardware clock.
    ClockSnapshot<HplsTime::Timepoint, NoStatus> Now() const noexcept override;

  private:
    /// \brief Converts raw hardware clock cycles to nanoseconds.
    std::chrono::nanoseconds ClockCyclesToNanoseconds(std::uint64_t clock_cycles) const noexcept;
};

}  // namespace qtime
}  // namespace hpls_time
}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_HPLS_TIME_DETAILS_QTIME_HPLS_QCLOCK_H
