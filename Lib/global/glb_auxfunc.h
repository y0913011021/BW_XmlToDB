#ifndef _GLOBAL_AUX_FUNC_H_
#define _GLOBAL_AUX_FUNC_H_

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QFile>
#include <QtCore/QtDebug>

struct DataRecInfo
{
    char *  _dataPtr;
    int     _dataLen;
};

typedef QList<DataRecInfo *> DataPtrList;

/*!
 * \brief The DataRecorder class
 * \author mofi
 * \date 2016-01-20
 */
class DataRecorder
{
public:
    DataRecorder():m_flag(false){}
    virtual ~DataRecorder()
    {
        stop();
    }

    void start(const QString & fileName)
    {
        m_fileName = fileName;
        m_flag = true;
    }

    bool recordData(const char * lpData, int length)
    {
        if(!m_flag) return false;
        DataRecInfo * info = applyDataInfo(lpData, length);
        m_dataInfoList.append(info);
        return true;
    }

    void stop()
    {
        if(!m_flag) return;

        QFile file(m_fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
            qDebug() << __FUNCTION__ << "open file error." << m_fileName;

        DataPtrList::iterator it = m_dataInfoList.begin();
        DataPtrList::iterator it2 = m_dataInfoList.end();
        for(; it != it2; ++it)
        {
            DataRecInfo * info = *it;
            file.write(info->_dataPtr, info->_dataLen);
            freeDataInfo(info);
        }

        m_dataInfoList.clear();
        file.close();

        m_flag = false;
    }

protected:
    DataRecInfo * applyDataInfo(const char * lpData, int length)
    {
        DataRecInfo * info = new DataRecInfo;
        info->_dataPtr = new char[length];
        memcpy(info->_dataPtr, lpData, length);
        info->_dataLen = length;
        return info;
    }
    void freeDataInfo(DataRecInfo * info)
    {
        delete[] info->_dataPtr;
        delete info;
    }

private:
    bool m_flag;
    DataPtrList m_dataInfoList;
    QString m_fileName;
};

#include <QtCore/QVariant>
#include <QtCore/QSettings>

namespace AuxParam
{
    #define aux_param_file "../configs/aux-param.ini"

    inline const char * GetAuxFile(){
        return (aux_param_file);
    }
    inline QVariant GetAuxParam(const QString & key)
    {
        //qDebug() << __FUNCTION__ << key;
        QSettings set(GetAuxFile(), QSettings::IniFormat);
        qDebug() << __FUNCTION__ << key << set.value(key);
        return set.value(key);
    }
    inline QVariant GetAuxParam(const QString & group, const QString & key)
    {
        QSettings set(GetAuxFile(), QSettings::IniFormat);
        set.beginGroup(group);
        qDebug() << __FUNCTION__ << group << key << set.value(key);
        return set.value(key);
    }
    inline void SetAuxParam(const QString & key, const QVariant & val)
    {
        qDebug() << __FUNCTION__ << key << val;
        QSettings set(GetAuxFile(), QSettings::IniFormat);
        set.setValue(key, val);
    }
    inline void SetAuxParam(const QString & group, const QString & key, const QVariant & val)
    {
        qDebug() << __FUNCTION__ << group << key << val;
        QSettings set(GetAuxFile(), QSettings::IniFormat);
        set.beginGroup(group);
        set.setValue(key, val);
    }
}

//class TaskSpin
//{
//public:
//    static lock();
//    static unlock();
//    static delay(int n);
//private:
//    char m_locked;
//};

#endif  // end of file
