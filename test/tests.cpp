#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include "parray.h"
#include "plist.h"
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(parrayTest)
struct Fixture
{
	persist::parray<int, 5> array = {1, 2, 3, 4, 5};
};
BOOST_FIXTURE_TEST_CASE(testArrayPersistency, Fixture)
{
	array.update(3, 100);
	BOOST_CHECK_EQUAL(array.lookup(3, 0),  4);
	BOOST_CHECK_EQUAL(array.lookup(3, 1),  100);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(plistTest)
struct Fixture
{
	persist::list<int> list = {1, 2, 3, 4, 5};
};

BOOST_FIXTURE_TEST_CASE(testListPersistency, Fixture)
{
	auto it = std::next(list.cbegin(), 2);
	auto inserted = list.insert(it, 100);
	BOOST_CHECK_EQUAL(*std::prev(inserted),  2);
	BOOST_CHECK_EQUAL(*std::next(inserted),  3);

	BOOST_CHECK_EQUAL(*std::prev(it),  2);
	BOOST_CHECK_EQUAL(*std::next(it),  4);
}
BOOST_AUTO_TEST_SUITE_END()