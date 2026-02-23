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
#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/tick_provider.h"

#include <sys/syspage.h>

namespace score
{
namespace time
{
namespace details
{
namespace qtime
{

std::uint64_t GetClockCyclesPerSec()
{
    return static_cast<std::uint64_t>(SYSPAGE_ENTRY(qtime)->cycles_per_sec);
}

}  // namespace qtime
}  // namespace details
}  // namespace time
}  // namespace score
