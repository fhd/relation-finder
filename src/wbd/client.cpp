#include "client.h"

Client::Client(int socketDescriptor)
: QThread(), socketDescriptor(socketDescriptor)
{
}

void Client::run()
{
	QTcpSocket s;
	s.setSocketDescriptor(socketDescriptor);

	s.waitForReadyRead();

	quint32 pid = ntohl(*((quint32 *) s.read(sizeof(quint32)).data()));
	quint32 fid = ntohl(*((quint32 *) s.read(sizeof(quint32)).data()));

	vector<quint32> path = find_path(pid, fid);

	quint32 size_n = htonl(path.size());
	s.write((char *) &size_n, sizeof(quint32));

	foreach (quint32 p, path) {
		quint32 node = htonl(p);
		s.write((char *) &node, sizeof(quint32));
	}

	s.waitForBytesWritten();
	s.disconnectFromHost();
}

vector<quint32> Client::find_path(quint32 p1, quint32 p2)
{
	vector<quint32> p;

	/*
	 * TODO:
	 * - quint32 ist ein unsigned int. deine funktionen sollten diesen statt int verwenden
	 * - den vector p mit den ids des pfades füllen, dieser wird dem client gesendet
	 */

	lock.lockForRead();

	timeval start, end;
	gettimeofday(&start, 0);			
	astar(graph, (int) p1, (int) p2);
	gettimeofday(&end, 0);		
	cout << start.tv_sec << ':' << start.tv_usec << endl;
	cout << end.tv_sec << ':' << end.tv_usec << endl;		
	cout << "time: " << end.tv_sec - start.tv_sec << ":" << end.tv_usec - start.tv_usec << endl;
	printf("\nFertig\n");

	lock.unlock();

	return p;
}

int Client::astar(map<int, edge> &graph, int node_start, int node_goal) {
	token node_current;
	map<int, token> open;
	deque<int> openqueue;
	map<int, token> closed;
	int key = 0;
	char path[999] = "";
	int i = 0;	
	open[node_start][0] = 0;			//cost
	open[node_start][1] = node_start;		//last
	open[node_start][2] = node_start;		//self
	openqueue.push_back(node_start);
	while(!open.empty()) {
		i = openqueue.at(0);
		node_current = open[i];		
		openqueue.pop_front();
		open.erase(i);		
		if(node_current[0] > 6) {
			printf("kein pfad\n\n");
			return 1;			
		}		
		if(node_current[2] == node_goal) {
			sprintf(path, "Cost: %i | Pfad: %i ",node_current[0],node_current[2]);
			while(1) {
				sprintf(path, "%s, %i", path,node_current[1]);
				node_current = closed[node_current[1]];
				if(node_current[2] == node_start) {
					printf("PFAD: %s\n\n",path);
					return 0;
				}
			}
		} else {
			for( key = 0; key < (int) graph[node_current[2]][3].size(); key++ ) {
				if(closed[graph[node_current[2]][3][key]].empty() && open[graph[node_current[2]][3][key]].empty()) {
					open[graph[node_current[2]][3][key]][0] = node_current[0]+1;
					open[graph[node_current[2]][3][key]][1] = node_current[2];
					open[graph[node_current[2]][3][key]][2] = graph[node_current[2]][3][key];
					openqueue.push_back(graph[node_current[2]][3][key]);
				} 
			}
			closed[node_current[2]] = node_current;			
		}
	}
	printf("kein pfad\n\n");
	return 1;
}
