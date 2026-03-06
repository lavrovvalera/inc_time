# *******************************************************************************
# Copyright (c) 2025 Contributors to the Eclipse Foundation
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
    name = "factory_impl_header",
    hdrs = ["factory_impl.h"],
    features = COMPILER_WARNING_FEATURES,
    tags = ["FFI"],
    visibility = [
        "//score/time/HighPrecisionLocalSteadyClock:__subpackages__",
    ],
)

filegroup(
    name = "factory_impl_stub_srcs",
    srcs = [
        "factory_impl_stub.cpp",
    ],
    visibility = [
        "//score/time/HighPrecisionLocalSteadyClock:__subpackages__",
    ],
)

cc_library(
    name = "factory_impl_for_utests",
    testonly = True,
    srcs = ["factory_impl_stub.cpp"],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/time/HighPrecisionLocalSteadyClock:__subpackages__"],
    deps = [
        "//score/time/HighPrecisionLocalSteadyClock:interface_mocks",
        "@googletest//:gtest",
    ],
)

alias(
    name = "details",
    actual = select({
        "@platforms//os:qnx": "//score/time/HighPrecisionLocalSteadyClock/details/qtime:qclock",
        "//conditions:default": "//score/time/HighPrecisionLocalSteadyClock/details/system_clock",
    }),
    visibility = [
        "//score/time/HighPrecisionLocalSteadyClock:__subpackages__",
    ],
)

py_unittest_qnx_test(
    name = "qnx_unit_test_cases",
    test_suites = [
        "//score/time/HighPrecisionLocalSteadyClock/details/qtime:qnx_unit_test_cases",
        "//score/time/HighPrecisionLocalSteadyClock/details/system_clock:qnx_unit_test_cases",
    ],
    visibility = ["//score/time/HighPrecisionLocalSteadyClock:__pkg__"],
)

test_suite(
    name = "unit_tests",
    tests = [
        "//score/time/HighPrecisionLocalSteadyClock/details/system_clock:unit_tests",
    ],
    visibility = ["//score/time/HighPrecisionLocalSteadyClock:__pkg__"],
)
