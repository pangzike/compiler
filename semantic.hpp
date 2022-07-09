//
//  semantic.hpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#ifndef semantic_hpp
#define semantic_hpp

#include <stdio.h>
#include"utils.hpp"
#include"parser.hpp"
void SEARCH1(string a);
void SEARCH2(string a);
void QUATFIRST();
void QUATJIA();
void QUATJIAN();
void QUATCHENGE();
void QUATCHU();
void QUATFUZHI(string len,int type);
void QUATLAST();
void QUATBEGIN();
void QUATBOOL();
void QUATTHEN();
void QUATELSE();
void QUATIFEND();
void QUATWHILE();
void QUATDO();
void QUATWHILEEND();
void QUATHANSHUSHENGMING(string str1,string str2);
void QUATDIAOYONG(string str);
void QUATRETURN();
void outputsiyuanshi();//输出所有四元式函数
void outputsiyuanshi1();//输出所有四元式函数
void yuyifenxi();
extern string siyuanshi[100];//存取四元式字符串数组
static int xuhao=0;//用以记录生成第几个四元式
static int if1;//用于if四元式回填地址时使用的
static int if2;
static int while1;//用于while四元式回填地址时使用的
static int while2;//用于while四元式回填地址时使用的
static int while3;
static int while4;
static int chongdingyi=0;//用于语义分析，重定义时使用的
static int weidingyi=1;//用于语义分析，未定义时使用的
static int xuhao1=0;
extern string siyuanshi1[100];
static string temp1;
static string temp2;
#endif /* semantic_hpp */
