cmake_minimum_required(VERSION 3.0)

project(curve_fitting)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")

find_package(Eigen3 REQUIRED)

include_directories(
    include
    ${EIGEN3_INCLUDE_DIRS}
)

add_library(curve_fitting SHARED src/curve_fitting.cpp)

add_executable(demo src/demo.cpp)
target_link_libraries(demo curve_fitting)

install(TARGETS curve_fitting DESTINATION lib)
install(FILES include/${PROJECT_NAME}/curve_fitting.h DESTINATION include/${PROJECT_NAME})
