#include <boost/test/unit_test.hpp>

namespace fs = std::filesystem;

BOOST_AUTO_TEST_SUITE(worker)

BOOST_AUTO_TEST_CASE(scanFolder0Files)
{
	fs::path folderPath = test_base_dir / "testfolder/0";



	BOOST_TEST(true /* test assertion */);
}

BOOST_AUTO_TEST_SUITE_END()
