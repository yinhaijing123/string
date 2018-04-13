#define _CRT_SECURE_NO_WARNINGS
#include"String.h"
String::String(const char *str)
    :_str(new char[strlen(str)+5])                //较之前多开辟4个字节大小的空间，用于存储共享空间的对象的个数(即此5=4+1)
{
    _str += 4;                                    //第四个字节开始，为有效字符串的空间，前四个字节，引用计数
    strcpy(_str, str);
    *((int *)(_str - 4)) = 1;                     //以整型空间的形式访问前四个字节

}
int* String::GetpCount()
{
    return (int *)(_str - 4);
}

String::String(const String& s)
    :_str(s._str)
{
    ++(*GetpCount());
}

String& String::operator=(const String& s)
{
    if (_str != s._str)
    {
        if (--(*GetpCount()) == 0)            //若只有一个对象指向某空间，需--Count,并释放空间;若有多个对象指向某空间，只需--Count。
        {
            delete[](_str - 4);
        }
        _str = s._str;
        ++(*GetpCount());
    }
    return *this;
}

String::~String()
{
    if (--(*GetpCount()) == 0)
    {
        delete[](_str - 4);
    }
}

char* String::c_str()
{
    return _str;
}

char& String::operator[](size_t pos)                  //可读可写，即使是进行读操作,this也更改指向并且指向重新开辟的空间。
{
    assert(pos < strlen(_str));
    CopyOnWrite();
    return _str[pos];
}

const char& String::operator[](size_t pos) const      //只允许读
{
    return _str[pos];
}

void String::CopyOnWrite()
{
    if (*GetpCount() > 1)                             //仅当多个对象指向同一块空间时，写时才需重新开辟空间
    {
        char *newspace = new char[strlen(_str) + 5];
        newspace += 4;
        strcpy(newspace, _str);
        --(*GetpCount());
        _str = newspace;
        *GetpCount()=1;
    }
}