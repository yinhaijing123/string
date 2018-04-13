#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;

class String
{
public:
    String(const char *str = "");
    String(const String &s);
    String& operator=(const String &s);
    ~String();
    const char* c_str();
    char& operator[](size_t pos);
    void CopyOnWrite();                       //Ð´Ê±¿½±´
private:
    char *_str;
    size_t *_pCount;
};