#ifndef GLB_TIMER
#define GLB_TIMER

#include <time.h>
#include <QtCore/QTime>
#include <QtCore/QString>
#include <QtCore/QElapsedTimer>
#include <QtCore/QDateTime>
#include <QtCore/QtDebug>

/*!
 * \brief The Timer class　计时器类
 * \author mofi
 * \date 20170608
 * \desc 支持设置基准时间开始计时、支持暂停继续、支持重新启动、支持设置不同的时间速率
 */
class Timer
{
public:
    Timer(quint64 base=0, quint8 speed=1):m_speed(speed),m_elapsedTime(0),m_paused(0)
    {
        (base > 0 ? restart(base) : restart());
//        qDebug() << "clockType:" << m_timer.clockType() << m_timer.isMonotonic();
    }

    // 设置暂停/继续状态
    void setPaused(quint8 paused)
    {
        if(m_paused != paused)
        {
            updateElapsedTime();
            m_paused = paused;
        }
    }

    // 设置计时倍率
    void setSpeed(quint8 speed)
    {
        if(speed > 0 && speed < 100)
        {
            updateElapsedTime();
            m_speed = speed;
        }
    }

    quint64 restart()
    {
		quint64 base = time(0)*1000 + QTime::currentTime().msec();
		return restart(base);
    }

    quint64 restart(quint64 base)
    {
        m_paused = 0;
        m_elapsedTime = 0;
        m_startTime = base;
        m_timer.start();
        return m_startTime;
    }

    // 获取计时器起始时间
    quint64 startTime() const
    {
        return m_startTime;
    }

    // 获取计时器流逝的时间
    quint64 elapsedTime() const
    {
        return m_elapsedTime;
    }

    // 获取计时器当前时间
    quint64 getTime()
    {
        quint64 et = 0;
        if(!m_paused)
            et = timerElapsed();
        return m_startTime + m_elapsedTime + et;
    }

    // 判断是否处于暂停状态
    bool isPaused() const
    {
        return m_paused;
    }

    // 获取当前速度
    quint8 speed() const
    {
        return m_speed;
    }

protected:
    inline void updateElapsedTime()
    {
        if(!m_paused)
            m_elapsedTime += timerElapsed();
        m_timer.restart();
    }

    inline quint64 timerElapsed() const{
        return (m_timer.elapsed() * m_speed);
    }

private:
    quint64 m_startTime, m_elapsedTime;
    QElapsedTimer m_timer;
    quint8 m_speed, m_paused;
};


inline quint64 GetCrntTimeMSec(){
    static Timer timer;
    return timer.getTime();
}

inline quint32 GetCrntTimeSec() {
    return GetCrntTimeMSec()/1000;
}

#define DateTimeFormat "yyyyMMdd hh:mm:ss"
inline QString TimetToString(quint64 timet)
{
    QDateTime dt = QDateTime::fromTime_t(timet);
    return dt.toString(DateTimeFormat);
}

inline quint64 StringToTimet(const QString & strdt)
{
    QDateTime dt = QDateTime::fromString(strdt, DateTimeFormat);
    return dt.toTime_t();
}

#include <QtCore/QSemaphore>
inline void TimeWait(quint32 msec)
{
    QSemaphore sem(0);
    sem.tryAcquire(1, msec);
}


#endif // GLB_TIMER

