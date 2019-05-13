add_executable(Novastor_Probeaufgabe
    "Novastor_Probeaufgabe.cpp"
    "Novastor_Probeaufgabe.h"
	"collector/Collector.cpp"
	"collector/Collector.h"
	"model/FileSystemEntry.h"
    "worker/WorkerBase.cpp"
    "worker/WorkerBase.h"
    "worker/LocalFilesystemWorker.cpp"
    "worker/LocalFilesystemWorker.h"
	"worker/WorkerThread.cpp"
	"worker/WorkerThread.h"
    )

target_link_libraries(Novastor_Probeaufgabe Boost::program_options Boost::thread Boost::disable_autolinking)



include(CTest)

add_test(Novastor_ProbeaufgabeRuns Novastor_Probeaufgabe)



