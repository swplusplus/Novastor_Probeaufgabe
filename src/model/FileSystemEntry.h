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

inline bool operator == (const FilesystemEntry& lhs, const FilesystemEntry& rhs)
{
	throw std::runtime_error("bool operator == (const FilesystemEntry& lhs, const FilesystemEntry& rhs): not yet implemented!");
	return false;
}

inline bool operator < (const FilesystemEntry& lhs, const FilesystemEntry& rhs)
{
	throw std::runtime_error("bool operator < (const FilesystemEntry& lhs, const FilesystemEntry& rhs): not yet implemented!");
	return false;
}

inline std::ostream& operator << (std::ostream& out, const FilesystemEntry& entry)
{
	throw std::runtime_error("std::ostream& operator << (std::ostream& out, const FilesystemEntry& entry): not yet implemented!");
	return out;
}
