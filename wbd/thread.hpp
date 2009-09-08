#ifndef _THREAD_HPP
#define _THREAD_HPP

#include <boost/bind.hpp>
#include <boost/thread.hpp>

class thread
{
public:
	void start();
	void wait();

protected:
	virtual void run() = 0;

private:
	boost::shared_ptr<boost::thread> m_thread;
};

#endif /* _THREAD_HPP */
