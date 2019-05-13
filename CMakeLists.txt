project(Novastor_Probeaufgabe)
cmake_minimum_required(VERSION 3.8)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/boost_1_70_0" CACHE PATH "Root dir of boost")
endif()

find_package(Boost REQUIRED COMPONENTS unit_test_framework program_options)

include_directories("${CMAKE_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(test)
