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
#ifndef SCORE_TIME_CLOCK_CLOCK_OVERRIDE_GUARD_H
#define SCORE_TIME_CLOCK_CLOCK_OVERRIDE_GUARD_H

#include "score/time/clock/clock.h"
#include "score/time/clock/clock_traits.h"

#include <memory>

namespace score
{
namespace time
{

/// @brief RAII guard that installs a test-double backend for @c Clock<Tag>.
///
/// On construction calls @c Clock<Tag>::OverrideForTest(); on destruction calls
/// @c Clock<Tag>::ResetOverride().
///
/// Properties:
///   - Move-only (non-copyable, move-assignment deleted).
///   - Non-re-entrant: nesting two guards for the same @c Tag is a logic error
///     and is caught by an assertion inside @c OverrideForTest().
///   - Scope-bound: the guard must not be interleaved with another guard of the
///     same @c Tag within the same process.
///
/// Usage:
/// @code
///     auto mock = std::make_shared<ClockMock<VehicleTime>>();
///     {
///         ClockOverrideGuard<VehicleTime> guard{mock};
///         MySvc svc{};  // GetInstance() returns mock
///         svc.DoSomething();
///     }  // ResetOverride() called here automatically
/// @endcode
template <typename Tag>
class ClockOverrideGuard final
{
    using Backend = typename ClockTraits<Tag>::Backend;

  public:
    /// @brief Installs @p impl as the test backend for @c Clock<Tag>.
    explicit ClockOverrideGuard(std::shared_ptr<Backend> impl) noexcept : active_{true}
    {
        Clock<Tag>::OverrideForTest(std::move(impl));
    }

    ~ClockOverrideGuard() noexcept
    {
        if (active_)
        {
            Clock<Tag>::ResetOverride();
        }
    }

    ClockOverrideGuard(const ClockOverrideGuard&)            = delete;
    ClockOverrideGuard& operator=(const ClockOverrideGuard&) = delete;

    ClockOverrideGuard(ClockOverrideGuard&& other) noexcept : active_{other.active_}
    {
        other.active_ = false;
    }

    ClockOverrideGuard& operator=(ClockOverrideGuard&&) = delete;

  private:
    bool active_;
};

}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_CLOCK_CLOCK_OVERRIDE_GUARD_H
