#include "LocalFilesystemWorker.h"

void LocalFilesystemWorker::Start(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue)
{
	m_theThread = std::thread{ [&]() {Run(workQueue, outQueue); } };
}

void LocalFilesystemWorker::Run(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue)
{
	while (true)
	{
		auto workItem = workQueue.pull();
		Work(workItem, workQueue, outQueue);
	}
}

void LocalFilesystemWorker::Work(const fs::path& workItem, WorkQueue& workQueue, FilesystemEntry::Queue& outQueue)
{
	for (fs::directory_iterator itend, it{ workItem }; it != itend; ++it)
	{
		if (it->is_directory())
		{
			workQueue.push(it->path());
		}
		else if (it->is_regular_file())
		{
			outQueue.push(FilesystemEntry{ it->path().string(), it->last_write_time(), it->file_size() });
		}
		else
		{
			throw std::exception{ ("found an unhandled file or directory entry: " + it->path().string()).c_str()};
		}
	}
}
