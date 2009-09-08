#include <QCoreApplication>
#include <QtCore>
#include <QtSql>

// database connection settings
#define DB_DRIVER   "QPSQL" 
#define DB_HOST     "localhost"
#define DB_NAME     "fhd"
#define DB_USERNAME "fhd"
#define DB_PASSWD   "fhd"

// queries
#define BUDDYS_DROP "DROP TABLE buddys"
#define BUDDYS_CREATE "\
CREATE TABLE buddys (\
  owner_nr integer NOT NULL,\
  buddy_nr integer NOT NULL,\
  CONSTRAINT buddys_pkey\
  PRIMARY KEY (owner_nr, buddy_nr)\
) WITHOUT OIDS\
"
#define BUDDYS_INDEX "\
CREATE INDEX buddy ON buddys USING btree (buddy_nr)\
CREATE INDEX buddy_owner ON buddys USING btree (owner_nr, buddy_nr)\
CREATE UNIQUE INDEX buddys_pkey ON buddys USING btree (owner_nr, buddy_nr)\
"
#define BUDDYS_INSERT "INSERT INTO buddys (owner_nr, buddy_nr) VALUES (%1, %2)"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	QSqlDatabase db = QSqlDatabase::addDatabase(DB_DRIVER);
	db.setHostName(DB_HOST);
	db.setDatabaseName(DB_NAME);
	db.setUserName(DB_USERNAME);
	db.setPassword(DB_PASSWD);
	if (!db.open()) {
		qCritical() << "Database connection failed";
		return 1;
	}

	QSqlQuery query;
	query.exec(BUDDYS_DROP);
	query.exec(BUDDYS_CREATE);
	query.exec(BUDDYS_INDEX);

	int fid;
	for(int i = 1; i < 30000; i++)
		for(int j = 1; j < 20; j++) {
			while((fid = (qrand()%30000)+1) == i);
			query.exec(QString(BUDDYS_INSERT).arg(i).arg(fid));
			qDebug() << "insert: " << i << " -> " << fid;
		}

	return app.exec();
}
