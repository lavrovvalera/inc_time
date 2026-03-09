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

alias(
    name = "SynchronizedVehicleTime",
    actual = "//score/time/SynchronizedVehicleTime/details:factory_impl",
    visibility = [
        "//visibility:public",
    ],
)

alias(
    name = "utest_mock",
    testonly = True,
    actual = "//score/time/SynchronizedVehicleTime/details:factory_impl_for_utests",
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "interface_mocks",
    testonly = True,
    srcs = [
        "factory_mock.cpp",
        "synchronized_vehicle_time_mock.cpp",
    ],
    hdrs = [
        "factory_mock.h",
        "synchronized_vehicle_time_mock.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = [
        "//score/time/SynchronizedVehicleTime:__subpackages__",
    ],
    deps = [
        ":interfaces",
        "//score/time/common:time_base_status",
        "@googletest//:gtest",
    ],
)

cc_library(
    name = "interfaces",
    srcs = [
        "factory.cpp",
        "slave_timebase_notification_types.cpp",
        "synchronized_vehicle_time.cpp",
        "time_base_status.cpp",
    ],
    hdrs = [
        "factory.h",
        "slave_timebase_notification_types.h",
        "synchronized_vehicle_time.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["FFI"],
    visibility = ["//visibility:public"],
    deps = [
        "//score/time/SynchronizedVehicleTime/details:factory_impl_header",
        "//score/time/common:time_base_status",
    ],
)

cc_test(
    name = "slave_timebase_notification_types_test",
    srcs = [
        "slave_timebase_notification_types_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":interfaces",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "time_base_status_test",
    srcs = [
        "time_base_status_test.cpp",
    ],
    tags = ["unit"],
    visibility = ["//visibility:private"],
    deps = [
        ":interfaces",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":slave_timebase_notification_types_test",
        ":time_base_status_test",
    ],
    test_suites_from_sub_packages = [
        "//score/time/SynchronizedVehicleTime/details:unit_test_suite",
    ],
    visibility = ["//score/time:__pkg__"],
)

test_suite(
    name = "unit_tests",
    tests = [
        ":unit_test_suite_host",
        "//score/time/SynchronizedVehicleTime/details:unit_tests",
    ],
    visibility = ["//score/time:__pkg__"],
)
