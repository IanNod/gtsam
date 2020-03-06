set (nonlinear_tests_exclued "testAdaptAutoDiff.cpp")
gtsamAddTestsGlob(nonlinear "test*.cpp" ${nonlinear_tests_exclued} "gtsam")
