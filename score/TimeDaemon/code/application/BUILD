load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "timebase_handler",
    hdrs = [
        "timebase_handler.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/application:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common:logging_contexts",
        "@score_baselibs//score/concurrency",
        "@score_baselibs//score/mw/log",
    ],
)

cc_binary(
    name = "TimeDaemon",
    srcs = [
        "TimeDaemon.cpp",
        "TimeDaemon.h",
        "main.cpp",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    deps = [
        "//score/TimeDaemon/code/application/svt:svt_handler",
        "//score/TimeDaemon/code/common:logging_contexts",
        "@score_baselibs//score/concurrency",
        "@score_baselibs//score/mw/lifecycle:lifecycle_non_adaptive",
        "@score_baselibs//score/mw/log",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    test_suites_from_sub_packages = [
        "//score/TimeDaemon/code/application/job_runner:unit_test_suite",
        "//score/TimeDaemon/code/application/svt:unit_test_suite",
    ],
    visibility = ["//score/TimeDaemon:__pkg__"],
)
