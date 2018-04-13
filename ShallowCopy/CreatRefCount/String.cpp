#define _CRT_SECURE_NO_WARNINGS
#include"String.h"

String::String(const char *str)
    :_str(new char[strlen(str) + 1]),
    _pCount(new size_t(1))
{
    strcpy(_str, str);
}

String::String(const String &s)
{
    _str = s._str;
    _pCount = s._pCount;
    ++(*_pCount);
}

//String::String(const String &s)
//    :_str(s._str),
//    _pCount(s._pCount)
//{
//    ++(*_pCount);
//}
String& String::operator=(const String &s)
{
    if (_str != s._str)
    {
        if (--(*_pCount) == 0)
        {
            delete[]_str;
            delete _pCount;
        }
        _str = s._str;
        _pCount = s._pCount;
        ++(*_pCount);
    }
    return *this;
}

String::~String()
{
    if (--(*_pCount) == 0)
    {
        delete[]_str;
        delete _pCount;
    }
}

const char* String::c_str()
{
    return _str;
}

void String::CopyOnWrite()
{
    if (*_pCount > 1)                        //若只有一个对象指向某空间，则不需要重新开辟空间
    {
        char *newspace = new char[strlen(_str) + 1];
        strcpy(newspace, _str);
        --(*_pCount);
        _str = newspace;
        _pCount = new size_t(1);
    }
}

char& String::operator[](size_t pos)
{
    CopyOnWrite();

    return _str[pos];
}