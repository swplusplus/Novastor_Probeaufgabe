#pragma once
#include "collector/Collector.h"
#include "worker/LocalFilesystemWorker.h"
#include <vector>
#include <filesystem>

class WorkerPool
{
	friend class WorkerPoolTestProxy;
public:
	// Constructor instantiates and starts worker threads
	WorkerPool(size_t numWorker, const std::vector<std::filesystem::path>& paths, std::ostream* output);

	// Wait for the workers to complete their work
	void Join();

private:

	// intrnal helper for starting the threads
	void StartThreads(size_t numWorker);

	std::vector<std::unique_ptr<LocalFilesystemWorker>> m_worker;
	// this queue contains work items in form of filesystem paths
	LocalFilesystemWorker::WorkQueue m_workQueue;
	// this queue contains unsorted discovered file information
	FilesystemEntry::Queue m_outQueue;
	// for thread synhronization purposes
	boost::concurrent::sync_queue<bool> synchronizerQueue;

	Collector m_collector;
	std::thread m_collectorThread;
	std::ostream* m_output;
};



