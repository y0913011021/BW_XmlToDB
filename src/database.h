#ifndef DATABASE_H
#define DATABASE_H

#include "glb_singleton.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include "QtCore/QString"


/**/
class DataBase
{
public:
    DECL_SINGLETON(DataBase)

    bool open();
    bool close();

    QSqlDatabase getDB();
	bool  IsOpen();
};

#endif // DATABASE_H
