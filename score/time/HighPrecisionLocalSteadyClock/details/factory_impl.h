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
#ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_FACTORY_IMPL_H
#define SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_FACTORY_IMPL_H

#include "score/time/HighPrecisionLocalSteadyClock/factory.h"
#include "score/time/HighPrecisionLocalSteadyClock/high_precision_local_steady_clock.h"

namespace score
{
namespace time
{

///
/// \brief Implementation of score::time::HighPrecisionLocalSteadyClock::Factory which provides
/// score::time::HighPrecisionLocalSteadyClock objects.
///
class HighPrecisionLocalSteadyClock::FactoryImpl final : public score::time::HighPrecisionLocalSteadyClock::Factory
{
  public:
    constexpr FactoryImpl() noexcept = default;
    FactoryImpl(FactoryImpl&&) noexcept = delete;
    FactoryImpl(const FactoryImpl&) noexcept = delete;
    FactoryImpl& operator=(FactoryImpl&&) noexcept = delete;
    FactoryImpl& operator=(const FactoryImpl&) noexcept = delete;
    ~FactoryImpl() noexcept override = default;

    std::unique_ptr<HighPrecisionLocalSteadyClock> CreateHighPrecisionLocalSteadyClock() const override;
};

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_HIGHPRECISIONLOCALSTEADYCLOCK_DETAILS_FACTORY_IMPL_H
