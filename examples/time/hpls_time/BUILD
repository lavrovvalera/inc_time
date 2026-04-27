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
    hdrs = ["hpls_time_handler.h"],
    features = COMPILER_WARNING_FEATURES,
    deps = [
        "//score/time/hpls_time:interface",
    ],
)

# Example binary: reads HplsTime once per second and prints the snapshot to stdout.
#
# Run with:
#   bazel run //examples/time/hpls_time
#
# HplsTime wraps a local monotonic hardware clock (high_resolution_clock on Linux,
# ClockCycles() on QNX) and has no synchronisation-quality concept, so the snapshot
# carries only a time-point.
cc_binary(
    name = "hpls_time",
    srcs = ["main.cpp"],
    features = COMPILER_WARNING_FEATURES,
    deps = [
        ":time_handler",
        # Single entry point: brings in HplsClock (hpls_clock.h)
        # AND the production HplsTime backend (CreateBackend<HplsTime>()).
        "//score/time/hpls_time",
    ],
)

# Unit test for the time handler: replaces HplsClock with a mock.
cc_test(
    name = "hpls_time_handler_test",
    srcs = ["hpls_time_handler_test.cpp"],
    features = COMPILER_WARNING_FEATURES,
    deps = [
        ":time_handler",
        "//score/time/hpls_time:hpls_time_mock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [":hpls_time_handler_test"],
    visibility = ["//examples/time:__pkg__"],
)
