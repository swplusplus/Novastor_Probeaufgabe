#pragma once

#include "model/FilesystemEntry.h"

#include <boost/lockfree/queue.hpp>
#include <set>

class Collector
{
public:
	// pulls all items from the outQueue and sorts them by inserting them into a std::set.
    void Run(FilesystemEntry::Queue& outQueue);

    const std::set<FilesystemEntry>& GetSortedEntries();
private:
    void Process(FilesystemEntry&& entry);

    std::set<FilesystemEntry> collectedEntries;
};
