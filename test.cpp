#include"string.h"

/********************************************************************************
                           以下为测试代码
********************************************************************************/
#define TEST_HEADER printf("=============================%s=============================\n",__FUNCTION__)

void TestConstruct()
{
    TEST_HEADER;
    String str1("abcdef");
    str1.Display("构造一个对象str1");
    String str2(str1);
    str2.Display("用str1拷贝构造另一对象str2");

    String str3;
    str3.Display("构造一个对象str3");
    str3 = str1;
    str3.Display("使用重载了的赋值运算符，将str1对象值赋值给str3");

    str3 = str3;
    str3.Display("尝试将str1对象值赋值给str3");

}

void TestPush()
{
    TEST_HEADER;
    String str("hello");
    str.Display("构造一个对象str");

    str.PushBack(' ');
    str.Display("尾部插入' '空格字符");

    str.PushBack("world!");
    str.Display("尾部插入\"world!\"字符串");

    str.PopBack();
    str.Display("删除尾部字符");
}

void TestInsert()
{
    TEST_HEADER;
    String str("hello");
    str.Display("构造一个对象str");

    str.Insert(0,' ');
    str.Display("在0号下标处插入' '空格字符");

    str.Insert(6, '!');
    str.Display("在尾部插入'！'字符");

    str.Insert(0, "haha");
    str.Display("在0号下标处插入\"haha\"字符串");

    str.Insert(11, " world");
    str.Display("在尾部插入\"world\"字符串");

    str.Insert(5, " MY ");
    str.Display("在5号下标处插入\" MY \"字符串");

    /*str.Insert(50, "haha");
    str.Display("不合法pos");*/

}

void TestErase()
{
    TEST_HEADER;
    String str("hello world!");
    str.Display("构造一个对象str");

    /*str.Erase(13, 10);
    str.Display("非法pos");*/

    str.Erase(10, 10);
    str.Display("删除d之后的字符");

    str.Erase(6, 2);
    str.Display("删除wo");

    str.Erase(0, 5);
    str.Display("删除hello");

}

void TestFind()
{
    TEST_HEADER;
    String str("hello");
    str.Display("构造一个对象str");

    cout << str[3] << endl;                             //读

    str[3] = 'x';                                       //写
    str.Display("修改下标为3的字符为x");       

    const String str1("world!");                   
    cout << str1[1] << endl;
    //str1[1] = 'x';                                    //不可被改，语法出错


    String str2("what?");
    str2.Display("构造一个对象str");

    cout << "expect result is: 0,actual result is:" << str2.Find('w') << endl;
    cout << "expect result is: 4,actual result is:" << str2.Find('?') << endl;
    cout << "expect result is: 0,actual result is:" << str2.Find("wh") << endl;
    cout << "expect result is: 2,actual result is:" << str2.Find("at?") << endl;


}

void TestOperator()
{
    TEST_HEADER;
    String str("hello");
    str.Display("构造一个对象str");
    str += '!';
    str.Display("为str字符串拼接一个！");

    String str1 = (str + '!');
    str1.Display("为str字符串拼接一个！");
    str1 = str + " world!";
    str1.Display("为str字符串拼接字符串 \" world！\"");

    String s1 = "hello";
    String s2 = s1;
    String s3 = "world";
    String s4 = "hell";
    String s5 = "hello!";
    cout <<"expect result is: 1,actual result is:"<< (s1 == s2) << endl;
    cout <<"expect result is: 0,actual result is:" << (s1 == s3) << endl;
    cout <<"expect result is: 0,actual result is:" << (s1 != s2) << endl;
    cout <<"expect result is: 1,actual result is:" << (s1 != s3) << endl;
    cout <<"expect result is: 1,actual result is:" << (s1 >= s4) << endl;
    cout <<"expect result is: 0,actual result is:" << (s1 >= s5) << endl;
    cout <<"expect result is: 1,actual result is:" << (s1 >= s2) << endl;

}


int main()
{
    TestConstruct();
    TestPush();
    TestInsert();
    TestErase();
    TestFind();
    TestOperator();

    system("pause");
    return 0;
}