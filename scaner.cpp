//
//  scaner.cpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#include "scaner.hpp"

char initial_code[1000] = {0};
Token token[1000] = {};
string biaoshifubiao[100]={""};
//词法分析阶段开始
int charornot(char ch){ //判断当前字符是不是字母
    if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))
        return 1;
    else
        return 0;
}
int numberornot(char ch){ //判断当前字符是不是数字
    if(ch>='0'&&ch<='9')
        return 1;
    else
        return 0;
}
int jiefuornot(char ch){  //判断当前字符是不是界符
    int i;
    for(i=0;i<18;i++){
        if(ch==boundary[i])
            return (i+1);
    }
    return 0;
}
int konggeornot(char ch){  //判断当前字符是不是字母
    if(ch==' ' or ch=='\n' or ch=='\t' or ch=='\r')
        return 1;
    else
        return 0;
}

int changshucharuhanshu(string a);
void shuzichuli(char* p) //数字处理函数
{
//    int i=0;
    int j=0;
    while((*p>='0'&&*p<='9')||(*p=='.'))
    {

        token[tag].content[j++]=*p;
        p++;
        index_0++;
    }
    int temp;
    temp=changshucharuhanshu(token[tag].content);
    token[tag].content[0]='c';
    token[tag].code=temp;
    tag++;
}
void jiefuchuli(char *p){ //界符处理函数
    int j=jiefuornot(*p);
    token[tag].code=j;
    token[tag].content[0]='p';
    index_0++;
    tag++;
}

int biaoshifucharuhanshu(string a);
int guanjianzichuli(char *p){ //关键字处理函数
    int i=0;
     while(!jiefuornot(*p)&&!konggeornot(*p)&&(initial_code[index_0]!='#'))
     {
         token[tag].content[i]=*p;
         i++;
         p++;
         index_0++;
     }
     int j;
     for(j=0;j<14;j++)
     {
         if(strcmp(keyword[j],token[tag].content)==0)
         {
             token[tag].code=j;
             token[tag].content[0]='k';
             tag++;
             return 1;
         }
     }
     token[tag].code=biaoshifucharuhanshu(token[tag].content);
     token[tag].content[0]='i';
     tag++;
     return 0;
}

void changshubiaogoujian()
{
    for(int j=0;j<100;j++)
    {
        changshubiao[j]="#";
    }
}//初始化时将所有的string赋值成“#”

int changshucharuhanshu(string a)
{
    int i=0;
    if(changshubiao[0]=="#")
    {
        changshubiao[0]=a;
        return i;
    }
    while(changshubiao[i]!="#")
    {
        if((changshubiao[i]!=a))
        {
            i++;
        }
        else
        {
        return i;
        }
    }
    changshubiao[i]=a;
    return i;
}//插入完成以后可以返回插入的位置

void biaoshifubiaogoujian()
{
    for(int j=0;j<100;j++)
    {
        biaoshifubiao[j]="#";
    }
}////初始化时将所有的string赋值成“#”

int biaoshifucharuhanshu(string a)
{
    int i=0;
    if(biaoshifubiao[0]=="#")
    {
        biaoshifubiao[0]=a;
        return i;
    }
    while(biaoshifubiao[i]!="#")
    {
        if((biaoshifubiao[i]!=a))
        {
            i++;
        }
        else
        {
        return i;
        }
    }
    biaoshifubiao[i]=a;
    return i;
}//能够返回标示符的位置

void lexer()//生成token序列函数，其实就是使用自动机的原理
{
    while(initial_code[index_0]!='#')
    {

        if(numberornot(initial_code[index_0]))
        {
            shuzichuli(&initial_code[index_0]);
            tag1++;
        }
        else if(konggeornot(initial_code[index_0]))
        {
            index_0++;
        }
        else if(jiefuornot(initial_code[index_0]))
        {
            jiefuchuli(&initial_code[index_0]);
            tag1++;
        }
        else if(charornot(initial_code[index_0]))
        {
            guanjianzichuli(&initial_code[index_0]);
            tag1++;
        }
    }
    if(initial_code[index_0]=='#')
        return;
}

void outputtoken()//输出token序列
{
    int i=0;
    int j=0;
    while(token[i].content[0]!='\0')
    {
        cout<<"("<<token[i].content[0]<<","<<token[i].code<<")"<<"  ";
        i++;
        j++;
        if(j==10)
        {
            cout<<endl;
            j=0;
        }
    }
    cout<<endl;
}

void outputchangshubiao()//输出常数表
{
    cout<<endl<<"常数表如下："<<endl;
    int m=0;
    while(changshubiao[m]!="#")
    {
        cout<<changshubiao[m]<<" "<<m<<endl;
        m++;
    }
    return;
}

void outputbiaoshifubiao()//输出标识符表
{
    cout<<endl<<"标识符表如下："<<endl;
    int m=0;
    while(biaoshifubiao[m]!="#")
    {
        cout<<biaoshifubiao[m]<<" "<<m<<endl;
        m++;
    }
    return;
}

void outkeywords()//输出关键字表
{
    int i;
    int j=0;
    cout<<endl<<"关键字表是:"<<endl;
    for(i=0;i<14;i++)
    {
        while(*(keyword[i]+j)!='\0')
        {
            cout<<*(keyword[i]+j);
            j++;
        }
        cout<<" "<<i<<endl;
        j=0;
    }
}
void outputjiefuchart()//输出界符表
{
    int i;
    cout<<endl<<"界符表是："<<endl;
    for(i=0;i<18;i++)
    {
        cout<<boundary[i]<<" "<<(i+1)<<endl;
    }
}
//词法分析结束
