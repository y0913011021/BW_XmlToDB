#include "glb_format.h"
#include <math.h>


/*!
 * \brief The DataFormat class
 * \author mofi
 * \date 2015-04-14
 */

// 获取经度字符串
QString DataFormat::longitude2String(double lon, bool enflag)
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

// 获取纬度字符串
QString DataFormat::latitude2String(double lat, bool enflag)
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
QString DataFormat::course2String(double course)
{
    return QString::number(course,'f°',1);
}

// 获取速度单位字符串
QString DataFormat::speedUnitText(RNGINDEX index0, bool enflag)
{
    const QString uintText[] = {QString("km/h"), QString("nm/h"), QString("mi/h"),\
                        QString("公里/小时"), QString("海里/小时"), QString("英里/小时")};
    return uintText[index0+(enflag?0:3)];
}

// 获取距离单位字符串
QString DataFormat::rangeUnitText(RNGINDEX index0, bool enflag)
{
    const QString uintText[] = {QString("km"), QString("nm"), QString("mi"),\
                                QString("公里"), QString("海里"), QString("英里")};
    return uintText[index0+(enflag?0:3)];
}

#ifndef LL2STRING
#define LL2STRING
// 获取经度字符串
QString Longitude2String(double lon, bool enflag)
{
    return DataFormat::longitude2String(lon,enflag);
}
// 获取纬度字符串
QString Latitude2String(double lat, bool enflag)
{
    return DataFormat::latitude2String(lat,enflag);
}
#endif
