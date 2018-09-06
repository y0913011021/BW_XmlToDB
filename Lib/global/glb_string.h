#ifndef STRING_H_MOFI_20170119
#define STRING_H_MOFI_20170119

#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    char * _text;

    // 构造函数
    String():_text(0){}
    String(int size):_text(0){
        _text = (char*)malloc(size+1);
        memset(_text, 0, size+1);
    }
    String(const char * txt, int len = -1):_text(0){
        if(_strlen(txt, len) > 0)
            append(txt, len);
    }
    String(const String & o):_text(0){
        if(o.length() > 0)
            append(o);
    }

    // 析构函数
    ~String(){
        if(_text) free(_text);
    }

    // 链接两个字符串
    String & append(const char * txt, int len = -1)
    {
        const int len1 = _strlen(txt, len);
        const int size = _strlen(_text) + len1 + 1;
        _text = (char*)realloc(_text, size);
        strncat(_text, txt, len1);
        _text[size] = 0;
        return *this;
    }
    String & append(const String & o)
    {
        append(o._text);
        return *this;
    }
    String & operator +=(const char * txt)
    {
        return append(txt);
    }
    String & operator +=(const String & o)
    {
        return append(o);
    }

    // 赋值操作
    String & operator =(const char * txt)
    {
        const int size = strlen(txt) + 1;
        _text = (char*)realloc(_text, size);
        strcat(_text, txt);
        return *this;
    }

    String & operator =(const String & o)
    {
        return *this = o._text;
    }

    // 字符串比较
    // ==
    bool operator ==(const char * txt) const{
        return strcmp(_text, txt) == 0;
    }
    bool operator ==(const String & o) const{
        return strcmp(_text, o._text) == 0;
    }
    // !=
    bool operator != (const char * txt) const{
        return strcmp(_text, txt) != 0;
    }
    bool operator !=(const String & o) const{
        return strcmp(_text, o._text) != 0;
    }
    // <
    bool operator <(const char * txt) const{
        return strcmp(_text, txt) < 0;
    }
    bool operator <(const String & o) const{
        return strcmp(_text, o._text) < 0;
    }
    // <=
    bool operator <=(const char * txt) const{
        return strcmp(_text, txt) <= 0;
    }
    bool operator <=(const String & o) const{
        return strcmp(_text, o._text) <= 0;
    }
    // >
    bool operator >(const char * txt) const{
        return strcmp(_text, txt) > 0;
    }
    bool operator >(const String & o) const{
        return strcmp(_text, o._text) > 0;
    }
    // >=
    bool operator >=(const char * txt) const{
        return strcmp(_text, txt) >= 0;
    }
    bool operator >=(const String & o) const{
        return strcmp(_text, o._text) >= 0;
    }

    // 判断是否为空
    bool empty() const
    {
        return (NULL == _text || 0 == length());
    }

    // 转换成字符串
    char * text()
    {
        return _text;
    }
    const char * text() const
    {
        return _text;
    }

    // 获取字符长度
    int length() const
    {
        return strlen(_text);
    }

    // 获取字符串长度
    int _strlen(const char * txt, int len = -1) const
    {
        if(len != -1)   return len;
        else return strlen(txt);
    }

}AsciiString;

inline const String	operator+ ( const String & s1, const String & s2 )
{
    String str(s1.length() + s2.length());
    strcat(str.text(), s1.text());
    strcat(str.text(), s2.text());
    return str;
}

inline const String	operator+ ( const String & s1, const char * s2 )
{
    String str(s1.length() + strlen(s2));
    strcat(str.text(), s1.text());
    strcat(str.text(), s2);
    return str;
}

inline const String	operator+ ( const char * s1, const String & s2 )
{
    String str(strlen(s1) + +s2.length());
    strcat(str.text(), s1);
    strcat(str.text(), s2.text());
    return str;
}

// 用于支持QHash操作
inline uint qHash(const String & str)
{
    return qHash(QString::fromAscii(str._text));
}

// 字义字符串列表
typedef QList<String> StringList;
// 定义属性表
typedef QHash<String, String> StringHash;

#endif  // {end of file}
