load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "validators",
    srcs = [
        "synchronization_validator.cpp",
        "time_jumps_validator.cpp",
        "timeout_validator.cpp",
    ],
    hdrs = [
        "synchronization_validator.h",
        "time_jumps_validator.h",
        "timeout_validator.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common:logging_contexts",
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/verification_machine/core:verification_machine",
        "@score_baselibs//score/mw/log",
        "//score/time/HighPrecisionLocalSteadyClock",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":timeout_validator_test",
        ":synchronization_validator_test",
        ":time_jumps_validator_test",
    ],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)

cc_test(
    name = "timeout_validator_test",
    srcs = [
        "timeout_validator_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":validators",
        "//score/time/HighPrecisionLocalSteadyClock:utest_mock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "synchronization_validator_test",
    srcs = [
        "synchronization_validator_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":validators",
        "//score/time/HighPrecisionLocalSteadyClock:utest_mock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "time_jumps_validator_test",
    srcs = [
        "time_jumps_validator_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":validators",
        "//score/time/HighPrecisionLocalSteadyClock:utest_mock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
