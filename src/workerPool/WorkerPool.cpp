#include "WorkerPool.h"
#include <condition_variable>

WorkerPool::WorkerPool(size_t numWorker, const std::vector<std::filesystem::path>& paths)
{
	for (const auto& path : paths)
	{
		m_workQueue.push(path);
	}
	StartThreads(numWorker);
}

void WorkerPool::Join()
{
	using namespace std::chrono_literals;
	while (!synchronizerQueue.empty())
	{
		std::this_thread::sleep_for(100ms);
	}
	m_workQueue.close();
	for (auto& worker : m_worker)
	{
		worker->Join();
	}
}

void WorkerPool::StartThreads(size_t numWorker)
{
	for (size_t i = 0; i < numWorker; ++i)
	{
		synchronizerQueue.push(true);
		m_worker.emplace_back(std::make_unique<LocalFilesystemWorker>())->Start(m_workQueue, m_outQueue, synchronizerQueue);
	}
}
