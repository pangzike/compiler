//
//  parser.hpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include"utils.hpp"
#include"scaner.hpp"
int PROGRAM();
int SUB_PROGRAM();
int VARIABLE();
int ID_SEQUENCE();
int ARRAY();
int TYPE();
int COM_SENTENCE();
int SEN_SEQUENCE();
int EVA_SENTENCE();
int EXPRESSION();
int TERM();
int FACTOR();
int CONDITION();
int BOOL();
int CIRCLE();

int ANOUNCE_FUNCTION();
int FUN_SENTENCE();
int RETURN();
int FUNCTION();
//声明语句、赋值语句和算术表达式语法分析的开始
int PROGRAM();
static int ip=0;
extern Stack s;
extern Stack s3;
extern string gen_tab[50][40];
static Stack s1;
static Stack s2;
static Stack s4;
static string arr_tab[10][40];
static string fun_tab[10][40];
extern int jilu;//用以记录第几个中间变量的生成
static stack<Array> s5;
static stack<Array> s6;
static stack<Params> s7;
static stack<Params> s8;
static string type;
static int len;
static int m=1;//处理到fhb第几项
static int position=-1;//数组表第几项
static int page=-1;//函数表第几项
static int offset;
extern string tp;//执行赋值语句时作为中间桥梁
extern string bo;//存取bool的比较符，要插动作
inline string int2str(int &i)
{
    string s;
    stringstream ss(s);
    ss<<i;
    return ss.str();
}

inline void FUNC1()//根据中间变量如果为整型的话就有如下性质
{
    type="i";
    len=4;
}
inline void FUNC2()//根据中间变量如果为实型的话就有如下性质
{
    type="r";
    len=8;
}
inline void FUNC3()//根据中间变量如果为字符型型的话就有如下性质
{
    type="c";
    len=1;
}
/*void FUNC4(string c)//每生成一个四元式将其中的t...压进去，注意插入函数位置
{
    s1.Push(c);
}*/
inline void FUNC5()//还原一个四元式意群的中间变量的顺序存在S4中
{
    while(!(s3.isEmpty()))
    {
        s4.Push(s3.Pop());
    }
}
inline void FUNC6()//填表算法，同上
{
        while(!(s4.isEmpty()))
    {
        gen_tab[m][0]=s4.Pop();
        gen_tab[m][1]=type;
        gen_tab[m][3]=int2str(offset);
        offset=offset+len;
        m++;
        }
}

inline int searchfhb(string a)//搜索符号表并若成功返回变量位置，用以判别中间变量的类型的
{
    int i=0;
    while(gen_tab[i][0]!="#")
    {
        if(a==gen_tab[i][0])
        {
            return i;
        }
        else
        {
            i++;
        }
    }
    return 0;
}

inline void func0()//填入符号表第一项，函数的名字
{
    gen_tab[0][0]=biaoshifubiao[token[ip].code];
    gen_tab[0][1]="/";
    gen_tab[0][2]="f";
}
inline void func1()//总体性质的执行，执行且只执行一次
{
    int i;
    for(i=1;i<50;i++)
    {
        gen_tab[i][2]="V";
    }
    offset=0;
    for(i=0;i<10;i++)
    {
        arr_tab[i][0]="0";
    }
    for(i=0;i<10;i++)
    {
        fun_tab[i][0]="0";
    }

}
inline void func2()//在一个声明变量意群模块里，依次把标识符压进栈中
{
    s1.Push(biaoshifubiao[token[ip].code]);
}
inline void func9(string up,string type,string len)
{
    position++;
    arr_tab[position][1]=up;
    arr_tab[position][2]=type;
    arr_tab[position][3]=len;
}
inline void func8(string na,int len)
{
    Array a;
    a.name=na;
    a.length=len;
    s5.push(a);
}

inline void func7()//S2用于恢复定义变量时的顺序
{
    while(!(s1.isEmpty()))
    {
        s2.Push(s1.Pop());
    }
    while(!(s5.empty()))
    {
        s6.push(s5.top());
        s5.pop();
    }

}

