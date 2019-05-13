#pragma once
#include "worker/LocalFilesystemWorker.h"
#include <vector>
#include <filesystem>

class WorkerPool
{
public:
	WorkerPool(size_t numWorker, const std::vector<std::filesystem::path>& paths);

private:

	void StartThreads(size_t numWorker);

	std::vector<std::unique_ptr<LocalFilesystemWorker>> m_worker;
	LocalFilesystemWorker::WorkQueue m_workQueue;
	FilesystemEntry::Queue m_outQueue;
};



