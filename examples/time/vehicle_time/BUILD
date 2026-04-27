# *******************************************************************************
# Copyright (c) 2026 Contributors to the Eclipse Foundation
#
# See the NOTICE file(s) distributed with this work for additional
# information regarding copyright ownership.
#
# This program and the accompanying materials are made available under the
# terms of the Apache License Version 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0
#
# SPDX-License-Identifier: Apache-2.0
# *******************************************************************************

load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")
load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")

# Library containing only the testable business-logic — no main(), no signal handling.
cc_library(
    name = "time_handler",
    hdrs = ["vehicle_time_handler.h"],
    features = COMPILER_WARNING_FEATURES,
    deps = [
        "//score/time/hpls_time:interface",
        "//score/time/vehicle_time:interface",
    ],
)

# Example binary: reads VehicleTime + HplsTime once per second and prints a combined report.
#
# Run with:
#   bazel run //examples/time/vehicle_time
#
# The production VehicleTime backend (TimeDaemon TDR receiver) is pulled in via
# //score/time/vehicle_time:vehicle_time.  On a development host that backend will
# return zero-valued snapshots with kTimeOut set — which is the expected behaviour
# when the TimeDaemon is not running.
cc_binary(
    name = "vehicle_time",
    srcs = ["main.cpp"],
    features = COMPILER_WARNING_FEATURES,
    deps = [
        ":time_handler",
        # Single entry point: brings in VehicleClock (vehicle_clock.h)
        # AND the production VehicleTime backend (CreateBackend<VehicleTime>()).
        "//score/time/vehicle_time",
        # VehicleTime's production backend uses HplsClock internally.
        # Provide its production backend so CreateBackend<HplsTime>() resolves at link time.
        "//score/time/hpls_time",
        # mw::log frontend is pulled in transitively via td_impl.
        # A binary must link exactly one concrete recorder implementation.
        "@score_baselibs//score/mw/log:console_only_backend",
    ],
)

# Unit test for the time handler: replaces both VehicleClock and HplsClock with mocks.
cc_test(
    name = "vehicle_time_handler_test",
    srcs = ["vehicle_time_handler_test.cpp"],
    features = COMPILER_WARNING_FEATURES,
    deps = [
        ":time_handler",
        "//score/time/hpls_time:hpls_time_mock",
        "//score/time/vehicle_time:vehicle_time_mock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "@score_baselibs//score/mw/log:console_only_backend",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [":vehicle_time_handler_test"],
    visibility = ["//examples/time:__pkg__"],
)
