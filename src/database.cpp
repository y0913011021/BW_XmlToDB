#include "database.h"
#include "glb_auxfunc.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLibrary>


static QSqlDatabase database;

bool OpenDB()
{
    QLibrary *oracle_lib = NULL;

    //QDir    dir;
    //QString runPath = dir.currentPath();
    //qDebug()<<"runPath1:"<<runPath;
	qDebug()<<"runPath2:"<<qApp->applicationDirPath();
	//QString LibPath = dir.currentPath()+"/oracle_lib/instantclient_11_1/oci.dll";
	QString LibPath = qApp->applicationDirPath()+"/oracle_lib/instantclient_11_1/oci.dll";
    QFileInfo file(LibPath);
    if(file.exists()) {
        oracle_lib = new QLibrary(LibPath);
    } else {
        qDebug()<<LibPath<<" "<<"is not exist!!!";
        return false;
    }

    oracle_lib->load();
    if (!oracle_lib->isLoaded())
    {
        qDebug() << "load Oracle failed!\n";
        return false;
    }

#if 1
    const QString hostName = AuxParam::GetAuxParam("Database", "HostName").toString();
    const QString drvName = AuxParam::GetAuxParam("Database", "DrvName").toString();
    const QString dbName = AuxParam::GetAuxParam("Database", "DbName").toString();
    //const QString connName = AuxParam::GetAuxParam("Database", "ConnName").toString();
    const QString userName = AuxParam::GetAuxParam("Database", "UserName").toString();
    const QString password = AuxParam::GetAuxParam("Database", "Password").toString();
    const int port = AuxParam::GetAuxParam("Database", "Port").toInt();
	if (QSqlDatabase::contains("qt_sql_default_connection")) 
		database = QSqlDatabase::database("qt_sql_default_connection");
	else database = QSqlDatabase::addDatabase(drvName); 
    
    database.setDatabaseName(dbName);
    database.setHostName(hostName);
    database.setUserName(userName);
    database.setPassword(password);
    database.setPort(port);
#endif


    bool res = database.open();
    if (res)
    {
        qDebug()<<"open database ok";
#if 0
		QString sql("select * from TB_COUNTY");
		bool ret = g_query.exec(sql);
		qDebug()<<"query is sucess:"<<ret;
		while(g_query.next())
		{
			QString Temp0 = g_query.value(0).toString();
			QString Temp1 = g_query.value(1).toString();
			qDebug()<<Temp0<<" "<<Temp1;
		}
		g_query.prepare("INSERT INTO TB_COUNTY(ID,MC) VALUES(:ID,:MC)");
		g_query.addBindValue(QString("00015"));
		g_query.addBindValue(QString("¹þ¹þ¹þ"));
		g_query.exec();
#endif
    }
    return res;
}


bool CloseDB()
{
    database.close();
    return true;
}

IMPL_SINGLETON(DataBase)


bool DataBase::open()
{
    return OpenDB();
}

bool DataBase::close()
{
    return CloseDB();
}

QSqlDatabase DataBase::getDB()
{
    return database;
}

bool DataBase::IsOpen()
{
	return database.isOpen();
}

