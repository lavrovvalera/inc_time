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
#ifndef SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_BACKEND_H
#define SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_BACKEND_H

#include "score/time/hpls_time/src/hpls_time.h"
#include "score/time/clock/src/clock_snapshot.h"
#include "score/time/clock/src/no_status.h"

namespace score
{
namespace time
{

///
/// \brief Pure-virtual pimpl interface for the HPLSC time domain backend.
class HplsClockBackend
{
  public:
    virtual ~HplsClockBackend() noexcept = default;

    /// \brief Returns the current HPLSC snapshot (time-point; status is NoStatus).
    virtual ClockSnapshot<HplsTime::Timepoint, NoStatus> Now() const noexcept = 0;
};

}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_BACKEND_H
