load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")
load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_library(
    name = "svt_verification_machine",
    srcs = [
        "factory.cpp",
    ],
    hdrs = [
        "factory.h",
        "svt_verification_machine.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/common/machines",
        "//score/TimeDaemon/code/verification_machine/core:verification_machine",
        "//score/TimeDaemon/code/verification_machine/svt/validators",
        "@score_baselibs//score/mw/log",
    ],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    cc_unit_tests = [
        ":svt_verification_machine_test",
    ],
    test_suites_from_sub_packages = ["//score/TimeDaemon/code/verification_machine/svt/validators:unit_test_suite"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)

cc_test(
    name = "svt_verification_machine_test",
    srcs = [
        "svt_verification_machine_test.cpp",
    ],
    tags = ["unit"],
    deps = [
        ":svt_verification_machine",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
