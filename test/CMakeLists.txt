add_executable(Novastor_Probeaufgabe_UT
	"Novastor_Probeaufgabe_UT.cpp"
	"Collector.cpp"
	"LocalFilesystemWorker.cpp"
	"WorkerPool.cpp")

target_link_libraries(Novastor_Probeaufgabe_UT Boost::unit_test_framework Boost::disable_autolinking)

include(CTest)

add_test(Novastor_Probeaufgabe_UTRuns Novastor_Probeaufgabe_UT)
