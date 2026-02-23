load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

alias(
    name = "qgptp_ptp_machine",
    actual = "//score/TimeDaemon/code/ptp_machine/qgptp:qgptp_machine",
    visibility = ["//score/TimeDaemon:__subpackages__"],
)

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    test_suites_from_sub_packages = [
        "//score/TimeDaemon/code/ptp_machine/core:unit_test_suite",
        "//score/TimeDaemon/code/ptp_machine/qgptp:unit_test_suite",
    ],
    visibility = ["//score/TimeDaemon:__subpackages__"],
)
