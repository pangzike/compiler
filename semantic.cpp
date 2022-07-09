//
//  semantic.cpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#include "semantic.hpp"

string siyuanshi[100];
string siyuanshi1[100];
void QUATFIRST()//生成第一个四元式
{
    string temp="";
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(program,"+"I0"+","+"_"+","+"_"+")";
    siyuanshi1[xuhao1]=temp+"(program,"+"I0"+","+"_"+","+"_"+")";
    xuhao1++;
    xuhao++;
}
void QUATJIA()//加号生成四元式
{
    temp1=s.Pop();
    temp2=s.Pop();
    string* p=new string;
    *p="t"+int2str(jilu);
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(+,"+temp2+","+temp1+","+*p+")";
    siyuanshi1[xuhao1]="(+,"+temp2+","+temp1+","+*p+")";
    s3.Push(*p);
    s.Push(*p);
    xuhao1++;
    xuhao++;

}
void QUATJIAN()//减号生成四元式
{
    temp1=s.Pop();
    temp2=s.Pop();
    string* p=new string;
    *p="t"+int2str(jilu);
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(-,"+temp2+","+temp1+","+*p+")";
    siyuanshi1[xuhao1]="(-,"+temp2+","+temp1+","+*p+")";
    s3.Push(*p);
    s.Push(*p);
    xuhao1++;
    xuhao++;
}
void QUATCHENGE()//乘号生成四元式
{
    temp1=s.Pop();
    temp2=s.Pop();
    string* p=new string;
    *p="t"+int2str(jilu);
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(*,"+temp2+","+temp1+","+*p+")";
    siyuanshi1[xuhao1]="(*,"+temp2+","+temp1+","+*p+")";
    s3.Push(*p);
    s.Push(*p);
    xuhao1++;
    xuhao++;
}


void QUATCHU()
{
    temp1=s.Pop();
    temp2=s.Pop();
    string* p=new string;
    *p="t"+int2str(jilu);
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(/,"+temp2+","+temp1+","+*p+")";
    siyuanshi1[xuhao1]="(/,"+temp2+","+temp1+","+*p+")";
    s3.Push(*p);
    s.Push(*p);
    xuhao1++;
    xuhao++;
}
//赋值语句生成四元式所需函数
void QUATFUZHI(string len,int type)
{
    temp1=s.Pop();
    if(type){
        siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(=,"+temp1+","+"_"+","+tp+"["+len+"]"+")";
        siyuanshi1[xuhao1]="(=,"+temp1+","+"_"+","+tp+"["+len+"]"+")";

    }else
    {
        siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(=,"+temp1+","+"_"+","+tp+")";
        siyuanshi1[xuhao1]="(=,"+temp1+","+"_"+","+tp+")";
    }
    xuhao1++;
    xuhao++;
}

void QUATLAST()//生成最后一个四元式
{
    string temp="";
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(end,"+"I0"+","+"_"+","+"_"+")";
    siyuanshi1[xuhao1]=temp+"(end,"+"I0"+","+"_"+","+"_"+")";
    xuhao1++;
    xuhao++;
}
void QUATBEGIN()
{
    string temp="";
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(begin,"+"I0"+","+"_"+","+"_"+")";
    siyuanshi1[xuhao1]=temp+"(begin,"+"I0"+","+"_"+","+"_"+")";
    xuhao++;
    xuhao1++;
}
void outputsiyuanshi()//输出所有四元式函数
{
    cout<<"四元式序列为："<<endl;
    int i=0;
    while(siyuanshi[i]!="")
    {
        cout<<siyuanshi[i]<<endl;
        i++;
    }
    cout<<endl;
}

void outputsiyuanshi1()//输出所有四元式函数
{
    cout<<"四元式一序列为："<<endl;
    int i=0;
    while(siyuanshi1[i]!="")
    {
        cout<<siyuanshi1[i]<<endl;
        i++;
    }
    cout<<endl;
}


