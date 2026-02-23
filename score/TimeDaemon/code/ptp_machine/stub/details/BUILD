load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")

cc_library(
    name = "stub_ptp_engine",
    srcs = [
        "stub_ptp_engine.cpp",
    ],
    hdrs = [
        "stub_ptp_engine.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    includes = [],
    tags = ["QM"],
    visibility = ["//score/TimeDaemon:__subpackages__"],
    deps = [
        "//score/TimeDaemon/code/common/data_types:ptp_time_info",
        "//score/TimeDaemon/code/common:logging_contexts",
        "//score/time/HighPrecisionLocalSteadyClock:interface",
        "@score_baselibs//score/mw/log",
    ],
)
