#pragma once
#include <boost/thread/concurrent_queues/sync_queue.hpp>
#include <filesystem>
#include <iosfwd>

namespace fs = std::filesystem;

struct FilesystemEntry
{
	using Queue = boost::concurrent::sync_queue<FilesystemEntry>;

	std::string m_filename;
	fs::file_time_type m_lastWriteTime;
	size_t m_sizeInBytes;
};

bool operator == (const FilesystemEntry& lhs, const FilesystemEntry& rhs);

bool operator < (const FilesystemEntry& lhs, const FilesystemEntry& rhs);

std::ostream& operator << (std::ostream& out, const FilesystemEntry& entry);