load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "ptp_control_flow_divider",
    srcs = [
        "factory.cpp",
    ],
    hdrs = [
        "factory.h",
        "ptp_control_flow_divider.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/common/machines",
        "//score/TimeDaemon/code/control_flow_divider/core:control_flow_divider",
        "@score_baselibs//score/mw/log",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":factory_test",
        ":ptp_control_flow_divider_test",
    ],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)

cc_test(
    name = "factory_test",
    srcs = [
        "factory_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":ptp_control_flow_divider",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "ptp_control_flow_divider_test",
    srcs = [
        "ptp_control_flow_divider_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":ptp_control_flow_divider",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
