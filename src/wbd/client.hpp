#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include "typedef.h"
#include "thread.hpp"

class client : public thread
{
public:
	client();
	~client();

private:
	void run();
};

#endif /* _CLIENT_HPP */
