set(ignore_test "testNestedDissection.cpp")
list (APPEND ignore_test "testFindSeparator.cpp")
gtsamAddTestsGlob(partition "test*.cpp" "${ignore_test}" "gtsam_unstable;gtsam;metis")
