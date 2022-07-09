//
//  scaner.hpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#ifndef scaner_hpp
#define scaner_hpp

#include <stdio.h>
#include"utils.hpp"

int charornot(char ch);
int numberornot(char ch);
int jiefuornot(char ch);
int konggeornot(char ch);
int changshucharuhanshu(string a);
void shuzichuli(char* p);
void jiefuchuli(char *p);//界符处理函数
int biaoshifucharuhanshu(string a);
int guanjianzichuli(char *p); //关键字处理函数
void changshubiaogoujian();//初始化时将所有的string赋值成“#”
int changshucharuhanshu(string a);//插入完成以后可以返回插入的位置
void biaoshifubiaogoujian();//初始化时将所有的string赋值成“#”
int biaoshifucharuhanshu(string a);//能够返回标示符的位置
void lexer();//生成token序列函数，其实就是使用自动机的原理
void outputtoken();//输出token序列
void outputchangshubiao();//输出常数表
void outputtoken();//输出token序列
void outputchangshubiao();//输出常数表
void outputbiaoshifubiao();//输出标识符表
void outkeywords();//输出关键字表
void outputjiefuchart();//输出界符表
static int index_0=0;
extern char initial_code[1000];
static int tag=0;
static int tag1=0;
extern string biaoshifubiao[100];//记录标示符
extern string changshubiao[100];//记录常数

extern Token token[1000];//TOKEN序列数组，用来存放生成的token

static char keyword[20][10]={"program","var","integer","real","char","begin","end","if","then","else","while","do","ifend","return"};//关键字表
static char boundary[20]={',',':',';','=','*','/','+','-','.','(',')','>','<','@','[',']','{','}'};//界符表

#endif /* scaner_hpp */
