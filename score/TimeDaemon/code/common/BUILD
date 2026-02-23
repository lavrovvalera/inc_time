load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "logging_contexts",
    srcs = [],
    hdrs = [
        "logging_contexts.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    test_suites_from_sub_packages = [
        "//score/TimeDaemon/code/common/data_types:unit_test_suite",
        "//score/TimeDaemon/code/common/data_flow:unit_test_suite",
        "//score/TimeDaemon/code/common/machines:unit_test_suite",
    ],
    visibility = ["//score/TimeDaemon:__pkg__"],
)
