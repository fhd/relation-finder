#include "client.h"
#include "server.h"

Server::Server(QObject *parent)
: QTcpServer(parent)
{
}

void Server::incomingConnection(int socketDescriptor)
{
	Client *client = new Client(socketDescriptor);
	connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
	client->start();
}
