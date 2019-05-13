#pragma once
#include "WorkerBase.h"

class LocalFilesystemWorker : public WorkerBase
{
public:
	LocalFilesystemWorker(const fs::path& workItem);

	// Inherited via WorkerBase
	virtual void Work(WorkQueueV& workQueue, OutQueueV& outQueue) override;

private:

	fs::path m_workItem;
};


