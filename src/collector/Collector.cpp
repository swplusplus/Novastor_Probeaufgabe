#include "Collector.h"

Collector::Collector()
{}


std::list<FilesystemEntry> Collector::GetSortedEntries()
{
    collectedEntries.sort();
    return collectedEntries;
}

void Collector::Run(FilesystemEntry::Queue& outQueue)
{
    try
    {
        while (true)
        {
            Process(outQueue.pull());
        }
    }
    catch(const boost::concurrent::sync_queue_is_closed& e)
    {}
}

void Collector::Process(FilesystemEntry&& entry)
{
    collectedEntries.emplace_back(entry);
}
