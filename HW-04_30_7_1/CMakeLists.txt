cmake_minimum_required(VERSION 3.18)
project(mainquick VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
add_executable(mainquick main.cpp quickSort.cpp thPool.cpp reqHandler.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
