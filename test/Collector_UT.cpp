#include "collector/Collector.h"

#include <boost/test/unit_test.hpp>
#include <list>


BOOST_AUTO_TEST_SUITE(collector)

BOOST_AUTO_TEST_CASE(sorting_test, *boost::unit_test::timeout(2))
{
	using namespace std::chrono_literals;
	using E = FilesystemEntry;
	using D = fs::file_time_type;
	FilesystemEntry::Queue queue;
	Collector collector;

	// std::string m_filename;
	// fs::file_time_type m_lastWriteTime;
	// size_t m_sizeInBytes;
	std::list<FilesystemEntry> entries = {
		E{"h", D{1s}, 1},
		E{"s", D{2s}, 1},
		E{"f", D{3s}, 1},
		E{"a", D{4s}, 1},
		E{"s", D{5s}, 1},
		E{"g", D{6s}, 1},
		E{"s", D{7s}, 1}
	};
	for (const auto& e: entries)
	{
		queue.push(e);
	}
	queue.close();
	collector.Run(queue);
	entries.sort();
	std::list<FilesystemEntry> result = collector.GetSortedEntries();

	BOOST_TEST(entries == result, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_SUITE_END()
