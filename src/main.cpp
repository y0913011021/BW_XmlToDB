#include <QCoreApplication>

#include "xml_reader.h"
#include "glb_auxfunc.h"
#include "database.h"


QString MyFile[] = {"getBase","getCounty","getIdentifyInfo","getTask","getTaskType","getTown","getVillage","getIdentify","getShipInfo"};

//extern QString MyFile[];
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	if (DataBase::instance()->open())
	{
		const QString XmlPath = AuxParam::GetAuxParam("FilePath","XmlPath").toString();
		qDebug()<<"XmlPath:"<<XmlPath;
		CXml_Reader reader;
		for(int loop=0;loop<sizeof(MyFile)/sizeof(MyFile[0]);loop++)
		{
			QString XmlFile(XmlPath+"/"+ MyFile[loop]+".xml");
			QFile file(XmlFile);

			if(file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qDebug()<<"File "<<XmlFile<<" load Sucess,Begin Parse!!!";
				reader.read(&file,MyFile[loop]);
			}
			else
			{
				qDebug()<<"File "<<XmlFile<<" Open Failed!!!";
			}
			file.close();
		}
	}
	else qDebug()<<"Open DataBase Failed!!!";
	
	
    if(DataBase::instance()->IsOpen())
            DataBase::instance()->close();
    qDebug()<<"Press ctrl+C to exit...";

    return a.exec();
}

bool testconn()
{
#if 0
    //动态加载oci动态库
    QLibrary *oracle_lib = NULL;
    //oracle_lib = new QLibrary(qApp->applicationDirPath()+"/oracle_lib/instantclient_11_1/oci.dll");
    QString LibPath = "E:/01-Code/BW_XmlToDB/src/oracle_lib/instantclient_11_1/oci.dll";
    //QString LibPath = "D:/01-Code/test_ocidriver_qt4.8.4_ora11G1/oracle_lib/instantclient_11_1/oci.dll";
    QFileInfo file(LibPath);
    if(file.exists()){
        oracle_lib = new QLibrary(LibPath);
    }
    oracle_lib->load();
    if (!oracle_lib->isLoaded())
    {
        qDebug() << "load Oracle failed!\n";
        return -1;
    }
    QList<ST_VIDEO_REORD> listVideoRecord;
    listVideoRecord.clear();

    QString qstrStartTime("2019-05-05 12:12:15");
    QString qstrStopTime("2019-06-18 12:12:15");
    QString qstrIP("192.169.1.170");
    QString qstrQuery;
//    qstrQuery   =   QString("select to_char(start_time,'yyyy-mm-dd hh24:mi:ss') as start_time,to_char(stop_time,'yyyy-mm-dd hh24:mi:ss') as stop_time,url from vts_video_record \
//                      where ip = '%1'and \
//                      (start_time<= to_date('%2','yyyy-mm-dd hh24:mi:ss') and stop_time >= to_date('%3','yyyy-mm-dd hh24:mi:ss') ) or \
//                      (start_time>= to_date('%4','yyyy-mm-dd hh24:mi:ss') and stop_time <= to_date('%5','yyyy-mm-dd hh24:mi:ss') ) or \
//                      (stop_time>= to_date('%6','yyyy-mm-dd hh24:mi:ss') and start_time <= to_date('%7','yyyy-mm-dd hh24:mi:ss') )    \
//                      order by start_time").arg(qstrIP).arg(qstrStartTime).arg(qstrStartTime).arg(qstrStartTime).arg(qstrStopTime).arg(qstrStopTime).arg(qstrStopTime);

    qstrQuery = QString("select * from vts_ais");

    const QString hostName = AuxParam::GetAuxParam("Database", "HostName").toString();
    const QString drvName = AuxParam::GetAuxParam("Database", "DrvName").toString();
    const QString dbName = AuxParam::GetAuxParam("Database", "DbName").toString();
    //const QString connName = AuxParam::GetAuxParam("Database", "ConnName").toString();
    const QString userName = AuxParam::GetAuxParam("Database", "UserName").toString();
    const QString password = AuxParam::GetAuxParam("Database", "Password").toString();
    const int port = AuxParam::GetAuxParam("Database", "Port").toInt();

    db = QSqlDatabase::addDatabase(drvName);
    db.setDatabaseName(dbName);
    db.setHostName(hostName);
    db.setUserName(userName);
    db.setPassword(password);
    db.setPort(port);
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("192.169.1.15");
    db.setPort(1521);
    db.setDatabaseName("orcl");
    db.setUserName("bwdba");
    db.setPassword("123456");*/

    bool ok = db.open();
    if(ok == true)
    {
        qDebug()<<"open database ok";

        QSqlQuery sqlQuery  =    db.exec(qstrQuery);

        if(!db.lastError().isValid())
        {
            qDebug()<<"query success";
            qDebug()<<sqlQuery.isActive();
            qDebug()<<sqlQuery.size();
            while (sqlQuery.next())
            {
                //qDebug() << sqlQuery.value(0).toString()<<";"<<sqlQuery.value(1).toString()<<";"<<sqlQuery.value(2).toString();
                ST_VIDEO_REORD stVideoRecord;
                stVideoRecord.qstrStartTime =   sqlQuery.value(0).toString();
                stVideoRecord.qstrStopTime  =   sqlQuery.value(1).toString();
                stVideoRecord.qstrURL   =   sqlQuery.value(2).toString();
                listVideoRecord.append(stVideoRecord);
            }
        }
        else
        {
            qDebug()<<db.lastError().text()<<" "<<"query failed";
        }
    }
    else
    {
        qDebug()<<db.lastError().text()<<" "<<"open database failed";
    }
#endif
    return 0;
}
