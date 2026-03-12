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

load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//third_party/itf:py_unittest_qnx_test.bzl", "py_unittest_qnx_test")

cc_library(
    name = "system_clock",
    srcs = [
        "factory_impl.cpp",
        "system_clock.cpp",
    ],
    hdrs = [
        "system_clock.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/time/HighPrecisionLocalSteadyClock/details:__subpackages__"],
    deps = [
        "//score/time/HighPrecisionLocalSteadyClock:interface",
        "//score/time/HighPrecisionLocalSteadyClock/details:factory_impl_header",
    ],
)

cc_test(
    name = "system_clock_test",
    testonly = True,
    srcs = [
        "system_clock.cpp",
        "system_clock.h",
        "system_clock_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        "//score/time/HighPrecisionLocalSteadyClock:interface",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

test_suite(
    name = "unit_tests",
    tests = [
        ":system_clock_test",
    ],
    visibility = ["//score/time/HighPrecisionLocalSteadyClock/details:__pkg__"],
)

py_unittest_qnx_test(
    name = "qnx_unit_test_cases",
    test_cases = [
        ":system_clock_test",
    ],
    visibility = ["//score/time/HighPrecisionLocalSteadyClock/details:__pkg__"],
)
