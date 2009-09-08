#include <iostream>
#include <QCoreApplication>
#include <QtNetwork>
#include <arpa/inet.h>

#define HOST "localhost"
#define PORT 8888

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	quint32 pid, fid;
	cout << "please tell me your id: ";
	cin >> pid;
	cout << "tell me your friend's id: ";
	cin >> fid;

	QTcpSocket *s = new QTcpSocket;
	s->connectToHost(HOST, PORT);

	if (!s->waitForConnected()) {
		cerr << "connection failed." << endl;
		return 1;
	}

	quint32 pid_n = htonl(pid);
	quint32 fid_n = htonl(fid);
	s->write((char *) &pid_n, sizeof(quint32));
	s->write((char *) &fid_n, sizeof(quint32));

	s->waitForBytesWritten();

	s->waitForReadyRead();
	quint32 n_nodes = ntohl(*((quint32 *) s->read(sizeof(quint32)).data()));
	cout << "there are " << n_nodes << " nodes";

	if (n_nodes)
		cout << ":";

	for (quint32 i = 0; i < n_nodes; i++) {
		quint32 node = *((quint32 *) s->read(sizeof(quint32)).data());
		cout << " " << node;
	}

	cout << endl;

	return 0;
}
