#include <boost/test/unit_test.hpp>
#include "workerPool/WorkerPool.h"
#include "Testdata.h"

class WorkerPoolTestProxy
{
public:
	WorkerPoolTestProxy(size_t numWorker, const std::vector<std::filesystem::path>& paths)
		: m_pool(numWorker, paths)
	{}

	const FilesystemEntry::Queue& OutQueue()
	{
		m_pool.Join();
		return m_pool.m_outQueue;
	}

private:
	WorkerPool m_pool;
};

BOOST_AUTO_TEST_SUITE(workerPool)

BOOST_AUTO_TEST_CASE(poolTest)
{
	WorkerPoolTestProxy proxy{ 2, {test_base_dir / "testfolder"} };
	BOOST_TEST_REQUIRE(proxy.OutQueue().size() == 3);
}

BOOST_AUTO_TEST_CASE(poolStressTest)
{
	//WorkerPoolTestProxy proxy{ std::thread::hardware_concurrency(), {"C:\\"} };
	WorkerPoolTestProxy proxy{ 1, {"C:\\"} };
	BOOST_TEST_REQUIRE(proxy.OutQueue().size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()
