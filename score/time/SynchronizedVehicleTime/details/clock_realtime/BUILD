load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")

[
    cc_library(
        name = name,
        testonly = testonly,
        srcs = [
            "clock_provider.cpp",
            "clock_provider.h",  # placed into 'srcs' since this is an internal header
            "factory_impl.cpp",
            "//score/time/SynchronizedVehicleTime/details:logging_contexts",  # placed into 'srcs' since this is an internal header
        ],
        hdrs = [
            "//score/time/SynchronizedVehicleTime/details:factory_impl_header",
        ],
        features = COMPILER_WARNING_FEATURES,
        visibility = [
            "//score/time/SynchronizedVehicleTime/details:__pkg__",
            "//score/time/SynchronizedVehicleTime/test:__subpackages__",
        ],
        deps = [
            "@score_baselibs//score/concurrency",
            "@score_baselibs//score/mw/log",
            "//score/time/SynchronizedVehicleTime:interfaces",
        ] + dependencies,
    )
    for name, testonly, dependencies in [
        (
            "clock_realtime",
            False,
            [
                "//score/time/HighPrecisionLocalSteadyClock",
            ],
        ),
        (
            "for_unit_testing",
            True,
            [
                "//score/time/HighPrecisionLocalSteadyClock:utest_mock",
            ],
        ),
    ]
]

cc_test(
    name = "factory_impl_test",
    srcs = [
        "factory_impl_test.cpp",
    ],
    tags = ["unit"],
    visibility = ["//score/time:__subpackages__"],
    deps = [
        ":for_unit_testing",
        "@score_baselibs//score/language/safecpp/coverage_termination_handler",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "clock_provider_test",
    srcs = [
        "clock_provider_test.cpp",
    ],
    tags = ["unit"],
    visibility = ["//score/time:__subpackages__"],
    deps = [
        ":for_unit_testing",
        "@score_baselibs//score/language/safecpp/coverage_termination_handler",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

test_suite(
    name = "unit_tests",
    tests = [
        ":clock_provider_test",
        ":factory_impl_test",
    ],
    visibility = ["//score/time/SynchronizedVehicleTime/details:__pkg__"],
)
