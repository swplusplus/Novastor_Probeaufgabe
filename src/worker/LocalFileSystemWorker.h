#pragma once
#include "WorkerBase.h"

class LocalFilesystemWorker : public WorkerBase
{
public:
	LocalFilesystemWorker(const fs::path& workItem);

private:
	// Inherited via WorkerBase
	virtual void Work(lf::queue<WorkerBase*>& workQueue, lf::queue<FilesystemEntry>& outQueue) override;

	fs::path m_workItem;
};


