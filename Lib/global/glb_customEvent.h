
#ifndef _CUSTEM_EVENT_20100711_DEFINED_
#define _CUSTEM_EVENT_20100711_DEFINED_

#include <QtCore/QVariant>
#include <QtCore/QEvent>

class CustomEvent : public QEvent
{
public:
    CustomEvent (int myType, const QVariant& v1 = QVariant(), const QVariant& v2 = QVariant())
        : QEvent((Type)myType), _param1(v1), _param2(v2)
    {}

    QVariant	_param1, _param2;
};

#endif
