#include "thread.hpp"

void thread::start()
{
	assert(!m_thread);
	m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&thread::run, this)));
	m_thread->join();
}

void thread::wait()
{
	m_thread->join();
}
