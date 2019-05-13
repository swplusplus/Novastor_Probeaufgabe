#include <boost/test/unit_test.hpp>
#include <filesystem>
#include "Testdata.h"
#include "worker/LocalFilesystemWorker.h"

namespace fs = std::filesystem;

struct TestFixture
{
	LocalFilesystemWorker::WorkQueue workQueue;
	FilesystemEntry::Queue outQueue;
};

void CompareEntries(const FilesystemEntry& e1, const FilesystemEntry& e2)
{
	BOOST_TEST(e1.m_filename == e2.m_filename);
	BOOST_TEST(e1.m_sizeInBytes == e2.m_sizeInBytes);
}

BOOST_AUTO_TEST_SUITE(worker, *boost::unit_test::timeout(10))

BOOST_FIXTURE_TEST_CASE(scanFolder0Files, TestFixture)
{
	fs::path folderPath = test_base_dir / "testfolder/0";

	LocalFilesystemWorker worker;

	BOOST_CHECK_NO_THROW(worker.Work(folderPath, workQueue, outQueue));
	BOOST_TEST(workQueue.empty());
	BOOST_TEST(outQueue.empty());
}

BOOST_FIXTURE_TEST_CASE(scanFolder1File, TestFixture)
{
	fs::path folderPath = test_base_dir / "testfolder/1";

	LocalFilesystemWorker worker;

	BOOST_CHECK_NO_THROW(worker.Work(folderPath, workQueue, outQueue));
	BOOST_TEST(workQueue.empty());
	BOOST_TEST_REQUIRE(outQueue.size() == 1);

	CompareEntries({ (folderPath / "1.txt").string(), fs::file_time_type {}, 0 }, outQueue.pull());
}

BOOST_FIXTURE_TEST_CASE(scanFolder2Files, TestFixture)
{
	fs::path folderPath = test_base_dir / "testfolder/2";

	LocalFilesystemWorker worker;

	BOOST_CHECK_NO_THROW(worker.Work(folderPath, workQueue, outQueue));
	BOOST_TEST(workQueue.empty());
	BOOST_TEST_REQUIRE(outQueue.size() == 2);

	CompareEntries({ (folderPath / "1").string(), fs::file_time_type {}, 0 }, outQueue.pull());
	CompareEntries({ (folderPath / "2.2").string(), fs::file_time_type {}, 0 }, outQueue.pull());
}


BOOST_FIXTURE_TEST_CASE(scanFolderWithSubfolders, TestFixture)
{
	fs::path folderPath = test_base_dir / "testfolder";

	LocalFilesystemWorker worker;

	BOOST_CHECK_NO_THROW(worker.Work(folderPath, workQueue, outQueue));
	BOOST_TEST_REQUIRE(workQueue.size() == 3);
	BOOST_TEST(outQueue.empty());

	while (!workQueue.empty())
	{
		auto w = workQueue.pull();
		BOOST_CHECK_NO_THROW(worker.Work(w, workQueue, outQueue));
	}

	BOOST_TEST_REQUIRE(outQueue.size() == 3);
	CompareEntries({ (folderPath / "1" / "1.txt").string(), fs::file_time_type {}, 0 }, outQueue.pull());
	CompareEntries({ (folderPath / "2" / "1").string(), fs::file_time_type {}, 0 }, outQueue.pull());
	CompareEntries({ (folderPath / "2" / "2.2").string(), fs::file_time_type {}, 0 }, outQueue.pull());
}

BOOST_AUTO_TEST_SUITE_END()
