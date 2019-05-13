#include "LocalFilesystemWorker.h"

LocalFilesystemWorker::LocalFilesystemWorker(const fs::path& workItem)
	: m_workItem(workItem)
{
}

void LocalFilesystemWorker::Work(WorkQueueV& workQueue, OutQueueV& outQueue)
{
}
