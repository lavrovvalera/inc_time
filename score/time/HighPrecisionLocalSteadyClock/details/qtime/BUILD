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
    name = "qclock",
    srcs = [
        "factory_impl.cpp",
        "qclock.cpp",
        "tick_provider.cpp",
        "tick_provider.h",  # internal header so it will stay in srcs"
    ],
    hdrs = [
        "qclock.h",
        # high_precision_local_steady_clock.h will come with the :interface target
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["FFI"],
    target_compatible_with = ["@platforms//os:qnx"],
    visibility = ["//score/time/HighPrecisionLocalSteadyClock/details:__subpackages__"],
    deps = [
        "@score_baselibs//score/os/qnx:neutrino",
        "//score/time/HighPrecisionLocalSteadyClock:interface",
        "//score/time/HighPrecisionLocalSteadyClock/details:factory_impl_header",
    ],
)

cc_test(
    name = "qclock_test",
    testonly = True,
    srcs = [
        "qclock.cpp",
        "qclock.h",
        "qclock_test.cpp",
        "tick_provider.h",
        "tick_provider_mock.cpp",
        "tick_provider_mock.h",
    ],
    tags = ["unit"],
    target_compatible_with = ["@platforms//os:qnx"],
    deps = [
        ":qclock",
        "@score_baselibs//score/os/qnx:neutrino_qnx_mock",
        "//score/time/HighPrecisionLocalSteadyClock:interface",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "tick_provider_test",
    testonly = True,
    srcs = [
        "tick_provider.cpp",
        "tick_provider.h",
        "tick_provider_test.cpp",
    ],
    tags = ["unit"],
    target_compatible_with = ["@platforms//os:qnx"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "factory_test",
    srcs = [
        "factory_test.cpp",
    ],
    tags = ["unit"],
    visibility = ["//score/time:__subpackages__"],
    deps = [
        ":qclock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

py_unittest_qnx_test(
    name = "qnx_unit_test_cases",
    test_cases = [
        ":factory_test",
        ":qclock_test",
        ":tick_provider_test",
    ],
    visibility = ["//score/time/HighPrecisionLocalSteadyClock/details:__pkg__"],
)
