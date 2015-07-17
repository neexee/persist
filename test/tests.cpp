#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include "parray.h"
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
