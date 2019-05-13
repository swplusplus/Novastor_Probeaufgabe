#pragma once

#include "model/FileSystemEntry.h"

#include <boost/lockfree/queue.hpp>
#include <list>

class Collector
{
public:

    Collector(const FilesystemEntry::Queue& outQueue);

    void Run();

    std::list<FilesystemEntry> GetSortedEntries();

};
