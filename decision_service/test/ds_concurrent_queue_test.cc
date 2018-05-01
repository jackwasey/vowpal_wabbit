#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif

#include "../src/ds_concurrent_queue.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(push_pop)
{
    decision_service::concurrent_queue<std::string> queue;

    //push n elements in the queue
    int n = 10;
    for (int i=0; i<n; ++i)
        queue.push(std::to_string(i+1));

    BOOST_CHECK_EQUAL(queue.size(), n);

    //pop front
	std::string item;
	queue.pop(&item);
	BOOST_CHECK_EQUAL(item, std::string("1"));

    //pop all
    while (queue.size()>0)
        queue.pop(&item);

    //check last item
    BOOST_CHECK_EQUAL(item, std::to_string(n));

	//check queue size
	BOOST_CHECK_EQUAL(queue.size(), 0);    
}

BOOST_AUTO_TEST_CASE(pop_empty)
{
	decision_service::concurrent_queue<int> queue;
	BOOST_REQUIRE(queue.size() == 0);

	//the pop call on an empty queue should do nothing
    int item = -1;
	queue.pop(&item);
	BOOST_CHECK_EQUAL(item, -1);
	BOOST_CHECK_EQUAL(queue.size(), 0);
}