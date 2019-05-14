#pragma once
#include <filesystem>
#include <memory>
#include <thread>
#include <boost/thread/concurrent_queues/queue_views.hpp>
#include "model/FileSystemEntry.h"

namespace fs = std::filesystem;
namespace bc = boost::concurrent;

class LocalFilesystemWorker
{
public:
	using WorkQueue = bc::sync_queue<fs::path>;

	// starts the thread
	void Start(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue, boost::concurrent::sync_queue<bool>& syncQueue);

	// walks one directory (without recursion) and pushes subdirectories into the workQueue, files into the outQueue
	void Work(const fs::path& workItem, WorkQueue& workQueue, FilesystemEntry::Queue& outQueue);
	void Join();
private:
	// pull new work-items from queue; thread synchronization
	void Run(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue, boost::concurrent::sync_queue<bool>& syncQueue);

	std::thread m_theThread;
};


