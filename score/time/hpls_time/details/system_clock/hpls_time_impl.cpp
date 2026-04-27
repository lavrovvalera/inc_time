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
#include "score/time/hpls_time/details/system_clock/hpls_time_impl.h"

#include "score/time/hpls_time/hpls_time.h"
#include "score/time/hpls_time/hpls_clock.h"

#include <chrono>
#include <memory>

namespace score
{
namespace time
{
namespace hpls_time
{
namespace sys_time
{

HplsTimeImpl::HplsTimeImpl() noexcept  = default;
HplsTimeImpl::~HplsTimeImpl() noexcept = default;

ClockSnapshot<HplsTime::Timepoint, NoStatus> HplsTimeImpl::Now() const noexcept
{
    const auto raw = std::chrono::high_resolution_clock::now().time_since_epoch();
    const HplsTime::Timepoint tp{std::chrono::duration_cast<HplsTime::Duration>(raw)};
    return ClockSnapshot<HplsTime::Timepoint, NoStatus>{tp, NoStatus{}};
}

}  // namespace sys_time
}  // namespace hpls_time

template <>
std::shared_ptr<HplsClockIface> detail::CreateBackend<HplsTime>()
{
    return std::make_shared<hpls_time::sys_time::HplsTimeImpl>();
}

}  // namespace time
}  // namespace score
