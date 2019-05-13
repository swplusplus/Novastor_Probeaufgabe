#pragma once

#include <filesystem>
#include <memory>
#include <boost/thread/concurrent_queues/queue_views.hpp>
#include "model/FileSystemEntry.h"

namespace fs = std::filesystem;
namespace bc = boost::concurrent;

class WorkerBase
{
public:
	using WorkQueue = bc::sync_queue<std::unique_ptr<WorkerBase>>;
	using WorkQueueV = bc::queue_back_view<WorkQueue>;
	using OutQueueV = bc::queue_back_view<FilesystemEntry::Queue>;

    virtual ~WorkerBase() {}

	virtual void Work(WorkQueueV& workQueue, OutQueueV& outQueue) = 0;
};
