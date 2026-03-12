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
#include "score/time/HighPrecisionLocalSteadyClock/details/factory_impl.h"
#include "score/time/HighPrecisionLocalSteadyClock/details/qtime/qclock.h"

namespace score
{
namespace time
{

std::unique_ptr<HighPrecisionLocalSteadyClock>
HighPrecisionLocalSteadyClock::FactoryImpl::CreateHighPrecisionLocalSteadyClock() const
{
    return std::make_unique<score::time::details::qtime::QClock>();
}

}  // namespace time
}  // namespace score
