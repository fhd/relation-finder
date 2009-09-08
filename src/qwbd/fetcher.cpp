#define FETCHER
#include "graph.h"
#include "fetcher.h"

void Fetcher::run()
{
	db = QSqlDatabase::addDatabase(DB_DRIVER);
	db.setHostName(DB_HOST);
	db.setDatabaseName(DB_NAME);
	db.setUserName(DB_USERNAME);
	db.setPassword(DB_PASSWD);
	if (!db.open()) {
		qDebug() << "couldn't connect to database.";
		return;
	}

	edge_count = 0;
	node_start = 0;
	node_goal = 0;

	forever {
		lock.lockForWrite();

		fetch_graph();

		lock.unlock();

		sleep(5 * 60);
	}
}

void Fetcher::fetch_graph()
{

	QSqlQuery query;
	query.exec(BUDDY_SELECT);

	while (query.next()) {
		graph[query.value(IDX_OWNER_NR).toInt()][3].push_back(query.value(IDX_BUDDY_NR).toInt());
		graph[query.value(IDX_OWNER_NR).toInt()][2].push_back(query.value(IDX_OWNER_NR).toInt());
		graph[query.value(IDX_BUDDY_NR).toInt()][3].push_back(query.value(IDX_OWNER_NR).toInt());
		graph[query.value(IDX_BUDDY_NR).toInt()][2].push_back(query.value(IDX_BUDDY_NR).toInt());
		edge_count += 2;
	}
}
