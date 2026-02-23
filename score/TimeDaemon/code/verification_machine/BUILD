load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    test_suites_from_sub_packages = [
        "//score/TimeDaemon/code/verification_machine/core:unit_test_suite",
        "//score/TimeDaemon/code/verification_machine/svt:unit_test_suite",
    ],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)
