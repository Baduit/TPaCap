#include <boost_ut/ut.hpp>

using namespace boost::ut;



void test_dummy()
{
	expect(true) << "dummy test.";
}

int main()
{
	"dummy"_test = test_dummy;
}