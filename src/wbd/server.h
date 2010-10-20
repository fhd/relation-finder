#ifndef SERVER_H
#define SERVER_H

#define PORT 8888

#include <QtCore>
#include <QtNetwork>

class Server : public QTcpServer
{
	Q_OBJECT

public:
	Server(QObject *parent = NULL);

protected:
	void incomingConnection(int socketDescriptor);
};

#endif
