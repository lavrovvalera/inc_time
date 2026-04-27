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
#include "score/time/steady_time/details/stub_impl/steady_clock_impl.h"
#include "score/time/steady_time/steady_clock.h"

#include <memory>

namespace score
{
namespace time
{

template <>
std::shared_ptr<SteadyClockIface> detail::CreateBackend<std::chrono::steady_clock>()
{
    return std::make_shared<detail::SteadyClockImpl>();
}

}  // namespace time
}  // namespace score
