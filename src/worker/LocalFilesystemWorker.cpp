#include "LocalFilesystemWorker.h"
#include <iostream>

void LocalFilesystemWorker::Start(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue, boost::concurrent::sync_queue<bool>& syncQueue)
{
	m_theThread = std::thread{ [&]() {Run(workQueue, outQueue, syncQueue); } };
}

void LocalFilesystemWorker::Run(WorkQueue& workQueue, FilesystemEntry::Queue& outQueue, boost::concurrent::sync_queue<bool>& syncQueue)
{
	try
	{
		while (true)
		{
			fs::path workItem;
			if (workQueue.nonblocking_pull(workItem) != boost::concurrent::queue_op_status::success)
			{
				syncQueue.pull();
				workItem = workQueue.pull();
				syncQueue.push(true);
			}

			try
			{
				Work(workItem, workQueue, outQueue);
			}
			catch (const std::exception& err)
			{
				std::cerr << "directory " << workItem << ": " << err.what() << std::endl;
			}

		}
	} catch (const boost::concurrent::sync_queue_is_closed&)
	{ }
}

void LocalFilesystemWorker::Work(const fs::path& workItem, WorkQueue& workQueue, FilesystemEntry::Queue& outQueue)
{
	for (const auto& it : fs::directory_iterator{workItem})
	{
		try
		{
			if (it.is_directory())
			{
				workQueue.push(it.path());
			}
			else
			{
				outQueue.push(FilesystemEntry{ it.path().string(), it.last_write_time(), it.file_size() });
			}
		}
		catch (const std::exception& err)
		{
			try
			{
				std::cerr << it << ": " << err.what() << std::endl;
			}
			catch (const std::exception& err)
			{
				std::cerr << err.what() << std::endl;
			}
		}
	}
}

void LocalFilesystemWorker::Join()
{
	m_theThread.join();
}

