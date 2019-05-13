#include "WorkerPool.h"

WorkerPool::WorkerPool(size_t numWorker, const std::vector<std::filesystem::path>& paths)
{
	for (const auto& path : paths)
	{
		m_workQueue.push(path);
	}
	StartThreads(numWorker);
}

void WorkerPool::StartThreads(size_t numWorker)
{
	for (size_t i = 0; i < numWorker; ++i)
	{
		m_worker.emplace_back(std::make_unique<LocalFilesystemWorker>())->Start(m_workQueue, m_outQueue);
	}
}
