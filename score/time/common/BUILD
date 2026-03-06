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

cc_library(
    name = "time_base_status",
    hdrs = [
        "time_base_status.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["FFI"],
    visibility = ["//score/time:__subpackages__"],
    deps = [
        "@score_baselibs//score/language/futurecpp",
    ],
)

cc_test(
    name = "time_base_status_test",
    srcs = [
        "time_base_status_test.cpp",
    ],
    tags = ["unit"],
    visibility = ["//score/time:__subpackages__"],
    deps = [
        ":time_base_status",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
