#ifndef _GOLBAL_DATA_FORMAT_H_
#define _GOLBAL_DATA_FORMAT_H_

#include <math.h>
#include <QtCore/QString>

/*!
 * \brief The DataFormat class
 * \author mofi
 * \date 2015-04-14
 */
namespace DataFormat
{
enum RNGINDEX{RI_KM = 0, RI_NM, RI_MI};

// 获取经度字符串,lon单位是度
inline QString longitude2String(double lon, bool enflag=true)
{
    const double fv = fabs(lon) + 1.0e-6;
    const int degree = (int)fv;
    double minute = (fv - degree) * 60.0;
    QString sLon = QString("%1°%2'").arg(degree).arg(minute, 6, 'f', 3, QLatin1Char('0'));
    if(lon>=0)
    {
        if(enflag)
            sLon += "E";
        else
            sLon = QString::fromLocal8Bit("东经") + sLon;
    }
    else
    {
        if(enflag)
            sLon += "W";
        else
            sLon = QString::fromLocal8Bit("西经") + sLon;
    }
    return sLon;
}

// 获取纬度字符串,lat单位是度
inline QString latitude2String(double lat, bool enflag=true)
{
    const double fv = fabs(lat) + 1.0e-6;
    const int degree = (int)fv;
    double minute = (fv - degree) * 60.0;
    QString sLon = QString("%1°%2'").arg(degree).arg(minute, 5, 'f', 3, QLatin1Char('0'));
    if(lat>=0)
    {
        if(enflag)
            sLon += "N";
        else
            sLon = QString::fromLocal8Bit("北纬") + sLon;
    }
    else
    {
        if(enflag)
            sLon += "S";
        else
            sLon = QString::fromLocal8Bit("南纬") + sLon;
    }
    return sLon;
}

// 获取航向字符串,单位是度
inline QString course2String(double course)
{
    return QString::number(course,'f°',1);
}

// 获取速度单位字符串
inline QString speedUnitText(RNGINDEX index, bool enflag=true)
{
    const QString uintText[] = {QString("km/h"), QString("nm/h"), QString("mi/h"),\
                        QString("公里/小时"), QString("海里/小时"), QString("英里/小时")};
    return uintText[index+(enflag?0:3)];
}

// 获取距离单位字符串
inline QString rangeUnitText(RNGINDEX index, bool enflag=true)
{
    const QString uintText[] = {QString("km"), QString("nm"), QString("mi"),\
                                QString("公里"), QString("海里"), QString("英里")};
    return uintText[index+(enflag?0:3)];
}

}   // end namespace DataFormat

// 获取经度字符串
inline QString Longitude2String(double lon, bool enflag)
{
    return DataFormat::longitude2String(lon, enflag);
}

// 获取纬度字符串
inline QString Latitude2String(double lat, bool enflag)
{
    return DataFormat::latitude2String(lat, enflag);
}


// 将数据转换成16进制字符串
inline QString Data2String(const quint8 * pdata, int length)
{
    QString text;
    for(int i=0; i<length; i++)
    {
        text += QString("%1 ").arg((int)pdata[i], 2, 16, QLatin1Char('0'));
    }
    return text;
}

inline QString Data2String(const QByteArray & data)
{
    return Data2String((quint8*)data.data(), data.size());
}

#endif // DATAFORMAT_H
