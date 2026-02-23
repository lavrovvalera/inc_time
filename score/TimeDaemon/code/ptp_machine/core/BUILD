load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "ptp_machine",
    srcs = [
    ],
    hdrs = [
        "ptp_machine.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common/data_flow",
        "//score/TimeDaemon/code/common/machines",
        "//score/time/HighPrecisionLocalSteadyClock",
        "@score_baselibs//score/mw/log",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":ptp_machine_test",
    ],
    test_suites_from_sub_packages = [
    ],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)

cc_test(
    name = "ptp_machine_test",
    srcs = [
        "ptp_engine_mock.h",
        "ptp_machine_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":ptp_machine",
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
