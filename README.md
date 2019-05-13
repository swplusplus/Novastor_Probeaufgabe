# Novastor_Probeaufgabe

## Prerequisites

- CMake >= 3.8
- for Windows MS Visual Studio 2017 or MS Visual Studio 2019 compiler is required to build using the prebuilt libraries under thirdparty folder
- for linux the boost-dev package must be installed

## Design

### Participating components

- Commandline Parser (main)
- WorkerPool
- WorkerThread
- WorkerBase
  - LocalFilesystemWorker
- Collector / Outputter
