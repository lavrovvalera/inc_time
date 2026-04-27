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
#ifndef SCORE_TIME_HPLS_TIME_DETAILS_SYSTEMCLOCK_HPLS_TIME_IMPL_H
#define SCORE_TIME_HPLS_TIME_DETAILS_SYSTEMCLOCK_HPLS_TIME_IMPL_H

#include "score/time/hpls_time/hpls_clock_iface.h"
#include "score/time/clock/no_status.h"

namespace score
{
namespace time
{
namespace hpls_time
{
namespace sys_time
{

///
/// \brief Production HplsTime backend for non-QNX platforms.
///
/// Reads the current time from @c std::chrono::high_resolution_clock and
/// converts it to an @c HplsTime::Timepoint.
///
class HplsTimeImpl final : public HplsClockIface
{
  public:
    HplsTimeImpl() noexcept;
    HplsTimeImpl(const HplsTimeImpl&) noexcept            = delete;
    HplsTimeImpl& operator=(const HplsTimeImpl&) noexcept = delete;
    HplsTimeImpl(HplsTimeImpl&&) noexcept                 = delete;
    HplsTimeImpl& operator=(HplsTimeImpl&&) noexcept      = delete;
    ~HplsTimeImpl() noexcept override;

    /// \brief Returns the current HPLS snapshot using @c high_resolution_clock.
    ClockSnapshot<HplsTime::Timepoint, NoStatus> Now() const noexcept override;
};

}  // namespace sys_time
}  // namespace hpls_time
}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_HPLS_TIME_DETAILS_SYSTEMCLOCK_HPLS_TIME_IMPL_H
