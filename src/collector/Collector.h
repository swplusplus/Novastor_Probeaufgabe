#pragma once

#include "model/FilesystemEntry.h"

#include <boost/lockfree/queue.hpp>
#include <list>

class Collector
{
public:

    Collector();

    void Run(FilesystemEntry::Queue& outQueue);

    std::list<FilesystemEntry> GetSortedEntries();
private:
    void Process(FilesystemEntry&& entry);

    std::list<FilesystemEntry> collectedEntries;
};