inline void func3()//设置整型填入标识符的性质
{
    type="i";
    len=4;
}
inline void func4()//设置实型填入标识符的性质
{
    type="r";
    len=8;
}
inline void func5()//设置字符型填入标识符的性质
{
    type="c";
    len=1;
}

inline void func6()//声明部分填表算法，按定义的顺序填表，性质对应，最后的offset更新为下一个要填的变量的地址
{
    string* aname=new string;
    int alength = 0;
    if(!(s6.empty())){
        *aname=s6.top().name;
        alength=s6.top().length;
        s6.pop();
    }
    while(!(s2.isEmpty()))
    {
        gen_tab[m][0]=s2.Pop();
        if(*aname==gen_tab[m][0])
        {
            gen_tab[m][1]="a";
            gen_tab[m][3]=int2str(offset);
            offset=offset+len*alength;
            int up=alength-1;
            func9(int2str(up),type,int2str(len));
            if(!(s6.empty()))
            {
                *aname=s6.top().name;
                alength=s6.top().length;
                s6.pop();
            }
        }
        else
        {
            gen_tab[m][1]=type;
            gen_tab[m][3]=int2str(offset);
            offset=offset+len;
        }
        m++;
    }
}

inline void func10(Function fun)//函数声明部分填表
{
     //参数表
    Params para;
    para.name=fun.name;
    para.fn=fun.fn;
    int i=0;
    while(fun.params[i]!="#")
    {

        para.csb[i]=fun.params[i];
        para.types[i]=fun.types[i];
        para.lens[i]=fun.lens[i];
        fun.off+=para.lens[i];
        i++;
    }
    s7.push(para);
    //符号表
    gen_tab[m][0]=fun.name;
    gen_tab[m][1]="p";
    gen_tab[m][2]="f";
    gen_tab[m][3]=int2str(offset);
    offset=offset+fun.off;
    m++;
    //函数表
    page++;
    fun_tab[page][1]=int2str(fun.off);
    fun_tab[page][2]=int2str(fun.fn);
    fun_tab[page][3]=fun.name;
}


inline void goujianfhb()
{
    int i=0;
    for(i=0;i<50;i++)
    {
        gen_tab[i][0]="#";
    }
    for(i=0;i<10;i++)
    {
        arr_tab[i][0]="#";
    }
    for(i=0;i<10;i++)
    {
        fun_tab[i][0]="#";
    }
}

inline void outputfhb()//输出符号表函数
{
    int i=0;
    gen_tab[0][3]=int2str(offset);
    cout<<"\n符号表如下:"<<endl;
    while(gen_tab[i][0]!="#")
    {
        cout<<gen_tab[i][0]<<"_"<<gen_tab[i][1]<<"_"<<gen_tab[i][2]<<"_"<<gen_tab[i][3]<<endl;
        i++;
    }
    if(position!=-1){
        i=0;
        cout<<"\n数组表如下:"<<endl;
        while(i<=position)
        {
           cout<<arr_tab[i][0]<<"_"<<arr_tab[i][1]<<"_"<<arr_tab[i][2]<<"_"<<arr_tab[i][3]<<endl;
           i++;
        }
    }
    if(page!=-1){
        i=0;
        cout<<"\n函数表如下:"<<endl;
        while(i<=page)
        {
           cout<<fun_tab[i][0]<<"_"<<fun_tab[i][1]<<"_"<<fun_tab[i][2]<<"_"<<fun_tab[i][3]<<endl;
           i++;
        }
    }
    while(!s7.empty())
    {
        int off=0;
        i=0;
        Params para=s7.top();
        s7.pop();
        cout<<para.name<<"函数的参数表如下:"<<endl;
        while(i<para.fn)
        {
            cout<<para.csb[i]<<"_"<<para.types[i]<<"_"<<"V"<<"_"<<off<<endl;
            off+=para.lens[i];
            i++;
        }
    }
}

inline int str2int(string s)
{
    int num;
    stringstream ss(s);
    ss>>num;
    return num;
}

#endif /* parser_hpp */
