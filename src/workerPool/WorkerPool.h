#pragma once
#include "collector/Collector.h"
#include "worker/LocalFilesystemWorker.h"
#include <vector>
#include <filesystem>

class WorkerPool
{
	friend class WorkerPoolTestProxy;
public:
	WorkerPool(size_t numWorker, const std::vector<std::filesystem::path>& paths, std::ostream* output);

	void Join();

private:

	void StartThreads(size_t numWorker);

	std::vector<std::unique_ptr<LocalFilesystemWorker>> m_worker;
	LocalFilesystemWorker::WorkQueue m_workQueue;
	FilesystemEntry::Queue m_outQueue;
	boost::concurrent::sync_queue<bool> synchronizerQueue;
	Collector m_collector;
	std::thread m_collectorThread;
	std::ostream* m_output;
};



