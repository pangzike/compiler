//
//  codegen.hpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#ifndef codegen_hpp
#define codegen_hpp

#include <stdio.h>
#include"utils.hpp"
#include"semantic.hpp"

int compa();
int isOperator(string ch);
void Operator_Number();
string OperatorToString(int i);
int displayOperations1(int k, FILE * out);
void last(FILE * out);
static int mm=0;
static string siyuanshi2[50];
static int j=0;//表示当前是第几个操作
static string acc="_";//寄存器标志：0表示为空，非0，被占用
static struct formula{
    string operationName;//操作码
    char opp1[MAX];//操作数
    char opp2[MAX];
    string ans;
    int temp;
}Operate[400];
#endif /* codegen_hpp */
