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
#ifndef SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_BACKEND_MOCK_H
#define SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_BACKEND_MOCK_H

#include "score/time/hpls_time/src/hpls_clock_backend.h"
#include "score/time/hpls_time/src/hpls_clock.h"
#include "score/time/clock/src/scoped_clock_override.h"
#include "score/time/clock/src/clock_test_factory.h"

#include <gmock/gmock.h>

namespace score
{
namespace time
{

/// @brief GMock test double for the HPLS clock domain.
///
/// Implements @c HplsClockBackend so it can be injected via
/// @c test_utils::ScopedClockOverride<HplsTime> or @c test_utils::ClockTestFactory<HplsTime> in unit tests.
///
/// Constructor injection (preferred — no global state):
/// @code
///   auto mock  = std::make_shared<HplsClockBackendMock>();
///   auto clock = test_utils::ClockTestFactory<HplsTime>::Make(mock);
///   MyComponent component{clock};
///   EXPECT_CALL(*mock, Now()).WillOnce(Return(...));
/// @endcode
///
/// Scope-bound override (when SUT calls @c GetInstance() internally):
/// @code
///   auto mock = std::make_shared<HplsClockBackendMock>();
///   test_utils::ScopedClockOverride<HplsTime> guard{mock};
///   MySvc svc{};
///   EXPECT_CALL(*mock, Now()).WillOnce(Return(...));
/// @endcode
class HplsClockBackendMock : public HplsClockBackend
{
  public:
    HplsClockBackendMock()                                    = default;
    ~HplsClockBackendMock() noexcept override                 = default;
    HplsClockBackendMock(const HplsClockBackendMock&)                = delete;
    HplsClockBackendMock& operator=(const HplsClockBackendMock&)     = delete;
    HplsClockBackendMock(HplsClockBackendMock&&)                     = delete;
    HplsClockBackendMock& operator=(HplsClockBackendMock&&)          = delete;

    MOCK_METHOD((ClockSnapshot<HplsTime::Timepoint, NoStatus>),
                Now,
                (),
                (const, noexcept, override));
};

}  // namespace time
}  // namespace score

#endif  // SCORE_TIME_HPLS_TIME_SRC_HPLS_CLOCK_BACKEND_MOCK_H
