#define _CRT_SECURE_NO_WARNINGS
#include"String.h"

String::String(const char *str )
    :_str(new char[strlen(str) + 1]),
    _size(strlen(str)),                  //其中_size为有效字符个数，不包含'\0' 
    _capacity(strlen(str))
{
    strcpy(_str, str);
}

//String::String(const String &s)
//    :_str(new char[strlen(s._str) + 1]),
//    _size(strlen(s._str)),
//    _capacity(strlen(s._str))
//{
//    strcpy(_str, s._str);
//}

String::String(const String &s)
{
    _str = new char[strlen(s._str) + 1];
    strcpy(_str, s._str);
    _size = s._size;
    _capacity = strlen(s._str);            //切记：不要将s._capacity赋值给_capacity;(_capacity标识着实际开辟的空间大小，s._capacity有可能与其大小不一样)
}

void String::Swap(String &s)
{
    swap(_str, s._str);
    swap(_size, s._size);
    swap(_capacity, s._capacity);
}
//1.传统写法
String& String::operator=(const String &s)
{
    if (this != &s)                     //判断该对象是否给自己赋值
    {
        delete[]_str;
        _str = new char[strlen(s._str) + 1];
        strcpy(_str, s._str);
        _size = s._size;
        _capacity = s._capacity;
    }
    return *this;
}

//2.现代写法(利用临时变量出作用域时，会自己释放空间。)
/* String& String::operator=(const String &s)
{
    if (this == &s)
    {
        return *this;
    }
    String tmp(s);
    Swap(tmp);

    return *this;
}*/

//3.简洁写法(若不存在自己给自己赋值)
/*String& String::operator=(String s)
{
    Swap(s);
    return *this;
}*/

String::~String()
{
    delete[]_str;
}
void String::Display(const char *msg)
{
    cout << msg << endl;
    cout << _str << endl<<endl;
}

void  String::Expand(size_t n)
{
    char *tmp = new char[n+1];                 //切记：重新开辟空间时，n表示的是有效字符的个数，不包含'\0'.故需开辟n+1个空间大小。否则会出现heap corruption detected错误
    strcpy(tmp, _str);
    delete[]_str;
    _str = tmp;
    _capacity = n;
}

void String::PushBack(char ch)
{
    /*if (_size >= _capacity)
    {
        Expand(_capacity*2+1);
    }
    _str[++_size-1] = ch;
    _str[_size] = '\0';*/
    Insert(_size, ch);
}

void String::PushBack(const char *str)
{
    /*int length = strlen(str);
    if (_size + length > _capacity)
    {
        Expand(_size + length);
    }
    strcpy(_str + _size, str);
    _size += length;*/
    Insert(_size, str);
}

void String::PopBack()
{
    if (_size > 0)
    {
        _str[--_size] = '\0';
    }
}

void String::Insert(size_t pos, char ch)
{
    assert(pos <= _size);
    if (_size >= _capacity)
    {
        Expand(_capacity * 2 + 1);
    }

    //注意：1.若将i定义为size_t类型；则当pos=0时，循环变为死循环；
    //      2.size_t类型变量与int类型变量进行比较，则发生隐式转换(int类型提升为size_t);
    for (int i = _size; i >=(int)pos; --i)            
    {
        _str[i + 1] = _str[i];
    }
    _str[pos] = ch;
    ++_size;
}

void String::Insert(size_t pos, const char* str)
{
    //1.参数判断
    assert(pos <= _size);
    assert(str);
    int length = strlen(str);
    //2.插入，需进行容量判断
    if (_size + length > _capacity)
    {
        Expand(_size + length);
    }
    //3.正式插入。

    //  A.pos为'\0'
    if (pos == _size)
    {
        strcpy(_str + _size, str);
        _size += length;
    }

    //B.pos为非'\0'的有效位置
    else
    {
        //<1>挪位置
        for (int i = _size; i >= (int)pos; --i)
        {
            _str[i + length] = _str[i];
        }
        //<2>插入
        size_t insert = pos;
        while (*str)
        {
            _str[insert] = *str;
            insert++;
            str++;
        }
        _size += length;
    }
    
}

void String::Erase(size_t pos, size_t n)
{
    assert(pos < _size);
    if (_size!=0)
    { 
        //1.pos之后的n个字符超过了_str的大小
        if ((pos + n) >= _size)
        {
            _str[pos] = '\0';
            _size = pos;
        }
        //2.删除pos位置之后的n个字符
        else
        {
            for (int i =pos; i <= (int)_size; ++i)
            {
                _str[i] = _str[i + n];
            }
            _size -= n;
        }
    }
}

size_t String::Find(char ch)
{
    const char *p = _str;
    for(size_t i=0;i<_size;i++)
    {
        if (p[i] == ch)
        {
            return i;
        }
    }
    return -1;
}

size_t String::Find(const char* str)
{
    assert(str);
    const char *src = _str;

    for (size_t i = 0; i<=(strlen(_str)-strlen(str)); ++i)
    {
        size_t j = 0;
        for (j=0; str[j] != '\0'; ++j)
        {
            if (str[j] != src[i + j])
            {
                break;
            }
        }
        if (str[j] == '\0')
        {
            return i;
        }
    }
    
    return -1;
}

String String::operator+(char ch)
{
    String tmp(*this);
    tmp.PushBack(ch);
    return tmp;  
}

String& String::operator+=(char ch)
{
    this->PushBack(ch);
    return *this;
}
String String::operator+(const char *str)
{
    String tmp(*this);
    tmp.PushBack(str);
    return tmp;
}
String& String::operator+=(const char *str)
{
    this->PushBack(str);
    return *this;
}

//bool String::operator==(const String &s)
//{
//    if (strcmp(_str, s._str))
//    {
//        return true;
//    }
//    return false;
//}


bool String::operator==(const String &s)
{
    const char *p1 = _str;
    const char *p2 = s._str;

    while (*p1&&*p2)
    {
        if (*p1 != *p2)
        {
            return false;
        }
        else
        {
            p1++;
            p2++;
        }
    }
    
    if (*p1 == '\0'&&*p2 == '\0')
    {
        return true;
    }
    return false;
}

bool String::operator!=(const String &s)
{
    return !(*this==s);
}

bool String::operator>(const String &s)
{
    const char *p1 = _str;
    const char *p2 = s._str;
    while (*p1&&*p2)
    {
        if (*p1 > *p2)
        {
            return true;
        }
        else if (*p1 < *p2)
        {
            return false;
        }
        else
        {
            p1++;
            p2++;
        }
    }
    if (*p1 != '\0'&&*p2 == '\0')
    {
        return true;
    }
    return false;
}

bool String::operator>=(const String &s)
{
    return (*this > s || *this == s);
}

bool String::operator<(const String &s)
{
    return !(*this >= s);
}

bool String::operator<=(const String &s)
{
    return !(*this > s);
}

char& String::operator[](size_t pos)                     //可读可写
{
    assert(pos < _size);
    return _str[pos];
}

//const成员函数的对象在函数内不会被改变。
const char& String::operator[](size_t pos) const         //只读
{
    assert(pos <= _size);
    return _str[pos];
}