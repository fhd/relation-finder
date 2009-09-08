#ifndef FETCHER_H
#define FETCHER_H

#include <QtCore>
#include <QtSql>

// database connection settings
#define DB_DRIVER   "QPSQL" 
#define DB_HOST     "localhost"
#define DB_NAME     "fhd"
#define DB_USERNAME "fhd"
#define DB_PASSWD   "fhdpw"

// queries
#define BUDDY_SELECT "SELECT * FROM buddys"
#define IDX_OWNER_NR 0
#define IDX_BUDDY_NR 1

class Fetcher : public QThread
{
	Q_OBJECT

public:
	void fetch_graph();

protected:
	void run();

private:
	QSqlDatabase db;
};

#endif
