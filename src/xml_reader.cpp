

#include "xml_reader.h" 
#include "Define.h"
#include "database.h"

#include <QSqlError>
#include <QSqlDatabase>

CXml_Reader::CXml_Reader()
{
}
CXml_Reader::~CXml_Reader()
{
	if (DataBase::instance()->IsOpen())
	{
		DataBase::instance()->close();
	}
}

bool CXml_Reader::read(QIODevice *device,QString FileName)
{
    setDevice(device);
	//DataBase::instance()->open();
    QSqlQuery query;
    while(!atEnd())  
    {
        readNext();
        if(isStartElement())  
        { 
            if(name() == "NewDataSet")  
            {  
				if ("getCounty" == FileName)//Delete Data
				{
					//DataBase::instance()->open();

					query.exec("TRUNCATE TABLE TB_COUNTY");
				}
				else if ("getBase" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_BASE");
				}
				else if ("getIdentify" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_IDENTIFY");
				}
				else if ("getIdentifyInfo" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_IDENTITY_INFO");
				}
				else if ("getTask" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_TASK");
				}
				else if ("getTaskType" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_TASKTYPE");
				}
				else if ("getTown" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_TOWN");
				}
				else if ("getVillage" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_VILLAGE");
				}
				else if ("getShipInfo" == FileName)
				{
					//DataBase::instance()->open();
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TA_FISHERINFO");
				}
#if 0
				else if ("getAllMember" == FileName)
				{
					return true;
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_IDENTIFY");
				}
				else if ("getIdentify" == FileName)
				{
                    //QSqlQuery query;
					query.exec("TRUNCATE TABLE TB_IDENTIFY");
				}
#endif
                query.finish();
                read_data(FileName);
				//DataBase::instance()->close();
            }  
        }

		if(isEndElement())  
		{  
			if( "NewDataSet" == name())  
			{  

				//qDebug()<<"Oprate Table "<<FileName<<" Sucess!!";
				//DataBase::instance()->close();
				//break;  
			}  
		}  
    } 
	//DataBase::instance()->close();
	qDebug()<<"Operate Table "<<FileName<<" Done!!!";
    return !error();  
}
void CXml_Reader::read_data(QString FileName)
{  
    qDebug()<<"Start to read table "<<FileName;  
    while(!atEnd())  
    {  
        readNext();  
        if(isStartElement())  
        {  
			if ("Table" == name())
			{
                if("getBase" == FileName) read_Base_Table();
                if("getCounty" == FileName) read_County_Table();
                if("getIdentifyInfo" == FileName) read_IdentifyInfo_Table();
                //if("getShipIdAndNameInfo" == FileName) read_ShipIdAndNameInfo_Table();
                if("getTask" == FileName) read_Task_Table();
                if("getTaskType" == FileName) read_TaskType_Table();
                if("getTown" == FileName) read_Town_Table();
                if("getVillage" == FileName) read_Village_Table();
                if("getIdentify" == FileName) read_Identify_Table();
                if("getShipInfo" == FileName) read_ShipInfo_Table();
                //if("getAllMember" == FileName) read_AllMember_Table();
			}
        }

        if(isEndElement())  
        {  
            if(name() == "Table")  
            {  
                //qDebug()<<"Now at the end of data element...";  
                //break;  
            }  
        }  
    }  
}  

