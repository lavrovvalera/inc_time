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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_SYSTEMCLOCK_SYSTEMCLOCK_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_SYSTEMCLOCK_SYSTEMCLOCK_H

#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock.h"

namespace score
{
namespace time
{
namespace details
{
namespace sys_time
{

///
/// \brief The class represents quasi-realtime clock that offers nanosecond resolution in PLP format.
///
class SystemClock final : public ::score::time::HighPrecisionLocalSteadyClock
{
  public:
    SystemClock() noexcept;
    SystemClock& operator=(const SystemClock&) noexcept = delete;
    SystemClock& operator=(SystemClock&&) noexcept = delete;
    SystemClock(const SystemClock&) noexcept = delete;
    SystemClock(SystemClock&&) noexcept = delete;
    ~SystemClock() noexcept override;

    /// \brief Method for obtaining the current clock value of the HPLSC.
    ///
    /// \details overrides ::score::time::HighPrecisionLocalSteadyClock::Now()
    ///
    /// \return current clock value and its status of the underlying timebase
    ///
    time_point Now() noexcept override;
};

}  // namespace sys_time
}  // namespace details
}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_SYSTEMCLOCK_SYSTEMCLOCK_H
