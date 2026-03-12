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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_QTIME_QCLOCK_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_QTIME_QCLOCK_H

#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock.h"

namespace score
{
namespace time
{
namespace details
{
namespace qtime
{

///
/// \brief The class represents quasi-realtime clock that offers nanosecond resolution in PLP format.
///
class QClock final : public ::score::time::HighPrecisionLocalSteadyClock
{
  public:
    QClock() noexcept = default;
    QClock& operator=(const QClock&) noexcept = delete;
    QClock& operator=(QClock&&) noexcept = delete;
    QClock(const QClock&) noexcept = delete;
    QClock(QClock&&) noexcept = delete;
    ~QClock() noexcept override = default;

    /// \brief Method for obtaining the current clock value of the HPLSC.
    ///
    /// \details overrides ::score::time::HighPrecisionLocalSteadyClock::Now()
    ///
    /// \return current clock value and its status of the underlying timebase
    ///
    time_point Now() noexcept override;

  private:
    std::chrono::nanoseconds ClockCyclesToNanoseconds(const std::uint64_t clock_cycles) const noexcept;
};

}  // namespace qtime
}  // namespace details
}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_QTIME_QCLOCK_H
