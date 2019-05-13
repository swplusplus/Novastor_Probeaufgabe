configure_file (
  "${PROJECT_SOURCE_DIR}/test/Testdata.h.in"
  "${PROJECT_BINARY_DIR}/Testdata.h"
  )

include_directories("${PROJECT_BINARY_DIR}")

add_executable(Novastor_Probeaufgabe_UT
	"Novastor_Probeaufgabe_UT.cpp"
	"Collector_UT.cpp"
	"${PROJECT_SOURCE_DIR}/src/worker/LocalFilesystemWorker.cpp"
	"${PROJECT_SOURCE_DIR}/src/worker/LocalFilesystemWorker.h"
	"LocalFilesystemWorker_UT.cpp"
	"WorkerPool_UT.cpp"
	"${PROJECT_BINARY_DIR}/Testdata.h"
	)

target_link_libraries(Novastor_Probeaufgabe_UT Boost::unit_test_framework Boost::thread Boost::disable_autolinking)

include(CTest)

add_test(Novastor_Probeaufgabe_UTRuns Novastor_Probeaufgabe_UT)
