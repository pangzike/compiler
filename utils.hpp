//
//  utils.hpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#ifndef utils_hpp
#define utils_hpp

#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<stack>
#define MAX 10
using namespace std;

struct Token{
    char content[10];
    int code;
};

class Stack
{
    public:
        Stack()
        {
            Top=-1;
        }
        void Push(string b)
        {
            if(Top==99)
                return;
            Top++;
            a[Top]=b;
        }
        string Pop()
        {
            string element;
            //如果栈空，则返回0；
            if(Top==-1)
                return 0;
            element=a[Top];
            Top--;
            return element;
        }
        void Clear()
        {
            Top=-1;//直接置栈顶指针，没有清空栈
        }
        string Peek() const
        {
            //如果栈为空，则返回0；
            if(Top==-1)
                return 0;
            return a[Top];
        }
        
        bool isEmpty() const
        {
            if(Top==-1)
            return true;
            else
                return false;
        }
    private:
        string a[100];
        int Top;
};
//前期准备，数字转字符串函数
struct Array{
string name;
int length;
};
//结构体用于临时保存子程序相关信息
struct Function{
string name;
string type;
int len;
int fn=0;
int off=0;
string params[10];
string types[10];
int lens[10];
};
struct Params{
    string name;
    string csb[10];
    string types[10];
    int lens[10];
    int fn=0;
};

#endif /* utils_hpp */
