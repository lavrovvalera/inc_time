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
    name = "shared_memory_handler",
    srcs = [],
    hdrs = [
        "shared_memory_handler.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/ipc:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common:logging_contexts",
        "@score_baselibs//score/memory/shared",
        "@score_baselibs//score/mw/log:frontend",
    ],
)

cc_library(
    name = "publisher_impl",
    srcs = [],
    hdrs = [
        "publisher_impl.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/ipc:__subpackages__"],
    deps = [
        ":shared_memory_handler",
        "//score/TimeDaemon/code/common/data_flow",
        "//score/TimeDaemon/code/common/machines",
        "//score/TimeDaemon/code/ipc:data_converter",
    ],
)

cc_library(
    name = "receiver_impl",
    srcs = [],
    hdrs = [
        "receiver_impl.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/ipc:__subpackages__"],
    deps = [
        ":shared_memory_handler",
        "//score/TimeDaemon/code/ipc:receiver",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":shared_memory_handler_test",
        ":publisher_impl_test",
        ":receiver_impl_test",
    ],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)

cc_test(
    name = "publisher_impl_test",
    srcs = [
        "publisher_impl_test.cpp",
        "test_types.h",
    ],
    tags = ["unit"],
    deps = [
        ":publisher_impl",
        "//score/TimeDaemon/code/ipc:data_converter",
        "@score_baselibs//score/mw/log:console_only_backend",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "receiver_impl_test",
    srcs = [
        "receiver_impl_test.cpp",
        "test_types.h",
    ],
    tags = ["unit"],
    deps = [
        ":receiver_impl",
        "//score/TimeDaemon/code/ipc:data_converter",
        "@score_baselibs//score/mw/log:console_only_backend",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "shared_memory_handler_test",
    srcs = [
        "shared_memory_handler_test.cpp",
        "test_types.h",
    ],
    tags = ["unit"],
    deps = [
        ":shared_memory_handler",
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/ipc:data_converter",
        "@score_baselibs//score/mw/log:console_only_backend",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
