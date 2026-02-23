load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "data_flow",
    srcs = [],
    hdrs = [
        "consumer.h",
        "producer.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":data_flow_test",
    ],
    visibility = ["//score/TimeDaemon:__pkg__"],
)

cc_test(
    name = "data_flow_test",
    srcs = [
        "producer_consumer_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":data_flow",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
