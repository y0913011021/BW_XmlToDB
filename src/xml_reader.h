#ifndef XML_READER_H  
#define XML_READER_H


#include <QtCore>
#include <QSqlQuery>



class CXml_Reader : public QXmlStreamReader
{  
    //Q_OBJECT  
public:  
    CXml_Reader();
	~CXml_Reader();
    bool read(QIODevice *device,QString FileName="");
private:  
    void read_data(QString FileName="");
    void read_period();
    void read_exception();  
    void read_subexception(); 
    void read_event(); 
    void read_eventdesc(); 
    void read_unknow();
	void PrintError(QSqlQuery query);
private:
	void read_Identify_Table();//getIdentify.xml
	void read_County_Table();//getCounty.xml
	void read_ShipInfo_Table();//getShipInfo.xml
	void read_Base_Table();//getBase.xml
	void read_IdentifyInfo_Table();//getIdentifyInfo.xml
	void read_ShipIdAndNameInfo_Table();//getShipIdAndNameInfo.xml
	void read_Task_Table();//getTask.xml
    void read_TaskType_Table();//getTaskType.xml
	void read_Town_Table();//getTown.xml
	void read_Village_Table();//getVillage.xml
	void read_AllMember_Table();//getAllMember.xml
};  
#endif
