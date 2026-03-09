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
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "factory_impl_header",
    hdrs = ["factory_impl.h"],
    features = COMPILER_WARNING_FEATURES,
    tags = ["FFI"],
    visibility = [
        "//score/time/SynchronizedVehicleTime:__subpackages__",
    ],
)

filegroup(
    name = "logging_contexts",
    srcs =
        [
            "logging_contexts.h",
        ],
    tags = ["FFI"],
    visibility = [
        "//score/time/SynchronizedVehicleTime:__subpackages__",
    ],
)
[
    cc_library(
        name = name,
        testonly = testonly,
        srcs = srcs,
        hdrs = hdrs,
        features = COMPILER_WARNING_FEATURES,
        implementation_deps = impl_dep,
        tags = tag,
        visibility = [
            "//score/time/SynchronizedVehicleTime:__subpackages__",
        ],
        deps = deps + [
            "//score/time/common:time_base_status",
        ],
    )
    for name, testonly, srcs, hdrs, impl_dep, deps, tag in [
        (
            "factory_impl",
            False,
            [
            ],
            [],
            [
                "//score/time/SynchronizedVehicleTime/details/tdr"
            ],
            [
                "//score/time/SynchronizedVehicleTime:interfaces",
            ],
            ["FFI"],
        ),
        (
            "factory_impl_for_utests",
            True,
            [
                "factory_impl_stub.cpp",
            ],
            [
                "factory_impl.h",
                "factory_mock_helper.h",
            ],
            [],
            [
                "//score/time/SynchronizedVehicleTime:interface_mocks",
                "@googletest//:gtest",
            ],
            [],
        ),
    ]
]

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
    ],
    test_suites_from_sub_packages = [
        "//score/time/SynchronizedVehicleTime/details/tdr:unit_test_suite",
    ],
    visibility = ["//score/time/SynchronizedVehicleTime:__pkg__"],
)

test_suite(
    name = "unit_tests",
    tests = [
        "//score/time/SynchronizedVehicleTime/details/clock_realtime:unit_tests",
    ],
    visibility = ["//score/time/SynchronizedVehicleTime:__pkg__"],
)
