#pragma once
#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class String
{
public:
    String(const char *str = "");
    String(const String &s);

    void Swap(String &s);
    String& operator=(const String &s);
    //String& operator=(String s);               //与上面未构成重载

    ~String();

    void Expand(size_t n);
    void PushBack(char ch);
    void PushBack(const char *str);

    void PopBack();

    void Insert(size_t pos, char ch);
    void Insert(size_t pos, const char* str);

    void Erase(size_t pos, size_t n = 1);

    size_t Find(char ch);
    size_t Find(const char* str);


    String operator+(char ch);
    String& operator+=(char ch);
    String operator+(const char *str);
    String& operator+=(const char *str);

    bool operator==(const String &s);
    bool operator!=(const String &s);
    bool operator>(const String &s);
    bool operator>=(const String &s);
    bool operator<(const String &s);
    bool operator<=(const String &s);

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    void Display(const char *msg);
private:
    char *_str;
    size_t _size;
    size_t _capacity;
};