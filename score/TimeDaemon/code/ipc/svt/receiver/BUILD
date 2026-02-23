load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")

cc_library(
    name = "factory",
    srcs = ["factory.cpp"],
    hdrs = [
        "factory.h",
        "svt_receiver.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/ipc:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/ipc/core:receiver_impl",
        "//score/TimeDaemon/code/ipc/svt:config",
        "//score/TimeDaemon/code/ipc/svt:time_info",
    ],
)

cc_library(
    name = "factory_mock",
    testonly = True,
    srcs = ["factory_stub.cpp"],
    hdrs = [
        "factory.h",
        "svt_receiver.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    visibility = ["//score/TimeDaemon/code/ipc:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/ipc:receiver_mock",
        "//score/TimeDaemon/code/ipc/svt:config",
        "//score/TimeDaemon/code/ipc/svt:time_info",
    ],
)
