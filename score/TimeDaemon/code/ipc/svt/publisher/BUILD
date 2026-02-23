load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")

cc_library(
    name = "factory",
    srcs = ["factory.cpp"],
    hdrs = [
        "factory.h",
        "svt_publisher.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/ipc/core:publisher_impl",
        "//score/TimeDaemon/code/ipc/svt:config",
        "//score/TimeDaemon/code/ipc/svt:time_info",
    ],
)