//以下为条件语句和循环语句生成四元式部分所需函数
void QUATBOOL()
{
    temp1=s.Pop();
    temp2=s.Pop();
    string* p=new string;
    *p="t"+int2str(jilu);
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+bo+","+temp2+","+temp1+","+*p+")";
    siyuanshi1[xuhao1]="("+bo+","+temp2+","+temp1+","+*p+")";
    xuhao++;
    xuhao1++;
    s.Push(*p);//将bool表达式的结果存入栈中
}
void QUATTHEN()
{
    temp1=s.Pop();
    string temp="";
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+"then"+","+temp1+","+"_"+",";//此时s.pop就是bool表达式的结果
    siyuanshi1[xuhao1]=temp+"("+"then"+","+temp1+","+"_"+",";
    if1=xuhao;
    if2=xuhao1;
    xuhao++;
    xuhao1++;
}
void QUATELSE()
{
    string temp="";
    int i=xuhao+1;
    int j=xuhao1+1;
    siyuanshi[if1]+=int2str(i)+")";
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+"else"+","+"_"+","+"_"+",";
    siyuanshi1[if2]+=int2str(j)+")";
    siyuanshi1[xuhao1]=temp+"("+"else"+","+"_"+","+"_"+",";
    if1=xuhao;
    if2=xuhao1;
    xuhao++;
    xuhao1++;
}
void QUATIFEND()
{
    string temp="";
    siyuanshi[if1]+=int2str(xuhao)+")";
    siyuanshi1[if2]+=int2str(xuhao1)+")";
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+"ifend"+","+"_"+","+"_"+","+"_"+")";
    siyuanshi1[xuhao1]=temp+"("+"ifend"+","+"_"+","+"_"+","+"_"+")";
    xuhao1++;
    xuhao++;
}
void QUATWHILE()
{
    string temp="";
    while1=xuhao;
    while3=xuhao1;
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+"while"+","+"_"+","+"_"+","+"_"+")";
    siyuanshi1[xuhao1]=temp+"("+"while"+","+"_"+","+"_"+","+"_"+")";
    xuhao1++;
    xuhao++;
}
void QUATDO()
{
    while2=xuhao;
    while4=xuhao1;
    string temp="";
    temp1=s.Pop();
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+"do"+","+temp1+","+"_"+",";//bool那个区已经将bool表达式的结果存进去了，即s.pop
    siyuanshi1[xuhao1]=temp+"("+"do"+","+temp1+","+"_"+",";
    xuhao1++;
    xuhao++;
}
void QUATWHILEEND()
{
    string temp="";
    int i=xuhao+1;
    int j=while1+1;
    int k=xuhao1+1;
    int m=while3+1;
    siyuanshi[while2]+=int2str(i)+")";
    siyuanshi1[while4]+=int2str(k)+")";
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+"whend"+","+"_"+","+"_"+","+int2str(j)+")";
    siyuanshi1[xuhao1]=temp+"("+"whend"+","+"_"+","+"_"+","+int2str(m)+")";
    xuhao1++;
    xuhao++;
}
void QUATHANSHUSHENGMING(string str1,string str2)
{
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+str1+","+"_"+","+"_"+","+str2+")";
    siyuanshi1[xuhao1]="("+str1+","+"_"+","+"_"+","+str2+")";
    xuhao1++;

}
void QUATDIAOYONG(string str)
{
     siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:("+str+","+"_"+","+"_"+"_"+")";
     xuhao++;

}
void QUATRETURN()
{
    string temp="";
    temp1=s.Pop();
    siyuanshi[xuhao]="QT["+int2str(xuhao)+"]:(return,"+"_"+","+"_"+","+temp1+")";
    siyuanshi1[xuhao1]=temp+"(return,"+"_"+","+"_"+","+temp1+")";
    xuhao1++;
    xuhao++;
}
//生成四元式区


//语义分析部分
void SEARCH1(string a)
{
    int i=0;
    while(gen_tab[i][0]!="#")
    {
        if(a==gen_tab[i][0])
        {
            chongdingyi=1;
            return;
        }
        else
        {
            i++;
        }
    }
}
void SEARCH2(string a)
{
    int i=0;
    while(gen_tab[i][0]!="#")
    {
        if(a==gen_tab[i][0])
        {
            weidingyi=0;
            return;
//            i++;
        }
        else
        {
            weidingyi=1;
            i++;
        }
    }
}
void yuyifenxi()
{
    int back=0;
    cout<<endl<<"语义分析结果如下:"<<endl;
        if(chongdingyi==1)
    {
        cout<<"重定义错误!"<<endl;
        back++;
    }
    if(weidingyi==1)
    {
        cout<<"未定义错误!"<<endl;
        back++;
    }
    if(back>0)
    {
        return;
    }
    else
    {
        cout<<"语义正确！"<<endl;
    }
}
