#pragma once
#include<iostream>
#include<stdlib.h>
#include<assert.h>

using namespace std;

class String
{
public:
    String(const char *str = "");
    String(const String& s);
    String& operator=(const String& s);
    ~String();
    int* GetpCount();
    char *c_str();
    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;
    void CopyOnWrite();
private:
    char *_str;
};
