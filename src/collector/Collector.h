#pragma once

#include "model/FilesystemEntry.h"

#include <boost/lockfree/queue.hpp>
#include <set>

class Collector
{
public:
    void Run(FilesystemEntry::Queue& outQueue);

    const std::set<FilesystemEntry>& GetSortedEntries();
private:
    void Process(FilesystemEntry&& entry);

    std::set<FilesystemEntry> collectedEntries;
};
