#pragma once

namespace fs = std::filesystem;

struct FilesystemEntry
{
	std::string m_filename;
	fs::file_time_type m_lastWriteTime;
	size_t m_sizeInBytes;
};