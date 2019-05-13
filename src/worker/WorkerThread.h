#pragma once
#include <boost/lockfree/queue.hpp>
#include "model/FileSystemEntry.h"

namespace lf = boost::lockfree;

class WorkerBase;

class WorkerThread
{
public:
	void Run(lf::queue<WorkerBase*>& workQueue, lf::queue<FilesystemEntry>& outQueue);
};
