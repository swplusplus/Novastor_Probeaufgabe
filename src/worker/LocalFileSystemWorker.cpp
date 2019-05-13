#include "LocalFileSystemWorker.h"

LocalFilesystemWorker::LocalFilesystemWorker(const fs::path& workItem)
	: m_workItem(workItem)
{
}

void LocalFilesystemWorker::Work(lf::queue<WorkerBase*>& workQueue, lf::queue<FilesystemEntry>& outQueue)
{
}
