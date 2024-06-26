load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("@org_tensorflow//tensorflow:tensorflow.bzl", "tf_cc_binary", "tf_cc_test")

package(default_visibility = ["//monolith/native_training/data:__subpackages__"])

cc_library(
    name = "relational_utils",
    srcs = [],
    hdrs = ["relational_utils.h"],
    deps = [
        "@com_google_glog//:glog",
    ],
)

cc_test(
    name = "relational_utils_test",
    srcs = ["relational_utils_test.cc"],
    deps = [
        ":relational_utils",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "label_utils",
    srcs = ["label_utils.cc"],
    hdrs = ["label_utils.h"],
    deps = [
        "//monolith/native_training/data:data_op_config_cc_proto",
        "//third_party/nlohmann:json",
        "@com_google_absl//absl/strings",
        "@com_google_glog//:glog",
    ],
)

cc_test(
    name = "label_utils_test",
    srcs = ["label_utils_test.cc"],
    deps = [
        ":label_utils",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "cache_mgr",
    srcs = [
        "cache_mgr.cc",
        "cache_mgr.h",
    ],
    hdrs = ["cache_mgr.h"],
    deps = [
        "//monolith/native_training/data/training_instance:data_reader",
        "//third_party/nlohmann:json",
        "@com_google_absl//absl/container:flat_hash_map",
    ],
)

tf_cc_test(
    name = "cache_mgr_test",
    srcs = ["cache_mgr_test.cc"],
    deps = [
        ":cache_mgr",
        "@com_google_googletest//:gtest_main",
        "@org_tensorflow//tensorflow/core:test",
    ],
)

cc_library(
    name = "datasource_utils",
    srcs = [
        "datasource_utils.cc",
        "datasource_utils.h",
    ],
    hdrs = ["datasource_utils.h"],
)

tf_cc_test(
    name = "datasource_utils_test",
    srcs = ["datasource_utils_test.cc"],
    deps = [
        ":datasource_utils",
        "@com_google_googletest//:gtest_main",
        "@org_tensorflow//tensorflow/core:test",
    ],
)

cc_library(
    name = "file_match_split_provider",
    srcs = ["file_match_split_provider.cc"],
    hdrs = ["file_match_split_provider.h"],
    deps = [
        "//monolith/native_training/runtime/concurrency:queue",
        "@org_tensorflow//tensorflow/core:framework_headers_lib",
        "@com_google_glog//:glog",
    ],
)

tf_cc_test(
    name = "file_match_split_provider_test",
    srcs = ["file_match_split_provider_test.cc"],
    deps = [
        ":file_match_split_provider",
        "@com_google_googletest//:gtest_main",
        "@org_tensorflow//tensorflow/core:test",
    ],
)

cc_library(
    name = "parquet_example_reader",
    srcs = [
        "arrow_random_access_file.h",
        "sized_random_access_file.h",
        "parquet_column_buffer.h",
        "parquet_example_reader.h",
    ],
    deps = [
        "@arrow",
    ]
)

cc_library(
    name = "uniq_hashtable",
    hdrs = ["uniq_hashtable.h"],
    deps = [
        "@com_google_absl//absl/base:core_headers",
        "@com_google_glog//:glog",
    ],
)

tf_cc_test(
    name = "uniq_hashtable_test",
    srcs = ["uniq_hashtable_test.cc"],
    deps = [
        ":uniq_hashtable",
        "@com_google_googletest//:gtest_main",
        "@org_tensorflow//tensorflow/core:test",
    ]
)

cc_library(
    name = "value_filter_by_line_id",
    hdrs = ["value_filter_by_line_id.h"],
    srcs = ["value_filter_by_line_id.cc"],
    deps = [
        ":relational_utils",
        "//idl:example_cc_proto",
        "//third_party/nlohmann:json",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/synchronization",
        "@org_tensorflow//tensorflow/core/platform:env",
    ],
)

cc_library(
    name = "value_filter_by_feature",
    hdrs = ["value_filter_by_feature.h"],
    srcs = ["value_filter_by_feature.cc"],
    deps = [
        ":relational_utils",
        "//idl:example_cc_proto",
        "//third_party/nlohmann:json",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/synchronization",
        "@org_tensorflow//tensorflow/core/platform:env",
    ],
)

