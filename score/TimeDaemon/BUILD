load("@score_baselibs//:bazel/unit_tests.bzl", "cc_unit_test_suites_for_host_and_qnx")

cc_unit_test_suites_for_host_and_qnx(
    name = "unit_test_suite",
    test_suites_from_sub_packages = [
        "//score/TimeDaemon/code/application:unit_test_suite",
        "//score/TimeDaemon/code/common:unit_test_suite",
        "//score/TimeDaemon/code/control_flow_divider:unit_test_suite",
        "//score/TimeDaemon/code/ipc:unit_test_suite",
        "//score/TimeDaemon/code/msg_broker:unit_test_suite",
        "//score/TimeDaemon/code/ptp_machine:unit_test_suite",
        "//score/TimeDaemon/code/verification_machine:unit_test_suite",
    ],
    visibility = ["//score:__pkg__"],
)
