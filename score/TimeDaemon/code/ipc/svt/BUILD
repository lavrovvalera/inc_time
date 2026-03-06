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
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "config",
    hdrs = [
        "config.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/ipc/svt:__subpackages__"],
)

cc_library(
    name = "time_info",
    srcs = [
        "svt_time_info.cpp",
    ],
    hdrs = [
        "svt_time_info.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/ipc/svt:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/ipc:data_converter",
    ],
)

cc_test(
    name = "common_factory_test",
    srcs = [
        "common_factory_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/ipc/svt/publisher:factory",
        "//score/TimeDaemon/code/ipc/svt/receiver:factory",
        "@score_baselibs//score/mw/log:console_only_backend",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "svt_time_info_test",
    srcs = [
        "svt_time_info_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":time_info",
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":common_factory_test",
        ":svt_time_info_test",
    ],
    visibility = ["//score/TimeDaemon/code/ipc:__subpackages__"],
)