void CXml_Reader::read_period()
{  
    qDebug()<<"Start to read period...";  
    while(!atEnd())  
    {  
        readNext();  
        if(isStartElement())  
        {  
            if(name() == "exception")  
            {  
                read_exception();  
            }
            if(name() == "event")  
            {  
                read_event();  
            }  
        }  
        if(isEndElement())  
        {  
            if(name() == "period")  
            {  
            qDebug()<<"Now at the end of period...";  
            break;  
            }  
        }  
    }  
}  
void CXml_Reader::read_County_Table()
{
	//qDebug()<<"Start to read Table...";  
	QSqlQuery query;
	QString CountyID,CountyMC;
	while(!atEnd())  
	{ 
		readNext();  
		if(isStartElement())  
		{  
			if ("ID" == name())
			{
				CountyID = readElementText();
			}
			else if ("MC" == name())
			{
				CountyMC = readElementText();
			}
#if 0
			for(int loop=0;loop<sizeof(County_Field)/sizeof(County_Field[0]);loop++)
			{
				if (County_Field[loop] == name())
				{
					qDebug()<<"read_County_Table "<<County_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
#endif
		}  

		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of Table...";
				//Insert Data
				query.prepare("INSERT INTO TB_COUNTY(ID,MC) VALUES(:ID,:MC)");
				query.addBindValue(CountyID);
				query.addBindValue(CountyMC);
				if (!query.exec())this->PrintError(query);
				query.finish();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_Identify_Table()
{
	//qDebug()<<"Start to read getIdentify Table...";
	QSqlQuery query;
	QString Identify_FID,Identity_TypeID,Identity_Value;
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{
			if ("SI_FID" == name())
			{
				Identify_FID = readElementText();
			}
			else if ("SI_TypeID" == name())
			{
				Identity_TypeID = readElementText();
			}
			else if ("SI_Value" == name())
			{
				Identity_Value = readElementText();
			}
#if 0
			for (int loop=0;loop<sizeof(Identify_Field)/sizeof(Identify_Field[0]);loop++)
			{
				if(Identify_Field[loop] == name())  
				{  
					qDebug()<<"read_Identify_Table "<<Identify_Field[loop]<<" is: "<< readElementText();
					break;
				}  
			}
#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getIdentify Table...";
				query.prepare("INSERT INTO TB_IDENTIFY(SI_FID,SI_TypeID,SI_Value) VALUES(:SI_FID,:SI_TypeID,:SI_Value)");
				query.addBindValue(Identify_FID);
				query.addBindValue(Identity_TypeID);
				query.addBindValue(Identity_Value);
				if(!query.exec())this->PrintError(query);
				query.finish();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_ShipInfo_Table()
{
	//qDebug()<<"Start to read getShipInfo Table...";
	QSqlQuery query;
	QString ShipInfo_ID,ShipInfo_COUNTYID,ShipInfo_TOWNID,ShipInfo_VILLAGEID,ShipInfo_FISHERNAME,ShipInfo_FISHERHOMELAND,ShipInfo_FISHERTYPE,\
		ShipInfo_FISHERSTUFF,ShipInfo_TASKTYPE,ShipInfo_TASKMODE,ShipInfo_TASKTRAIT,ShipInfo_BUILDPLACE,ShipInfo_BUILDERNAME;
	
	int ShipInfo_RADIO = 0;
	
	int ShipInfo_AIRDOOR,ShipInfo_SAFETYPERSON;

	QString /*ShipInfo_ISDIS("0"),*/ShipInfo_RADIOISHAVE("1"),ShipInfo_ISTHREECARD("1");//char(1)
	QString ShipInfo_ISDIS,ShipInfo_ISQUERY,ShipInfo_MOORSHIP,ShipInfo_SAILORCOMPETENT;//char(1)

	QString ShipInfo_RADIOLICENSEID,ShipInfo_OWNERNAME,ShipInfo_OWNERADDR,ShipInfo_OWNERMOBILE,ShipInfo_OWNERPHONE,ShipInfo_TESTNUM,ShipInfo_LOGONNUM,\
			ShipInfo_GAINALLOW,ShipInfo_SAFETYCOMPANY,ShipInfo_IMAGE,ShipInfo_SAILORSAFE,ShipInfo_APPROVETASK,ShipInfo_SHIPGRADE,\
			ShipInfo_BLACKSHIP,ShipInfo_SAFEMEMBER,ShipInfo_SAFEMEMBERPHONE,ShipInfo_SHIPGROUP,ShipInfos_MOOREXPLAIN,ShipInfo_SATELLITICPHONE;
	
	float	ShipInfo_FISHERLENGTH,ShipInfo_FISHERWIDTH,ShipInfo_FISHERDEPTH,ShipInfo_TOTALTON,ShipInfo_MINETON,ShipInfo_MAINPOWER,ShipInfo_SAFETYMONEY,ShipInfo_TOTALLENGTH;
	
	QString ShipInfo_BUILDTIME,ShipInfo_TESTUSEDTIME,ShipInfo_LOGONUSEDTIME,ShipInfo_GAINALLOWUSEDTIME,ShipInfo_SAFETYTIME,\
				ShipInfo_RADIOUSEDTIME,ShipInfo_TIME,ShipInfo_SAFETYPERSONTIME;



	//=====无====
	//CString ShipInfo_USEDID = "",ShipInfo_NUM = "",ShipInfo_VOICECARD = "",ShipInfo_FORMERLY = "",ShipInfo_CAPTIONNAME = "",ShipInfo_VOICENUM = "";
	//int ShipInfo_SAILORNUM,ShipInfo_SHIP_ID;
	//=====无====
	bool ok = false;
	while(!atEnd())  
	{
		readNext();
		if(isStartElement())  
		{
			if ("ID" == name()) ShipInfo_ID = readElementText();////ID
			else if ("FI_CountyID" == name()) ShipInfo_COUNTYID = readElementText();////FI_COUNTYID
			else if ("FI_TownID" == name()) ShipInfo_TOWNID = readElementText();////FI_TOWNID
			else if ("FI_VillageID" == name()) ShipInfo_VILLAGEID = readElementText();////FI_VILLAGEID	
			else if ("FI_FisherName" == name()) ShipInfo_FISHERNAME = readElementText();////FI_FISHERNAME			
			else if ("FI_FisherHomeLand" == name()) ShipInfo_FISHERHOMELAND = readElementText();////FI_FISHERHOMELAND			
			else if ("FI_FisherType" == name()) ShipInfo_FISHERTYPE = readElementText();////FI_FISHERTYPE			
			else if ("FI_FisherStuff" == name()) ShipInfo_FISHERSTUFF = readElementText();////FI_FISHERSTUFF			
			else if ("FI_TaskType" == name()) ShipInfo_TASKTYPE = readElementText();////FI_TASKTYPE			
			else if ("FI_TaskMode" == name())ShipInfo_TASKMODE = readElementText();////FI_TASKMODE			
			else if ("FI_TaskTrait" == name()) ShipInfo_TASKTRAIT = readElementText();////FI_TASKTRAIT			
			else if ("FI_BuildPlace" == name()) ShipInfo_BUILDPLACE = readElementText();////FI_BUILDPLACE			
			else if ("FI_BuilderName" == name())ShipInfo_BUILDERNAME = readElementText();////FI_BUILDERNAME	
			else if ("FI_BuildTime" == name()) 
			{
				ShipInfo_BUILDTIME = readElementText();//FI_BUILDTIME,(TIMESTAMP(6))
				ShipInfo_BUILDTIME =  ShipInfo_BUILDTIME.replace("T"," ");
				int index = ShipInfo_BUILDTIME.indexOf(".");
				ShipInfo_BUILDTIME = ShipInfo_BUILDTIME.left(index);
			}
			else if ("FI_FisherLength" == name()) ShipInfo_FISHERLENGTH = readElementText().toFloat();//FI_FISHERLENGTH,NUMBER(10,2),			
			else if ("FI_FisherWidth" == name()) ShipInfo_FISHERWIDTH = readElementText().toFloat();//FI_FISHERWIDTH,NUMBER(10,2),			
			else if ("FI_FisherDepth" == name()) ShipInfo_FISHERDEPTH = readElementText().toFloat();//FI_FISHERDEPTH,NUMBER(10,2),			
			else if ("FI_TotalTon" == name()) ShipInfo_TOTALTON = readElementText().toFloat();//FI_TOTALTON,NUMBER(10,2),			
			else if ("FI_MineTon" == name()) ShipInfo_MINETON = readElementText().toFloat();//FI_MINETON,NUMBER(10,2),			
			else if ("FI_MainPower" == name()) ShipInfo_MAINPOWER = readElementText().toFloat();//FI_MAINPOWER,NUMBER(10,2),			
			else if ("FI_Radio" == name()) ShipInfo_RADIO = readElementText().toInt(&ok,10);//FI_RADIO,INTEGER default 0,
			else if ("FI_RadioLicenseID" == name()) ShipInfo_RADIOLICENSEID = readElementText();//FI_RADIOLICENSEID		
			else if ("FI_AirDoor" == name()) ShipInfo_AIRDOOR = readElementText().toInt(&ok,10);//FI_AIRDOOR,INTEGER,		
			else if ("FI_OwnerName" == name()) ShipInfo_OWNERNAME = readElementText();//FI_OWNERNAME			
			else if ("FI_OwnerAddr" == name()) ShipInfo_OWNERADDR = readElementText();//FI_OWNERADDR		
			else if ("FI_OwnerMobile" == name()) ShipInfo_OWNERMOBILE = readElementText();//FI_OWNERMOBILE		
			else if ("FI_OwnerPhone" == name()) ShipInfo_OWNERPHONE = readElementText();//FI_OWNERPHONE
			else if ("FI_TestNum" == name()) ShipInfo_TESTNUM = readElementText();//FI_TESTNUM
			else if ("FI_TestUsedTime" == name())
			{
				ShipInfo_TESTUSEDTIME = readElementText();//FI_TESTUSEDTIME,TIMESTAMP(6),
				ShipInfo_TESTUSEDTIME = ShipInfo_TESTUSEDTIME.replace("T"," ");
				ShipInfo_TESTUSEDTIME = ShipInfo_TESTUSEDTIME.left(ShipInfo_TESTUSEDTIME.indexOf("."));
			}
			else if ("FI_LogonNum" == name()) ShipInfo_LOGONNUM = readElementText();//FI_LOGONNUM			
			else if ("FI_LogonUsedTime" == name()) 
			{
				ShipInfo_LOGONUSEDTIME = readElementText();//FI_LOGONUSEDTIME,TIMESTAMP(6),
				ShipInfo_LOGONUSEDTIME = ShipInfo_LOGONUSEDTIME.replace("T"," ");
				ShipInfo_LOGONUSEDTIME = ShipInfo_LOGONUSEDTIME.left(ShipInfo_LOGONUSEDTIME.indexOf("."));
			}
			else if ("FI_GainAllow" == name()) ShipInfo_GAINALLOW = readElementText();//FI_GAINALLOW			
			else if ("FI_GainAllowUsedTime" == name()) 
			{
				ShipInfo_GAINALLOWUSEDTIME = readElementText();//FI_GAINALLOWUSEDTIME,TIMESTAMP(6),	
				ShipInfo_GAINALLOWUSEDTIME = ShipInfo_GAINALLOWUSEDTIME.replace("T", " ");
				ShipInfo_GAINALLOWUSEDTIME = ShipInfo_GAINALLOWUSEDTIME.left(ShipInfo_GAINALLOWUSEDTIME.indexOf("."));
			}
			else if ("FI_SafetyCompany" == name()) ShipInfo_SAFETYCOMPANY = readElementText();//FI_SAFETYCOMPANY			
			else if ("FI_SafetyTime" == name()) 
			{
				ShipInfo_SAFETYTIME = readElementText();//FI_SAFETYTIME,TIMESTAMP(6),
				ShipInfo_SAFETYTIME = ShipInfo_SAFETYTIME.replace("T"," ");
				ShipInfo_SAFETYTIME = ShipInfo_SAFETYTIME.left(ShipInfo_SAFETYTIME.indexOf("."));
			}
			else if ("FI_Image" == name()) ShipInfo_IMAGE = readElementText();//FI_IMAGE
			else if ("FI_IsDis" == name()) ShipInfo_ISDIS = readElementText();//FI_ISDIS,CHAR(1) default 0		
			else if ("FI_RadioUsedTime" == name()) 
			{
				ShipInfo_RADIOUSEDTIME = readElementText();//FI_RADIOUSEDTIME,TIMESTAMP(6),
				ShipInfo_RADIOUSEDTIME = ShipInfo_RADIOUSEDTIME.replace("T"," ");
				ShipInfo_RADIOUSEDTIME = ShipInfo_RADIOUSEDTIME.left(ShipInfo_RADIOUSEDTIME.indexOf("."));
			}
			else if ("FI_SafetyMoney" == name()) ShipInfo_SAFETYMONEY = readElementText().toFloat();//FI_SAFETYMONEY,NUMBER(10,2),			
			else if ("FI_RadioIsHave" == name()) ShipInfo_RADIOISHAVE = readElementText();//FI_RADIOISHAVE,CHAR(1) default 1,			
			else if ("FI_IsThreeCard" == name()) ShipInfo_ISTHREECARD = readElementText();//FI_ISTHREECARD,CHAR(1) default 1,			
			else if ("time" == name())
			{
				ShipInfo_TIME = readElementText();//TIME,TIMESTAMP(6),
				ShipInfo_TIME = ShipInfo_TIME.replace("T"," ");
				ShipInfo_TIME = ShipInfo_TIME.left(ShipInfo_TIME.indexOf("."));
			}
			else if ("FI_TotalLength" == name()) ShipInfo_TOTALLENGTH = readElementText().toFloat();//FI_TOTALLENGTH,NUMBER(10,2),			
			else if ("FI_SailorSafe" == name()) ShipInfo_SAILORSAFE = readElementText();//FI_SAILORSAFE,			
			else if ("FI_SafetyPerson" == name()) ShipInfo_SAFETYPERSON = readElementText().toInt(&ok,10);//FI_SAFETYPERSON,INTEGER,			
			else if ("FI_SafetyPersonTime" == name()) 
			{
				ShipInfo_SAFETYPERSONTIME = readElementText();//FI_SAFETYPERSONTIME,TIMESTAMP(6),
				ShipInfo_SAFETYPERSONTIME = ShipInfo_SAFETYPERSONTIME.replace("T"," ");
				ShipInfo_SAFETYPERSONTIME = ShipInfo_SAFETYPERSONTIME.left(ShipInfo_SAFETYPERSONTIME.indexOf("."));
			}
			else if ("FI_ApproveTask" == name()) ShipInfo_APPROVETASK = readElementText();//FI_APPROVETASK			
			else if ("FI_IsQuery" == name()) ShipInfo_ISQUERY = readElementText();//FI_ISQUERY			
			else if ("FI_ShipGrade" == name()) ShipInfo_SHIPGRADE = readElementText();//FI_SHIPGRADE			
			else if ("FI_BlackShip" == name()) ShipInfo_BLACKSHIP = readElementText();//FI_BLACKSHIP			
			else if ("FI_SafeMember" == name()) ShipInfo_SAFEMEMBER = readElementText();//FI_SAFEMEMBER			
			else if ("FI_SafeMemberPhone" == name()) ShipInfo_SAFEMEMBERPHONE = readElementText();//FI_SAFEMEMBERPHONE			
			else if ("FI_shipGroup" == name()) ShipInfo_SHIPGROUP = readElementText();//FI_SHIPGROUP			
			else if ("FI_MoorShip" == name()) ShipInfo_MOORSHIP = readElementText();//FI_MOORSHIP			
			else if ("FI_MoorExplain" == name()) ShipInfos_MOOREXPLAIN = readElementText();//FI_MOOREXPLAIN			
			else if ("FI_SailorCompetent" == name()) ShipInfo_SAILORCOMPETENT = readElementText();//FI_SAILORCOMPETENT
			else if ("FI_SatelliticPhone" == name()) ShipInfo_SATELLITICPHONE = readElementText();//FI_SATELLITICPHONE
#if 0
			for (int loop=0;loop<sizeof(ShipInfo_Field)/sizeof(ShipInfo_Field[0]);loop++)
			{
				if (ShipInfo_Field[loop] == name())
				{
					qDebug()<<"read_ShipInfo_Table "<<ShipInfo_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getShipInfo Table...";
				//Insert Data
				

				QString sql = QString("INSERT INTO TA_FISHERINFO (ID,FI_COUNTYID,FI_TOWNID,FI_VILLAGEID,FI_FISHERNAME,FI_FISHERHOMELAND,FI_FISHERTYPE,FI_FISHERSTUFF,\
										FI_TASKTYPE,FI_TASKMODE,FI_TASKTRAIT,FI_BUILDPLACE,FI_BUILDERNAME,FI_BUILDTIME,FI_FISHERLENGTH,FI_FISHERWIDTH,FI_FISHERDEPTH,\
										FI_TOTALTON,FI_MINETON,FI_MAINPOWER,FI_RADIO,FI_RADIOLICENSEID,FI_AIRDOOR,FI_OWNERNAME,FI_OWNERADDR,FI_OWNERMOBILE,FI_OWNERPHONE,\
										FI_TESTNUM,FI_TESTUSEDTIME,FI_LOGONNUM,FI_LOGONUSEDTIME,FI_GAINALLOW,FI_GAINALLOWUSEDTIME,FI_SAFETYCOMPANY,FI_SAFETYTIME,FI_IMAGE,FI_ISDIS,FI_RADIOUSEDTIME,\
										FI_SAFETYMONEY,FI_RADIOISHAVE,FI_ISTHREECARD,TIME,FI_TOTALLENGTH,FI_SAILORSAFE,FI_SAFETYPERSON,FI_SAFETYPERSONTIME,FI_APPROVETASK,FI_ISQUERY,FI_SHIPGRADE,\
										FI_BLACKSHIP,FI_SAFEMEMBER,FI_SAFEMEMBERPHONE,FI_SHIPGROUP,FI_MOORSHIP,FI_MOOREXPLAIN,FI_SAILORCOMPETENT,FI_SATELLITICPHONE) VALUES ('%1','%2','%3','%4','%5','%6','%7',\
										'%8','%9','%10','%11','%12','%13',to_date('%14','yyyy-mm-dd hh24:mi:ss'),%15,%16,%17,%18,%19,%20,%21,'%22',%23,'%24','%25','%26','%27',\
										'%28',to_date('%29','yyyy-mm-dd hh24:mi:ss'),'%30',to_date('%31','yyyy-mm-dd hh24:mi:ss'),'%32',to_date('%33','yyyy-mm-dd hh24:mi:ss'),'%34',to_date('%35','yyyy-mm-dd hh24:mi:ss'),\
										'%36','%37',to_date('%38','yyyy-mm-dd hh24:mi:ss'),'%39','%40','%41',to_date('%42','yyyy-mm-dd hh24:mi:ss'),%43,'%44',%45,to_date('%46','yyyy-mm-dd hh24:mi:ss'),'%47','%48','%49','%50','%51','%52','%53','%54','%55','%56','%57')")\
										.arg(ShipInfo_ID).arg(ShipInfo_COUNTYID).arg(ShipInfo_TOWNID).arg(ShipInfo_VILLAGEID).arg(ShipInfo_FISHERNAME).arg(ShipInfo_FISHERHOMELAND)
										.arg(ShipInfo_FISHERTYPE).arg(ShipInfo_FISHERSTUFF).arg(ShipInfo_TASKTYPE).arg(ShipInfo_TASKMODE).arg(ShipInfo_TASKTRAIT).arg(ShipInfo_BUILDPLACE)
										.arg(ShipInfo_BUILDERNAME).arg(ShipInfo_BUILDTIME).arg(ShipInfo_FISHERLENGTH).arg(ShipInfo_FISHERWIDTH).arg(ShipInfo_FISHERDEPTH).arg(ShipInfo_TOTALTON)
										.arg(ShipInfo_MINETON).arg(ShipInfo_MAINPOWER).arg(ShipInfo_RADIO).arg(ShipInfo_RADIOLICENSEID).arg(ShipInfo_AIRDOOR).arg(ShipInfo_OWNERNAME).arg(ShipInfo_OWNERADDR)
										.arg(ShipInfo_OWNERMOBILE).arg(ShipInfo_OWNERPHONE).arg(ShipInfo_TESTNUM).arg(ShipInfo_TESTUSEDTIME).arg(ShipInfo_LOGONNUM).arg(ShipInfo_LOGONUSEDTIME)
										.arg(ShipInfo_GAINALLOW).arg(ShipInfo_GAINALLOWUSEDTIME).arg(ShipInfo_SAFETYCOMPANY).arg(ShipInfo_SAFETYTIME).arg(ShipInfo_IMAGE).arg(ShipInfo_ISDIS)
										.arg(ShipInfo_RADIOUSEDTIME).arg(ShipInfo_SAFETYMONEY).arg(ShipInfo_RADIOISHAVE).arg(ShipInfo_ISTHREECARD).arg(ShipInfo_TIME).arg(ShipInfo_TOTALLENGTH).arg(ShipInfo_SAILORSAFE)
										.arg(ShipInfo_SAFETYPERSON).arg(ShipInfo_SAFETYPERSONTIME).arg(ShipInfo_APPROVETASK).arg(ShipInfo_ISQUERY).arg(ShipInfo_SHIPGRADE).arg(ShipInfo_BLACKSHIP).arg(ShipInfo_SAFEMEMBER)
										.arg(ShipInfo_SAFEMEMBERPHONE).arg(ShipInfo_SHIPGROUP).arg(ShipInfo_MOORSHIP).arg(ShipInfos_MOOREXPLAIN).arg(ShipInfo_SAILORCOMPETENT).arg(ShipInfo_SATELLITICPHONE);
			
				if (!query.exec(sql)) this->PrintError(query);
				query.finish();
				//qDebug()<<query.lastQuery();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_AllMember_Table()
{
	return;
	//qDebug()<<"Start to read getAllMember Table...";  
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{  
			for (int loop=0;loop<sizeof(AllMember_Field)/sizeof(AllMember_Field[0]);loop++)
			{
				if (AllMember_Field[loop] == name())
				{
					qDebug()<<"read_AllMember_Table "<<AllMember_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				qDebug()<<"Now at the end of getAllMember Table...";  
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_Base_Table()
{
	//qDebug()<<"Start to read getBase Table...";
	QSqlQuery query;
	QString BaseID,BaseMC,BaseType;
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{
			if ("ID" == name())
			{
				BaseID = readElementText();
			}
			else if ("MC" == name())
			{
				BaseMC = readElementText();
			}
			else if ("Type" == name())
			{
				BaseType = readElementText();
			}
#if 0
			for (int loop=0;loop<sizeof(Base_Field)/sizeof(Base_Field[0]);loop++)
			{
				if (Base_Field[loop] == name())
				{
					qDebug()<<"read_Base_Table "<<Base_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getBase Table...";
				//Insert Data
				query.prepare("INSERT INTO TB_Base(ID,MC,Type) VALUES(:ID,:MC,:Type)");
				query.addBindValue(BaseID);
				query.addBindValue(BaseMC);
				query.addBindValue(BaseType);
				if (!query.exec()) this->PrintError(query);
				query.finish();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_IdentifyInfo_Table()
{
	//qDebug()<<"Start to read getIdentifyInfo Table...";
	QSqlQuery query;
	QString IdentifyInfo_ID,IdentifyInfo_MC;
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{
			if ("ID" == name())
			{
				IdentifyInfo_ID = readElementText();
			}
			else if ("MC" == name())
			{
				IdentifyInfo_MC = readElementText();
			}
#if 0
			for (int loop=0;loop<sizeof(IdentifyInfo_Field)/sizeof(IdentifyInfo_Field[0]);loop++)
			{
				if (IdentifyInfo_Field[loop] == name())
				{
					qDebug()<<"read_IdentifyInfo_Table "<<IdentifyInfo_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}

#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getIdentifyInfo Table...";
				//Insert Data
				query.prepare("INSERT INTO TB_IDENTITY_INFO(ID,MC) VALUES(:ID,:MC)");
				query.addBindValue(IdentifyInfo_ID);
				query.addBindValue(IdentifyInfo_MC);
				if(!query.exec())this->PrintError(query);
				query.finish();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_ShipIdAndNameInfo_Table()
{
	//qDebug()<<"Start to read getAllMember getShipIdAndNameInfo Table...";  
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{  
			for (int loop=0;loop<sizeof(ShipIdAndNameInfo_Field)/sizeof(ShipIdAndNameInfo_Field[0]);loop++)
			{
				if (ShipIdAndNameInfo_Field[loop] == name())
				{
					qDebug()<<"read_ShipIdAndNameInfo_Table "<<ShipIdAndNameInfo_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				qDebug()<<"Now at the end of getShipIdAndNameInfo Table...";  
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_Task_Table()
{
	//qDebug()<<"Start to read getTask Table...";
	QSqlQuery query;
	QString Task_ID,Task_Type,Task_Kind;
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{
			if ("ID" == name())
			{
				Task_ID = readElementText();
			}
			else if ("T_Type" == name())
			{
				Task_Type = readElementText();
			}
			else if ("T_Kind" == name())
			{
				Task_Kind = readElementText();
			}
#if 0
			for (int loop=0;loop<sizeof(Task_Field)/sizeof(Task_Field[0]);loop++)
			{
				if (Task_Field[loop] == name())
				{
					qDebug()<<"read_Task_Table "<<Task_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getTask Table...";
				//Insert Data
				query.prepare("INSERT INTO TB_TASK(ID,T_Type,T_Kind) VALUES(:ID,:T_Type,:T_Kind)");
				query.addBindValue(Task_ID);
				query.addBindValue(Task_Type);
				query.addBindValue(Task_Kind);
				if(!query.exec())this->PrintError(query);
				query.finish();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CXml_Reader::read_TaskType_Table()
{
	//qDebug()<<"Start to read getTaskType Table...";
	QSqlQuery query;
	QString TaskType_ID,TaskType_Type,TaskType_Name;
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{  
			if ("ID" == name())
			{
				TaskType_ID = readElementText();
			}
			else if ("TD_FisherType" == name())
			{
				TaskType_Type = readElementText();
			}
			else if ("TD_TaskTypeName" == name())
			{
				TaskType_Name = readElementText();
			}
#if 0
			for (int loop=0;loop<sizeof(TaskType_Field)/sizeof(TaskType_Field[0]);loop++)
			{
				if (TaskType_Field[loop] == name())
				{
					qDebug()<<"read_TakeType_Table "<<TaskType_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getTaskType Table...";
				//Insert Data
				QString sql = QString("INSERT INTO TB_TASKTYPE(ID,TD_FISHERTYPE,TD_TASKTYPENAME) VALUES('%1','%2','%3')").arg(TaskType_ID).arg(TaskType_Type).arg(TaskType_Name);
				if (query.exec(sql)) this->PrintError(query);
				//qDebug()<<query.lastQuery();
				query.finish();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/* getTown                                                               
/************************************************************************/
void CXml_Reader::read_Town_Table()
{
	//qDebug()<<"Start to read getTown Table...";
	QSqlQuery query;
	QString Town_ID,Town_MC,Town_CountyID;
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{
			if ("ID" == name())
			{
				Town_ID = readElementText();
			}
			else if ("MC" == name())
			{
				Town_MC = readElementText();
			}
			else if ("CountyID" == name())
			{
				Town_CountyID = readElementText();
			}
#if 0
			for (int loop=0;loop<sizeof(Town_Field)/sizeof(Town_Field[0]);loop++)
			{
				if (Town_Field[loop] == name())
				{
					qDebug()<<"read_Town_Table "<<Town_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getTown Table...";
				//Insert Data
				query.prepare("INSERT INTO TB_TOWN(ID,MC,COUNTYID) VALUES(:ID,:MC,:COUNTYID)");
				query.addBindValue(Town_ID);
				query.addBindValue(Town_MC);
				query.addBindValue(Town_CountyID);
				//query.exec();
				if(!query.exec())this->PrintError(query);
				query.finish();
				break;  
			}  
		}  
	}  
}
/************************************************************************/
/* getVillage                                                            
/************************************************************************/
void CXml_Reader::read_Village_Table()
{
	//qDebug()<<"Start to read getVillage Table...";
	QSqlQuery query;
	QString Village_ID,Village_MC,Village_CountyID,Village_TownID;
	while(!atEnd())  
	{  
		readNext();  
		if(isStartElement())  
		{
			if ("ID" == name())
			{
				Village_ID = readElementText();
			}
			else if ("MC" == name())
			{
				Village_MC = readElementText();
			}
			else if ("CountyID" == name())
			{
				Village_CountyID = readElementText();
			}
			else if ("TownID" == name())
			{
				Village_TownID = readElementText();
			}
#if 0
			for (int loop=0;loop<sizeof(Village_Field)/sizeof(Village_Field[0]);loop++)
			{
				if (Village_Field[loop] == name())
				{
					qDebug()<<"read_Village_Table "<<Village_Field[loop]<<" is: "<< readElementText();
					break;
				}
			}
#endif
		}  
		if(isEndElement())  
		{  
			if(name() == "Table")  
			{  
				//qDebug()<<"Now at the end of getVillage Table...";
				//Insert Data
				query.prepare("INSERT INTO TB_VILLAGE(ID,MC,COUNTYID,TOWNID) VALUES(:ID,:MC,:COUNTYID,:TOWNID)");
				query.addBindValue(Village_ID);
				query.addBindValue(Village_MC);
				query.addBindValue(Village_CountyID);
				query.addBindValue(Village_TownID);
				//query.exec();
				if(!query.exec())this->PrintError(query);
				query.finish();
				break;  
			}  
		}  
	}  
}

void CXml_Reader::read_exception()
{  
    qDebug()<<"Start to read exception...";  
    while(!atEnd())  
    {  
        readNext();  
        if(isStartElement())  
        {  
            if(name() == "subexception")  
            {  
                read_subexception();  
            }  
        }  
        if(isEndElement())  
        {  
            if(name() == "exception")  
            {  
            qDebug()<<"Now at the end of exception...";  
            break;  
            }  
        }  
    }  
}  
void CXml_Reader::read_subexception()
{  
    qDebug()<<"Start to read subexception...";  
    while(!atEnd())  
    {  
        readNext();  
        if(isStartElement())  
        {  
            if(name() == "id")  
            {  
                //read_id();  
            }
        }  
        if(isEndElement())  
        {  
            if(name() == "subexception")  
            {  
            qDebug()<<"Now at the end of subexception...";  
            break;  
            }  
        }  
    }  
}  
 
void CXml_Reader::read_event()
{  
    qDebug()<<"Start to read event...";  
    while(!atEnd())  
    {  
        readNext();  
        if(isStartElement())  
        {  

            if(name() == "eventdesc")  
            {  
                read_eventdesc();  
            }  

        }  
        if(isEndElement())  
        {  
            if(name() == "event")  
            {  
            qDebug()<<"Now at the end of event..";  
            break;  
            }  
        }  
    }  
}  

void CXml_Reader::read_eventdesc()
{  
    qDebug()<<"Start to read eventdesc...";  
    while(!atEnd())  
    {  
        readNext();  
        if(isStartElement())  
         {  
            if(name() == "eventname")  
            {  
                //read_eventname();  
            }
         }  
        if(isEndElement())  
        {  
            if(name() == "eventdesc")  
            {  
                qDebug()<<"Now at the end of eventdesc...";  
                break;  
            }  
        }  
    }  
}

void CXml_Reader::PrintError(QSqlQuery query)
{
	QSqlError sqlError;
	sqlError = query.lastError();
	if (sqlError.isValid())
	{
		switch(sqlError.type())
		{
		case QSqlError::NoError:
			qDebug()<<sqlError.text();
			break;
		case QSqlError::ConnectionError:
			qDebug()<<sqlError.text();
			break;
		case QSqlError::StatementError:
			qDebug()<<sqlError.text();
			break;
		case QSqlError::TransactionError:
			qDebug()<<sqlError.text();
			break;
		default:
			qDebug()<<sqlError.text();
			break;
		}
	}
}


#if 0
query.prepare("INSERT INTO TA_FISHERINFO (ID, FI_COUNTYID, FI_TOWNID, FI_VILLAGEID, FI_FISHERNAME, \
			  FI_FISHERHOMELAND, FI_FISHERTYPE, FI_FISHERSTUFF, FI_TASKTYPE, FI_TASKMODE, FI_TASKTRAIT, \
			  FI_BUILDPLACE, FI_BUILDERNAME, FI_BUILDTIME, FI_FISHERLENGTH, FI_FISHERWIDTH, FI_FISHERDEPTH, \
			  FI_TOTALTON, FI_MINETON, FI_MAINPOWER, FI_RADIO, FI_RADIOLICENSEID, FI_AIRDOOR, FI_OWNERNAME, \
			  FI_OWNERADDR, FI_OWNERMOBILE, FI_OWNERPHONE, FI_TESTNUM, FI_TESTUSEDTIME, FI_LOGONNUM, FI_LOGONUSEDTIME, \
			  FI_GAINALLOW, FI_GAINALLOWUSEDTIME, FI_SAFETYCOMPANY, FI_SAFETYTIME, FI_USEDID, FI_IMAGE, FI_NUM, FI_VOICECARD, \
			  FI_ISDIS, FI_FORMERLY, CAPTIONNAME, SAILORNUM, SHIP_ID, VOICENUM, FI_RADIOUSEDTIME, FI_SAFETYMONEY, FI_RADIOISHAVE, \
			  FI_ISTHREECARD, TIME, FI_TOTALLENGTH, FI_SAILORSAFE, FI_SAFETYPERSON, FI_SAFETYPERSONTIME, FI_APPROVETASK, FI_ISQUERY, \
			  FI_SHIPGRADE, FI_BLACKSHIP, FI_SAFEMEMBER, FI_SAFEMEMBERPHONE, FI_SHIPGROUP, FI_MOORSHIP, FI_MOOREXPLAIN, FI_SAILORCOMPETENT, FI_SATELLITICPHONE) \
			  VALUES (:ID, :FI_COUNTYID, :FI_TOWNID, :FI_VILLAGEID, :FI_FISHERNAME, \
			  :FI_FISHERHOMELAND, :FI_FISHERTYPE, :FI_FISHERSTUFF, :FI_TASKTYPE, :FI_TASKMODE, :FI_TASKTRAIT, \
			  :FI_BUILDPLACE, :FI_BUILDERNAME, :FI_BUILDTIME, :FI_FISHERLENGTH, :FI_FISHERWIDTH, :FI_FISHERDEPTH, \
			  :FI_TOTALTON, :FI_MINETON, :FI_MAINPOWER, :FI_RADIO, :FI_RADIOLICENSEID, :FI_AIRDOOR, :FI_OWNERNAME, \
			  :FI_OWNERADDR, :FI_OWNERMOBILE, :FI_OWNERPHONE, :FI_TESTNUM, :FI_TESTUSEDTIME, :FI_LOGONNUM, :FI_LOGONUSEDTIME, \
			  :FI_GAINALLOW, :FI_GAINALLOWUSEDTIME, :FI_SAFETYCOMPANY, :FI_SAFETYTIME, :FI_USEDID, :FI_IMAGE, :FI_NUM, :FI_VOICECARD, \
			  :FI_ISDIS, :FI_FORMERLY, :CAPTIONNAME, :SAILORNUM, :SHIP_ID, :VOICENUM, :FI_RADIOUSEDTIME, :FI_SAFETYMONEY, :FI_RADIOISHAVE, \
			  :FI_ISTHREECARD, :TIME, :FI_TOTALLENGTH, :FI_SAILORSAFE, :FI_SAFETYPERSON, :FI_SAFETYPERSONTIME, :FI_APPROVETASK, :FI_ISQUERY, \
			  :FI_SHIPGRADE, :FI_BLACKSHIP, :FI_SAFEMEMBER, :FI_SAFEMEMBERPHONE, :FI_SHIPGROUP, :FI_MOORSHIP, :FI_MOOREXPLAIN, :FI_SAILORCOMPETENT, :FI_SATELLITICPHONE);");
query.prepare("INSERT INTO TA_FISHERINFO (ID, FI_COUNTYID, FI_TOWNID, FI_VILLAGEID, FI_FISHERNAME, \
			  FI_FISHERHOMELAND, FI_FISHERTYPE, FI_FISHERSTUFF, FI_TASKTYPE, FI_TASKMODE, FI_TASKTRAIT, \
			  FI_BUILDPLACE, FI_BUILDERNAME, FI_BUILDTIME, FI_FISHERLENGTH, FI_FISHERWIDTH, FI_FISHERDEPTH, \
			  FI_TOTALTON, FI_MINETON, FI_MAINPOWER, FI_RADIO, FI_RADIOLICENSEID, FI_AIRDOOR, FI_OWNERNAME, \
			  FI_OWNERADDR, FI_OWNERMOBILE, FI_OWNERPHONE, FI_TESTNUM, FI_TESTUSEDTIME, FI_LOGONNUM, FI_LOGONUSEDTIME, \
			  FI_GAINALLOW, FI_GAINALLOWUSEDTIME, FI_SAFETYCOMPANY, FI_SAFETYTIME, FI_IMAGE, \
			  FI_ISDIS, FI_RADIOUSEDTIME, FI_SAFETYMONEY, FI_RADIOISHAVE, \
			  FI_ISTHREECARD, TIME, FI_TOTALLENGTH, FI_SAILORSAFE, FI_SAFETYPERSON, FI_SAFETYPERSONTIME, FI_APPROVETASK, FI_ISQUERY, \
			  FI_SHIPGRADE, FI_BLACKSHIP, FI_SAFEMEMBER, FI_SAFEMEMBERPHONE, FI_SHIPGROUP, FI_MOORSHIP, FI_MOOREXPLAIN, FI_SAILORCOMPETENT, FI_SATELLITICPHONE) \
			  VALUES (:ID, :FI_COUNTYID, :FI_TOWNID, :FI_VILLAGEID, :FI_FISHERNAME, \
			  :FI_FISHERHOMELAND, :FI_FISHERTYPE, :FI_FISHERSTUFF, :FI_TASKTYPE, :FI_TASKMODE, :FI_TASKTRAIT, \
			  :FI_BUILDPLACE, :FI_BUILDERNAME, to_timestamp(:FI_BUILDTIME,'yyyy-MM-ddTHH24:MI:ss.ff'), :FI_FISHERLENGTH, :FI_FISHERWIDTH, :FI_FISHERDEPTH, \
			  :FI_TOTALTON, :FI_MINETON, :FI_MAINPOWER, :FI_RADIO, :FI_RADIOLICENSEID, :FI_AIRDOOR, :FI_OWNERNAME, \
			  :FI_OWNERADDR, :FI_OWNERMOBILE, :FI_OWNERPHONE, :FI_TESTNUM, to_timestamp(:FI_TESTUSEDTIME,'yyyy-MM-ddTHH24:MI:ss.ff'), :FI_LOGONNUM, to_timestamp(:FI_LOGONUSEDTIME,'yyyy-MM-ddTHH24:MI:ss.ff'), \
			  :FI_GAINALLOW, to_timestamp(:FI_GAINALLOWUSEDTIME,'yyyy-MM-ddTHH24:MI:ss.ff'), :FI_SAFETYCOMPANY, to_timestamp(:FI_SAFETYTIME,'yyyy-MM-ddTHH24:MI:ss.ff'), :FI_IMAGE, \
			  :FI_ISDIS, to_timestamp(:FI_RADIOUSEDTIME,'yyyy-MM-ddTHH24:MI:ss.ff'), :FI_SAFETYMONEY, :FI_RADIOISHAVE, \
			  :FI_ISTHREECARD, to_timestamp(:TIME,'yyyy-MM-ddTHH24:MI:ss.ff'), :FI_TOTALLENGTH, :FI_SAILORSAFE, :FI_SAFETYPERSON, to_timestamp(:FI_SAFETYPERSONTIME,'yyyy-MM-ddTHH24:MI:ss.ff'), :FI_APPROVETASK, :FI_ISQUERY, \
			  :FI_SHIPGRADE, :FI_BLACKSHIP, :FI_SAFEMEMBER, :FI_SAFEMEMBERPHONE, :FI_SHIPGROUP, :FI_MOORSHIP, :FI_MOOREXPLAIN, :FI_SAILORCOMPETENT, :FI_SATELLITICPHONE);");
query.addBindValue(ShipInfo_ID);//ID
query.addBindValue(ShipInfo_COUNTYID);//FI_COUNTYID
query.addBindValue(ShipInfo_TOWNID);//FI_TOWNID
query.addBindValue(ShipInfo_VILLAGEID);//FI_VILLAGEID
query.addBindValue(ShipInfo_FISHERNAME);//FI_FISHERNAME
query.addBindValue(ShipInfo_FISHERHOMELAND);//FI_FISHERHOMELAND
query.addBindValue(ShipInfo_FISHERTYPE);//FI_FISHERTYPE
query.addBindValue(ShipInfo_FISHERSTUFF);//FI_FISHERSTUFF
query.addBindValue(ShipInfo_TASKTYPE);//FI_TASKTYPE
query.addBindValue(ShipInfo_TASKMODE);//FI_TASKMODE
query.addBindValue(ShipInfo_TASKTRAIT);//FI_TASKTRAIT
query.addBindValue(ShipInfo_BUILDPLACE);//FI_BUILDPLACE
query.addBindValue(ShipInfo_BUILDERNAME);//FI_BUILDERNAME
query.addBindValue(ShipInfo_BUILDTIME);//FI_BUILDTIME,(TIMESTAMP(6))
query.addBindValue(ShipInfo_FISHERLENGTH);//FI_FISHERLENGTH,NUMBER(10,2),
query.addBindValue(ShipInfo_FISHERWIDTH);//FI_FISHERWIDTH,NUMBER(10,2),
query.addBindValue(ShipInfo_FISHERDEPTH);//FI_FISHERDEPTH,NUMBER(10,2),
query.addBindValue(ShipInfo_TOTALTON);//FI_TOTALTON,NUMBER(10,2),
query.addBindValue(ShipInfo_MINETON);//FI_MINETON,NUMBER(10,2),
query.addBindValue(ShipInfo_MAINPOWER);//FI_MAINPOWER,NUMBER(10,2),
query.addBindValue(ShipInfo_RADIO);//FI_RADIO,INTEGER default 0,
query.addBindValue(ShipInfo_RADIOLICENSEID);//FI_RADIOLICENSEID
query.addBindValue(ShipInfo_AIRDOOR);//FI_AIRDOOR,INTEGER,
query.addBindValue(ShipInfo_OWNERNAME);//FI_OWNERNAME
query.addBindValue(ShipInfo_OWNERADDR);//FI_OWNERADDR
query.addBindValue(ShipInfo_OWNERMOBILE);//FI_OWNERMOBILE
query.addBindValue(ShipInfo_OWNERPHONE);//FI_OWNERPHONE
query.addBindValue(ShipInfo_TESTNUM);//FI_TESTNUM
query.addBindValue(ShipInfo_TESTUSEDTIME);//FI_TESTUSEDTIME,TIMESTAMP(6),
query.addBindValue(ShipInfo_LOGONNUM);//FI_LOGONNUM
query.addBindValue(ShipInfo_LOGONUSEDTIME);//FI_LOGONUSEDTIME,TIMESTAMP(6),
query.addBindValue(ShipInfo_GAINALLOW);//FI_GAINALLOW
query.addBindValue(ShipInfo_GAINALLOWUSEDTIME);//FI_GAINALLOWUSEDTIME,TIMESTAMP(6),
query.addBindValue(ShipInfo_SAFETYCOMPANY);//FI_SAFETYCOMPANY
query.addBindValue(ShipInfo_SAFETYTIME);//FI_SAFETYTIME,TIMESTAMP(6),
//query.addBindValue(CountyID);//FI_USEDID(无)
query.addBindValue(ShipInfo_IMAGE);//FI_IMAGE
//query.addBindValue(CountyID);//FI_NUM(无)
//query.addBindValue(CountyMC);//FI_VOICECARD(无)
query.addBindValue(ShipInfo_ISDIS);//FI_ISDIS,CHAR(1) default 0
//query.addBindValue(CountyMC);//FI_FORMERLY(无)
//query.addBindValue(CountyID);//CAPTIONNAME(无)
//query.addBindValue(CountyMC);//SAILORNUM,NUMBER(3),(无)
//query.addBindValue(CountyID);//SHIP_ID,NUMBER(19),(无)
//query.addBindValue(CountyMC);//VOICENUM(无)
query.addBindValue(ShipInfo_RADIOUSEDTIME);//FI_RADIOUSEDTIME,TIMESTAMP(6),
query.addBindValue(ShipInfo_SAFETYMONEY);//FI_SAFETYMONEY,NUMBER(10,2),
query.addBindValue(ShipInfo_RADIOISHAVE);//FI_RADIOISHAVE,CHAR(1) default 1,
query.addBindValue(ShipInfo_ISTHREECARD);//FI_ISTHREECARD,CHAR(1) default 1,
query.addBindValue(ShipInfo_TIME);//TIME,TIMESTAMP(6),
query.addBindValue(ShipInfo_TOTALLENGTH);//FI_TOTALLENGTH,NUMBER(10,2),
query.addBindValue(ShipInfo_SAILORSAFE);//FI_SAILORSAFE,
query.addBindValue(ShipInfo_SAFETYPERSON);//FI_SAFETYPERSON,INTEGER,
query.addBindValue(ShipInfo_SAFETYPERSONTIME);//FI_SAFETYPERSONTIME,TIMESTAMP(6),
query.addBindValue(ShipInfo_APPROVETASK);//FI_APPROVETASK
query.addBindValue(ShipInfo_ISQUERY);//FI_ISQUERY
query.addBindValue(ShipInfo_SHIPGRADE);//FI_SHIPGRADE
query.addBindValue(ShipInfo_BLACKSHIP);//FI_BLACKSHIP
query.addBindValue(ShipInfo_SAFEMEMBER);//FI_SAFEMEMBER
query.addBindValue(ShipInfo_SAFEMEMBERPHONE);//FI_SAFEMEMBERPHONE
query.addBindValue(ShipInfo_SHIPGROUP);//FI_SHIPGROUP
query.addBindValue(ShipInfo_MOORSHIP);//FI_MOORSHIP
query.addBindValue(ShipInfos_MOOREXPLAIN);//FI_MOOREXPLAIN
query.addBindValue(ShipInfo_SAILORCOMPETENT);//FI_SAILORCOMPETENT
query.addBindValue(ShipInfo_SATELLITICPHONE);//FI_SATELLITICPHONE
#endif
