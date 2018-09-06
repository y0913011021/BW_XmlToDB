#ifndef GLOBAL_VALIDATOR_H
#define GLOBAL_VALIDATOR_H

#include <QtCore/QVariant>

/*!
 * \brief The Validator class 数值验证类, 提供验证接口
 * \author : mofi
 * \date : 2013-05-10
 */
class Validator
{
public :
    virtual bool validate(const QVariant & var) const = 0;
};

/*!
 * \brief The IntValidator class 整数验证，验证整数值是否在有效范围内
 * \author : mofi
 * \date : 2013-05-10
 */
class IntValidator : public Validator
{
public :
    IntValidator(int _min, int _max): m_valMin(_min),m_valMax(_max)
    {}

    //! 设置有效整数范围
    void setRange(int _min, int _max)
    {
        m_valMin = _min, m_valMax = _max;
    }

    //! 验证输入值是否在有效范围内
    virtual bool validate(const QVariant & var) const
    {
        bool ok = false;
        const int val = var.toInt(&ok);
        return (ok && val >= m_valMin && val <= m_valMax);
    }

private:
    int m_valMin, m_valMax;
};

/*!
 * \brief The DoubleValidator class 浮点数验证，验证浮点值是否在有效范围内
 * \author : mofi
 * \date : 2013-05-10
 */
class DoubleValidator : public Validator
{
public :
    DoubleValidator(double _min, double _max): m_valMin(_min),m_valMax(_max)
    {}

    //! 设置有效浮点数范围
    void setRange(double _min, double _max)
    {
        m_valMin = _min, m_valMax = _max;
    }

    //! 验证输入值是否在有效范围内
    virtual bool validate(const QVariant & var) const
    {
        bool ok = false;
        const double val = var.toDouble(&ok);
        return (ok && BigEqual(val,m_valMin) && LessEqual(val,m_valMax));
    }

private:
    double m_valMin, m_valMax;
};

#endif // GLOBAL_VALIDATOR_H
