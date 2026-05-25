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
#ifndef SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_H
#define SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_H

#include "score/time/hpls_time/src/hpls_time.h"
#include "score/time/clock/src/clock.h"
#include "score/time/clock/src/clock_snapshot.h"
#include "score/time/clock/src/no_status.h"


namespace score
{
namespace time
{

class HplsClockBackend;

template <>
struct ClockTraits<HplsTime>
{
    using Backend        = HplsClockBackend;
    using Duration       = HplsTime::Duration;
    using Timepoint      = HplsTime::Timepoint;
    using Snapshot       = ClockSnapshot<Timepoint, NoStatus>;

    /// \brief Obtains the current HPLS clock snapshot from the backend.
    static Snapshot CallNow(const Backend& impl) noexcept;
};

using HplsClock = Clock<HplsTime>;
using HplsTimePoint = ClockTraits<HplsTime>::Timepoint;
using HplsSnapshot = ClockTraits<HplsTime>::Snapshot;

}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_H
