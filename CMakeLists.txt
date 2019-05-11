project(Novastor_Probeaufgabe)
cmake_minimum_required(VERSION 3.8)
enable_language(CXX)

IF (WIN32)
    SET(BOOST_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/boost_1_70_0" CACHE PATH "Root dir of boost")
ENDIF()

find_package(Boost REQUIRED COMPONENTS unit_test_framework program_options)

add_executable(Novastor_Probeaufgabe "Novastor_Probeaufgabe.cpp" "Novastor_Probeaufgabe.h")
target_link_libraries(Novastor_Probeaufgabe Boost::program_options Boost::disable_autolinking)

add_executable(Novastor_Probeaufgabe_UT "Novastor_Probeaufgabe_UT.cpp")
target_link_libraries(Novastor_Probeaufgabe_UT Boost::unit_test_framework Boost::disable_autolinking)


include(CTest)

add_test(Novastor_ProbeaufgabeRuns Novastor_Probeaufgabe)
add_test(Novastor_Probeaufgabe_UTRuns Novastor_Probeaufgabe_UT)
