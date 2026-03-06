load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "job_runner",
    srcs = ["job_runner.cpp"],
    hdrs = [
        "job_runner.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common:logging_contexts",
        "@score_baselibs//score/concurrency",
        "@score_baselibs//score/mw/log:frontend",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":job_runner_test",
    ],
    visibility = ["//score/TimeDaemon/code/application:__pkg__"],
)

cc_test(
    name = "job_runner_test",
    srcs = [
        "job_runner_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":job_runner",
        "@score_baselibs//score/mw/log:console_only_backend",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
