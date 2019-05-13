#include "Collector.h"


const std::set<FilesystemEntry>& Collector::GetSortedEntries()
{
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
    collectedEntries.insert(entry);
}
