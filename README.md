# Novastor_Probeaufgabe

## Prerequisites

- CMake >= 3.8
- for Windows MS Visual Studio 2017 or MS Visual Studio 2019 compiler is required to build using the prebuilt libraries under the thirdparty folder
- for linux the boost-dev package (1.70.0?) must be installed

## Design

### Algorithm

- The Application can be parameterized (by command line) to scan 1..n folders. Passed folders shall not be sub folders of each other, otherwise entries may be contained multiple times in the output file. Only the local filesystem is supported (which includes mounted remote file systems).
- There are three Queues: the work-item queue, the result-queue and one queue for internal synchronization.
- At start of the program all parameterized folders are pushed into the work queue.
- Then we start a configurable (by command line) number of worker threads for filesystem traversal, as well as one collector thread for sorting and outputting the result file.
- Each worker reads exactly one directory, without recursion.
  - Each newly discovered subdirectory is pushed into the work-item queue, files are pushed into the output-queue.
  - When finished, a new work-item (directory) is pulled out of the work queue.
- The collector thread concurrently sorts the content of the output queue.

### Participating components

- src/Novastor_Probeaufgabe.cpp: command line Parser (main)
- src/workerPool/WorkerPool.[h,cpp]: WorkerPool (starts and synchronizes worker threads and collector thread)
- src/worker/LocalFilesystemWorker.[h,cpp]: LocalFilesystemWorker (traverses the local file system)
- src/collector/Collector.[h,cpp] Collector (sorts and writes the result)
