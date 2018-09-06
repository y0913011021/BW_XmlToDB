#ifndef GLOBAL_SIGLETON_H
#define GLOBAL_SIGLETON_H

#include <QtCore/QMutex>

/*! 说明， 莫红飞， 20170713
 * DECL_SINGLETON必须放到头文件中，如果放在cpp文件中则编译时会出错
 */

#define DECL_SINGLETON(classname)   \
private:                            \
classname(){};                      \
~classname(){};                     \
static   classname * m_instance;    \
static QMutex  m_mutex;             \
public:                             \
static classname * instance();      \
static void freeInstance();

#define DECL_SINGLETON2(classname,baseclassname) \
private:                            \
classname():baseclassname(){};      \
~classname(){};                     \
static   classname * m_instance;    \
static QMutex  m_mutex;             \
public:                             \
static classname * instance();      \
static void freeInstance();

#define IMPL_SINGLETON(classname)   \
classname * classname::m_instance = NULL; \
QMutex classname::m_mutex;          \
classname * classname::instance() { \
if(!m_instance)                     \
{                                   \
    QMutexLocker lock(&m_mutex);    \
    if(!m_instance)                 \
        m_instance = new classname; \
}                                   \
return m_instance;                  \
}                                   \
void classname::freeInstance() {    \
    QMutexLocker lock(&m_mutex);    \
    if(m_instance) {                \
        delete m_instance; m_instance = NULL;   \
    }   \
}

#endif // GLOBAL_SIGLETON_H
