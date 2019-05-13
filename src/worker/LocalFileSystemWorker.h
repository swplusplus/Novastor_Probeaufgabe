#pragma once
#include "WorkerBase.h"

class LocalFilesystemWorker : public WorkerBase
{
public:

private:
	// Inherited via WorkerBase
	virtual void Work(lf::queue<WorkerBase*>& workQueue, lf::queue<FilesystemEntry>& outQueue) override;

};


