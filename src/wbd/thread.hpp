#ifndef THREAD_HPP
#define THREAD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

/** A thread */
class thread
{
public:
	/** Starts the thread */
	void start();

	/** Waits until the thread finishes */
	void wait();

protected:
	/**
	 * This method executes the thread's task.
	 * Subclasses have to implement it.
	 */
	virtual void run() = 0;

private:
	boost::shared_ptr<boost::thread> m_thread;
};

#endif /* THREAD_HPP */
