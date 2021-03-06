    #include "FilesystemEntry.h"
#include <string_view>
#include <tuple>
#include <time.h>

namespace
{
#ifdef _WIN32
	constexpr auto SEC_TO_UNIX_EPOCH = 11644473600LL;
    #define localtime_fun(time_t, tm) localtime_s(time_t, tm)
#else
	constexpr auto SEC_TO_UNIX_EPOCH = -6437664000LL;
    #define localtime_fun(time_t, tm) localtime_r(tm, time_t)
#endif
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
    time_t tt = std::chrono::duration_cast<seconds>(entry.m_lastWriteTime.time_since_epoch()).count() - SEC_TO_UNIX_EPOCH;
    struct tm stm;
    localtime_fun(&stm, &tt);
    size_t bs = 26;
    std::unique_ptr<char[]> buf{new char[bs]};
    while (strftime(buf.get(), bs, "%FT%T%z", &stm) == 0 && bs < 1000)
    {
        bs *=2;
        buf.reset(new char[bs]);
    }
    out << '"' << entry.m_filename << "\" ; "sv << buf.get() << " ; "sv << entry.m_sizeInBytes;
	return out;
}
