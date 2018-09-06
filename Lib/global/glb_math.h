#ifndef _GLOBAL_MATH_H_20160815_
#define _GLOBAL_MATH_H_20160815_

#include "glb_mathDefine.h"
#include <math.h>
#include <time.h>
#include <QtCore/QPointF>

// 计算纬度渐长率
inline double calLatGrowRatio(double lat)
{
    // 单位转化:度-->弧度
    lat = lat * Deg2Rad;
    double e = 0.081813334;
    double temp1 = tan(M_PI/4+lat/2);
    double temp = e*sin(lat);//增加了一个临时变量，避免了重复计算
    double temp2 = (1-temp)/(1+temp);
    temp2 = pow(temp2, e/2);
    return 7915.704468*log10(temp1*temp2);
}

// 计算两点的相对弧度
inline double calRelativRadian(double lon1, double lat1, double lon2, double lat2)
{
    lon1 = lon1 * Deg2Rad;
    lat1 = lat1 * Deg2Rad;
    lon2 = lon2 * Deg2Rad;
    lat2 = lat2 * Deg2Rad;
    return acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon2-lon1));
}

// 计算两点间的相对方位和距离，返回值单位：azi度，rng海里
inline void calRelativeAziRng(double lon1, double lat1, double lon2, double lat2, \
                              double &azi, double &rng)
{
//    if(abs(lat1-lat2) < 1.0e-5)
    if(EqualZero(lat1-lat2))
    {	// 采用中分纬度算法
        if(/*abs(lon1-lon2) < 1.0e-5*/EqualZero(lon1-lon2)) azi = 0;
        else if(lon1 <= lon2) azi = 90;
        else azi = 270;
        rng = /*abs*/Abs((lon2 - lon1) * cos((lat1+lat2)/2.0*Deg2Rad) * 60);
    }
    else
    {	// 采用墨卡托算法
        const double MP1 = calLatGrowRatio(lat1);
        const double MP2 = calLatGrowRatio(lat2);
        const double tanc = (lon2 - lon1) * 60.0 / (MP2-MP1);
        azi = atan(/*abs*/Abs(tanc))/Deg2Rad;
        const bool xflag = lon2>lon1, yflag = lat2>lat1;
        if(xflag && yflag)
            azi = azi;
        else if(xflag && !yflag)
            azi = 180 - azi;
        else if(!xflag && !yflag)
            azi = 180 + azi;
        else
            azi = 360 - azi;
        rng = /*abs*/Abs((lat2-lat1)/cos(azi*Deg2Rad)*60.0);
    }
}

inline void calRelativeAziRng(const QPointF & ld1, const QPointF & ld2, double &azi, double &rng)
{
    calRelativeAziRng(ld1.x(), ld1.y(), ld2.x(), ld2.y(), azi, rng);
}

// 计算两点的相对距离
inline double calRelativeRange(double lon1, double lat1, double lon2, double lat2)
{
    double azi, rng;
    calRelativeAziRng(lon1, lat1, lon2, lat2, azi, rng);
    return rng;
}

// 计算两点的相对方位(0-360度)
inline double calRelativeAzi(double lon1, double lat1, double lon2, double lat2)
{
    double azi, rng;
    calRelativeAziRng(lon1, lat1, lon2, lat2, azi, rng);
    return azi;
}

// speed:节，course:度，time:毫秒
inline void calArrivePos_ms(double startLon, double startLat, double speed, double course,
                  unsigned int time, double& arriveLon, double& arriveLat)
{
    const double dr = speed*time/1000.0;
    const bool flag = (abs(course-90) < 1.0 || abs(course-270) < 1.0);
    course = course * Deg2Rad;
    //double cosc = cos(course);
    arriveLat = startLat + dr*cos(course)/216000.0;//将原来的分母：3600.0改为216000.0
    if(flag)
    {	// 使用中分纬度算法
        const double dlon = dr*sin(course)/cos((startLat+arriveLat)*Deg2Rad/2)/216000.0;
        arriveLon = startLon + dlon;
    }
    else
    {	// 使用墨卡托算法
        const double MP1 = calLatGrowRatio(startLat);
        const double MP2 = calLatGrowRatio(arriveLat);
        const double dlon = (MP2-MP1)*tan(course)/60.0;
        arriveLon = startLon + dlon;
    }

    if(arriveLon < -180) arriveLon += 360;
    else if(arriveLon > 180) arriveLon -= 360;
}

// 已知起始点的经纬度，航速、航向和航行时间，计算到达点的经纬度
// speed:节，course:度，time:秒
inline void calArrivePos(double startLon, double startLat, double speed, double course,
                  unsigned int time, double& arriveLon, double& arriveLat)
{
    calArrivePos_ms(startLon, startLat, speed, course, time*1000, arriveLon, arriveLat);
}

// 生成随机数
inline int getRand(int min, int max)
{
    qsrand(qrand()+time(0));
    int v = qrand();
    return min + v % (max-min+1);
}

#include <QtCore/QBitArray>
struct LongBit
{
    LongBit(const int size = 8):_bits(size),_size(size),_begin(0)
    {
    }

    bool getBit(int index) const
    {
        return _bits.at(_pos(index));
    }

    void setBit(int index, bool val)
    {
        if(val)
            setBit(index);
        else
            cleanBit(index);
    }

    void setBit(int index)
    {
        _bits.setBit(_pos(index));
    }

    void cleanBit(int index)
    {
        _bits.clearBit(_pos(index));
    }

    LongBit & operator << (int bits)
    {
        for(int i=1; i<=bits; i++)
            _bits.clearBit(_pos(-i));
        _begin = _pos(-bits);
        return *this;
    }

    LongBit & operator >> (int bits)
    {
        for(int i=1; i<=bits; i++)
            _bits.clearBit(_pos(i));
        _begin = _pos(bits);
        return *this;
    }

    inline int _pos(int index) const{
        return (_size+_begin+index)%_size;
    }

    QBitArray _bits;
    quint16   _size;
    quint16   _begin;
};

#endif  // end of file
