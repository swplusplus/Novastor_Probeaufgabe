add_library(Novastor_Probeaufgabe_lib STATIC
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

target_link_libraries(Novastor_Probeaufgabe_lib Boost::program_options Boost::thread Boost::disable_autolinking)

add_executable(Novastor_Probeaufgabe
    "Novastor_Probeaufgabe.cpp"
    "Novastor_Probeaufgabe.h"
    )


target_link_libraries(Novastor_Probeaufgabe Novastor_Probeaufgabe_lib)
add_test(Novastor_ProbeaufgabeRuns Novastor_Probeaufgabe)
