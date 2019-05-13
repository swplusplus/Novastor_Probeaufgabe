project(Novastor_Probeaufgabe)
cmake_minimum_required(VERSION 3.8)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/boost_1_70_0" CACHE PATH "Root dir of boost")
endif()

set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost REQUIRED COMPONENTS unit_test_framework program_options thread)

include_directories("${CMAKE_SOURCE_DIR}/src")

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
