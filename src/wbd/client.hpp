#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "thread.hpp"

/** A thread handling a client */
class client : public thread
{
public:
	/** Constructor */
	client();

	/** Destructor */
	~client();

private:
	void run();
};

#endif /* CLIENT_HPP */
