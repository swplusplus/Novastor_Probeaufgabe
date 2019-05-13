#include "LocalFilesystemWorker.h"

LocalFilesystemWorker::LocalFilesystemWorker(const fs::path& workItem)
	: m_workItem(workItem)
{
}

void LocalFilesystemWorker::Work(WorkQueueV& workQueue, OutQueueV& outQueue)
{
	for (fs::directory_iterator itend, it{ m_workItem }; it != itend; ++it)
	{
		if (it->is_directory())
		{
			workQueue.push(std::make_unique<LocalFilesystemWorker>(it->path()));
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
