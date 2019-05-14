#include "WorkerPool.h"

#include "collector/Collector.h"

#include <condition_variable>
#include <iostream>

WorkerPool::WorkerPool(size_t numWorker, const std::vector<std::filesystem::path>& paths, std::ostream* output)
	: m_output(output)
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
	// an empty synchronizerQueue means all workers are waiting on an empty workQueue, so we can safely close it now.
	m_workQueue.close();
	for (auto& worker : m_worker)
	{
		worker->Join();
	}
	// also close the outQueue, the collector will pull all remaining entries and then terminate the collector thread.
	m_outQueue.close();
	m_collectorThread.join();
	if (m_output)
	{
		for (const auto& entry : m_collector.GetSortedEntries())
		{
			(*m_output) << entry << std::endl;
		}
	}
}

void WorkerPool::StartThreads(size_t numWorker)
{
	m_collectorThread = std::thread([&] {m_collector.Run(m_outQueue); });
	for (size_t i = 0; i < numWorker; ++i)
	{
		synchronizerQueue.push(true);
		m_worker.emplace_back(std::make_unique<LocalFilesystemWorker>())->Start(m_workQueue, m_outQueue, synchronizerQueue);
	}
}
