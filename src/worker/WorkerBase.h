#pragma once

#include <filesystem>
#include <boost/lockfree/queue.hpp>
#include "model/FileSystemEntry.h"

namespace lf = boost::lockfree;
namespace fs = std::filesystem;



class WorkerBase
{
public:
    virtual ~WorkerBase() {}
    WorkerBase();

	virtual void Work(lf::queue<WorkerBase*>& workQueue, lf::queue<FilesystemEntry>& outQueue) = 0;
};
