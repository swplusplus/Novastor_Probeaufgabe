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

	void Start(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue);

	void Work(const fs::path& workItem, WorkQueue& workQueue, FilesystemEntry::Queue& outQueue);
private:
	void Run(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue);

	std::thread m_theThread;
};


