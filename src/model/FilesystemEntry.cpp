#include "FilesystemEntry.h"
#include <string_view>
#include <tuple>

namespace
{
    template <typename... T>
    auto creftuple(const T&... p)
    {
        return std::make_tuple(std::cref(p)...);
    }

    auto ascreftuple(const FilesystemEntry& entry)
    {
        return creftuple(entry.m_filename, entry.m_lastWriteTime, entry.m_sizeInBytes);
    }
}

bool operator == (const FilesystemEntry& lhs, const FilesystemEntry& rhs)
{
	return ascreftuple(lhs) == ascreftuple(rhs);
}

bool operator < (const FilesystemEntry& lhs, const FilesystemEntry& rhs)
{
	return ascreftuple(lhs) < ascreftuple(rhs);

}

std::ostream& operator << (std::ostream& out, const FilesystemEntry& entry)
{
    using std::chrono::seconds;
    using namespace std::literals::string_view_literals;
    time_t tt = std::chrono::duration_cast<seconds>(entry.m_lastWriteTime.time_since_epoch()).count();
    struct tm stm; 
    localtime_s(&stm, &tt);
    size_t bs = strftime(nullptr, 0, "%FT%T+%z", &stm);
    std::unique_ptr<char[]> buf{new char[bs]};
    strftime(buf.get(), bs, "%FT%T+%z", &stm); 
    out << '"' << entry.m_filename << "\" ; "sv << buf << " ; "sv << entry.m_sizeInBytes;
	return out;
}
