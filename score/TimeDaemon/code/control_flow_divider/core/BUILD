load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "control_flow_divider",
    srcs = [],
    hdrs = [
        "control_flow_divider.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common/data_flow",
        "//score/TimeDaemon/code/common/machines",
        "@score_baselibs//score/mw/log:frontend",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":control_flow_divider_test",
    ],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)

cc_test(
    name = "control_flow_divider_test",
    srcs = [
        "control_flow_divider_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":control_flow_divider",
        "@score_baselibs//score/mw/log:console_only_backend",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
