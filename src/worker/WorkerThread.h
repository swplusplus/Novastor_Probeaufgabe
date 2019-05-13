#pragma once

namespace lf = boost::lockfree;

class WorkerBase;

class WorkerThread
{
public:
	void Run(lf::queue<WorkerBase*>& workQueue, lf::queue<FilesystemEntry>& outQueue);
};
