#ifndef CLIENT_H
#define CLIENT_H

#include <map>
#include <vector>
#include <functional>
#include <queue>
#include <iostream>
#include <deque>
#include <string>
#include <sys/time.h>
#include <arpa/inet.h>

#include <QtCore>
#include <QtNetwork>
#include "graph.h"

using namespace std;

class Client : public QThread
{
	Q_OBJECT

public:
	Client(int socketDescriptor);
	vector<quint32> find_path(quint32 p1, quint32 p2);
	int astar(map<int, edge> &graph, int node_start, int node_goal);

protected:
	void run();

private:
	int socketDescriptor;
};

#endif
