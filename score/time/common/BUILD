load("@score_baselibs//score/language/safecpp:toolchain_features.bzl", "COMPILER_WARNING_FEATURES")

cc_library(
    name = "time_base_status",
    hdrs = [
        "time_base_status.h",
    ],
    features = COMPILER_WARNING_FEATURES,
    tags = ["FFI"],
    visibility = ["//score/time:__subpackages__"],
    deps = [
    ],
)

cc_test(
    name = "time_base_status_test",
    srcs = [
        "time_base_status_test.cpp",
    ],
    tags = ["unit"],
    visibility = ["//score/time:__subpackages__"],
    deps = [
        ":time_base_status",
        "@googletest//:gtest",
        "@googletest//:gtest:main",
    ],
)
