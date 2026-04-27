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

# Non-QNX production backend for HplsTime.
# Wraps std::chrono::high_resolution_clock and provides CreateBackend<HplsTime>().
cc_library(
    name = "system_clock",
    srcs = [
        "hpls_time_impl.cpp",
    ],
    hdrs = [
        "hpls_time_impl.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/time/hpls_time:__subpackages__"],
    deps = [
        "//score/time/clock:clock_core",
        "//score/time/hpls_time:hpls_clock",
        "//score/time/hpls_time:hpls_clock_iface",
    ],
)

cc_test(
    name = "hpls_time_impl_test",
    testonly = True,
    srcs = [
        "hpls_time_impl.cpp",
        "hpls_time_impl.h",
        "hpls_time_impl_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        "//score/time/clock:clock_core",
        "//score/time/hpls_time:hpls_clock",
        "//score/time/hpls_time:hpls_clock_iface",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":hpls_time_impl_test",
    ],
    visibility = ["//score/time/hpls_time/details:__pkg__"],
)
