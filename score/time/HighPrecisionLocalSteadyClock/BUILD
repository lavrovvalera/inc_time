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

# DEPRECATED — replaced by //score/time/hpls_time.
# This package will be deleted once all consumers (TimeDaemon) have been migrated.
# Do NOT add new dependencies on any target in this package.

load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//third_party/itf:py_unittest_qnx_test.bzl", "py_unittest_qnx_test")

alias(
    name = "HighPrecisionLocalSteadyClock",
    actual = "//score/time/HighPrecisionLocalSteadyClock/details",
    deprecation = "DEPRECATED: use //score/time/hpls_time:hpls_time instead. This target will be removed after TimeDaemon migration.",
    visibility = ["//visibility:public"],
)

alias(
    name = "utest_mock",
    testonly = True,
    actual = "//score/time/HighPrecisionLocalSteadyClock/details:factory_impl_for_utests",
    deprecation = "DEPRECATED: use //score/time/hpls_time:hpls_time_mock instead. This target will be removed after TimeDaemon migration.",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "interface",
    srcs = [
        "factory.cpp",
        "high_precision_local_steady_clock.cpp",
    ],
    hdrs = [
        "factory.h",
        "high_precision_local_steady_clock.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["FFI"],
    visibility = ["//visibility:public"],
    deps = [
        "//score/time/HighPrecisionLocalSteadyClock/details:factory_impl_header",
    ],
)

cc_library(
    name = "interface_mocks",
    testonly = True,
    srcs = [
        "factory_mock.cpp",
        "high_precision_local_steady_clock_mock.cpp",
    ],
    hdrs = [
        "factory_mock.h",
        "high_precision_local_steady_clock_mock.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":interface",
        "@googletest//:gtest",
    ],
)

py_unittest_qnx_test(
    name = "qnx_unit_test_cases",
    test_suites = [
        "//score/time/HighPrecisionLocalSteadyClock/details:qnx_unit_test_cases",
    ],
    visibility = ["//score/time:__pkg__"],
)

test_suite(
    name = "unit_tests",
    tests = [
        "//score/time/HighPrecisionLocalSteadyClock/details:unit_tests",
    ],
    visibility = ["//score/time:__subpackages__"],
)
