#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<stack>
#include"utils.hpp"
#include"scaner.hpp"
#include"parser.hpp"
#include"semantic.hpp"
#include"codegen.hpp"

//主函数
int main(){
    changshubiaogoujian();
    biaoshifubiaogoujian();
    goujianfhb();
    //处理输入程序为处理格式
    string file = "sample.txt";
    FILE *file_in, *file_out;
    
    int y=0;
    //打开源程序
    if ((file_in = fopen(file.c_str(), "r")) == NULL)
    {
        cout << "this file cannot be opened.\n";
        exit(0);
    }
    initial_code[y] = fgetc(file_in);
    
    while (initial_code[y] != '#')
    {//将源程序读入resourceProject[]数组
        y++;
        initial_code[y] = fgetc(file_in);
    }
    initial_code[y]='#';
    fclose(file_in);
    
    //处理完毕
    cout<<endl<<"token序列为:"<<endl;
    lexer();//生成token
    outputtoken();//按序输出token
    outputchangshubiao();
    outputbiaoshifubiao();
    outkeywords();
    outputjiefuchart();
    cout<<endl<<"语法分析"<<endl;
    if(PROGRAM()==1)
    {
        cout<<"the result of syntax analysis is succeed!"<<endl<<endl;
    }
    else
    {
        cout<<"the result of syntax analysis is error!"<<endl;
        return 0;//说明：错误以后不再执行后续工作
    }
    outputsiyuanshi();//输出四元式序列
    outputfhb();
    yuyifenxi();
    outputsiyuanshi1();
    compa();
    file_out = fopen("out.txt", "w+");
    last(file_out);
    return 0;
}
