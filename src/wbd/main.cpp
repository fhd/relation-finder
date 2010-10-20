#include <QCoreApplication>

#include "fetcher.h"
#include "server.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	int argno = 0, port = PORT;

	foreach (QString arg, app.arguments()) {
		if (arg == "-port")
			port = app.arguments().at(argno+1).toInt();
		argno++;
	}

	Fetcher fetcher;
	fetcher.start();

	// wait for possible error
	if (fetcher.wait(100))
		return(1);

	Server server;
	server.listen(QHostAddress::Any, port);

	return app.exec();
}
