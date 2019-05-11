project(Novastor_Probeaufgabe)
cmake_minimum_required(VERSION 3.8)
enable_language(CXX)

SET(BOOST_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/boost_1_70_0" CACHE PATH "Root dir of boost")

find_package(Boost REQUIRED COMPONENTS unit_test_framework program_options)

add_executable(Novastor_Probeaufgabe "Novastor_Probeaufgabe.cpp" "Novastor_Probeaufgabe.h")
target_link_libraries(Novastor_Probeaufgabe Boost::program_options Boost::disable_autolinking)

