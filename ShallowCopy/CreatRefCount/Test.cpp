#include"String.h"

void TestConstruction()
{
    String s1("hello!");
    String s2(s1);
    String s3("world");
    s2 = s3;
    s1 = s3;

}

void TestCopyOnWrite()
{
    String s1("hello!");
    String s2(s1);
    String s3("world");

    cout << s1[0] << endl;
    cout << s3[0] << endl;
}

int main()
{
    TestConstruction();
    TestCopyOnWrite();

    system("pause");
    return 0;
}