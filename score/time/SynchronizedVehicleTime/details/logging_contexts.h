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
#ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_DETAILS_LOGGING_CONTEXTS_H
#define SCORE_TIME_SYNCHRONIZEDVEHICLETIME_DETAILS_LOGGING_CONTEXTS_H

#include <string>

namespace score
{
namespace time
{
namespace details
{

// Main logging Context
constexpr auto kSvtMainLogContext = "MSVT";
// Logging context dedicated for printing statistics
constexpr auto kSvtStatisticsLogContext = "SVTS";

}  // namespace details
}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_SYNCHRONIZEDVEHICLETIME_DETAILS_LOGGING_CONTEXTS_H
