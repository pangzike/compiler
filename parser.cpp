//
//  parser.cpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#include "parser.hpp"
#include "semantic.hpp"
Stack s;
Stack s3;
string gen_tab[50][40] = {""};
string changshubiao[100] = {""};
int jilu;
string tp;
string bo;
int PROGRAM()
{
    int back=0;
    if(!((token[ip].content[0]=='k')&&(token[ip].code==0)))/*不是program*/
    {
        back++;
        return 0;
    }
    else/*是program*/
    {
        QUATFIRST();//生成第一个四元式
        ip++;//program正确，移向下一个
    }//识别program关键字

    if(!(token[ip].content[0]=='i'))/*不是标识符*/
    {
        back++;
        return 0;
    }
    else/*是标识符*/
    {
        func0();
        ip++;//标示符正确，移向下一个
    }//识别标示符

    if((SUB_PROGRAM())==0)
    {
        back++;
        return 0;
    }//识别SUB_PROGRAM是否正确

    if((token[ip].content[0]=='p')&&(token[ip].code==9))//p9为点
    {
        QUATLAST();//生成最后一个四元式
    }
    else
    {
        back++;
        return 0;
    }

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
int SUB_PROGRAM()
{

     int back=0;
     if(!(VARIABLE()))/*不正确*/
     {
         back++;
         return 0;
     }//识别VARIABLE是否正确

    while(((token[ip].content[0]=='k')&&(token[ip].code==1)))//如果当前单词是var
    {

        if(!(ANOUNCE_FUNCTION()))//识别函数定义不正确
        {
            cout<<"函数识别错误"<<endl;
            back++;
            return 0;
        }else {
        //正确
        if(((token[ip].content[0]=='p')&&(token[ip].code==3)))//p3是分号
        ip++;
        else
        {
         back++;
         return 0;
         }
        }
    }

     if(!COM_SENTENCE())/*不正确*/
     {
         back++;
         return 0;
     }

     if(back>0)//如果能到达这个区，那么应该返回的就是1
     {
         return 0;
     }
     else
     {
     return 1;
     }
}

int VARIABLE()
{
    int back=0;
    if(!(token[ip].content[0]=='k')&&(token[ip].code==1))/*不是var*/
    {
        back++;
        return 0;
    }
    else/*是var*/
    {
        func1();
        ip++;//没有缺var关键字
    }//是否写了var

    if((ID_SEQUENCE())==0)
    {
        back++;
        return 0;
    }

    if(!(token[ip].content[0]=='p')&&(token[ip].code==2))/*不是：*/
    {
        back++;
        return 0;
    }
    else/*是：*/
    {
        func7();
        ip++;//没有缺省:号
    }

    if(TYPE()==0)/*不是type*/
    {
        back++;
        return 0;
    }
    else/*是type*/
    {
        func6();
    }

    if((token[ip].content[0]=='p')&&(token[ip].code==3))/*是;*/
    {
        ip++;
    }//看缺不缺分号
    else/*不是;*/
    {
        back++;
        return 0;
    }

    while(!(((token[ip].content[0]=='k')&&(token[ip].code==5))||((token[ip].content[0]=='k')&&(token[ip].code==1))))//k5是begin,k1是var
    {
        if(!(ID_SEQUENCE()))
        {
            back++;
            return 0;
        }

        if((token[ip].content[0]=='p')&&(token[ip].code==2))//p2是冒号
        {
            func7();
            ip++;
        }
        else
        {
            back++;
            ip++;
            return 0;
        }

        if(!(TYPE()))
        {
            back++;
            return 0;
        }
        else
        {
            func6();
        }

        if((token[ip].content[0]=='p')&&(token[ip].code==3))//p3是分号
        {
            ip++;
        }
        else
        {
            back++;
            return 0;
        }
    }

    if(back>0)
    {
    return 0;
    }
    else
    {
    return 1;
    }
}

int ID_SEQUENCE()//在没有关键字的时候这个函数会出现错误
{
    int back=0;
    if(token[ip].content[0]=='i')
        {
            SEARCH1(biaoshifubiao[token[ip].code]);
            func2();
            ip++;//正确识别第一个标示符
        }
    else
    {
        back++;
        return 0;
    }
    int returnNum=ARRAY();
    if(returnNum==0)
       {
          back++;
           return 0;
       }
    if(returnNum==2){
        //TODO

        func8(biaoshifubiao[token[ip-4].code],str2int(changshubiao[token[ip-2].code]));

    }

    while(((token[ip].content[0]=='p')&&(token[ip].code==1)))//p1是逗号
    {
        ip++;
        if(token[ip].content[0]=='i')
        {
            SEARCH1(biaoshifubiao[token[ip].code]);
            func2();
            ip++;
        }
        returnNum=ARRAY();
       if(returnNum==0)
       {
          back++;
           return 0;
       }
    if(returnNum==2){
        //TODO
        func8(biaoshifubiao[token[ip-4].code],str2int(changshubiao[token[ip-2].code]));
    }
    }

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int ARRAY()
{
    int back=0;
    if((token[ip].content[0]=='p')&&(token[ip].code==15))
    {
        ip++;
    }
    else
    {
        return 1;
    }
    if(token[ip].content[0]=='c')
    {
        ip++;
    }
    else
    {
        back++;
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==16))
    {
        ip++;
    }
    else
    {
        back++;
        return 0;
    }

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 2;
    }
}

int TYPE()
{
    if((token[ip].content[0]=='k')&&((token[ip].code==2)||(token[ip].code==3)||(token[ip].code==4)))
    {
        if(token[ip].code==2)//k2为integer
        {
            func3();
            ip++;
            return 1;
        }
        if(token[ip].code==3)//k3为real
        {
            func4();
            ip++;
            return 2;

        }
        if(token[ip].code==4)//k4为char
        {
            func5();
            ip++;
            return 3;
        }

    }
    else
    {
        return 0;
    }
    return 0;
}

int COM_SENTENCE()
{
    int back=0;
    if((token[ip].content[0]=='k')&&(token[ip].code==5))/*是begin*/
    {
        QUATBEGIN();
        ip++;
    }
    else
    {
        back++;
        return 0;
    }

    if(!((SEN_SEQUENCE()==1)||(CONDITION()==1)||(CIRCLE()==1)))
    {
        ip--;
        if(!(FUNCTION()==1))
        {
             back++;
            return 0;
        }
    }
        while(((token[ip].content[0]=='p')&&(token[ip].code==3)))
    {
         ip++;
            if(!((SEN_SEQUENCE()==1)||(CONDITION()==1)||(CIRCLE()==1)))
            {
                ip--;
                if(!(FUNCTION()==1))
                {
                    back++;
                    return 0;
                }
            }
    }


    if(!((token[ip].content[0]=='k')&&(token[ip].code==6)))//k6为end
    {
        back++;
        return 0;
    }
    else
    {
       // QUATLAST();
        ip++;
    }


    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int SEN_SEQUENCE()
{
    int back=0;
    if(EVA_SENTENCE()==0)
    {

        back++;
        return 0;
    }

    while(((token[ip].content[0]=='p')&&(token[ip].code==3)))//p3是分号
    {
         ip++;
         if(EVA_SENTENCE()==0)
    {
        back++;
        return 0;
    }

    }

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int EVA_SENTENCE()
{
    int back=0;
    int temp;
    string length="";
    int type=0;
    if(!(token[ip].content[0]=='i'))
    {
        back++;
        return 0;
    }
    else
    {
        SEARCH2(biaoshifubiao[token[ip].code]);
        temp=searchfhb(biaoshifubiao[token[ip].code]);
        if(gen_tab[temp][1]=="i")
        {
            FUNC1();
        }
        if(gen_tab[temp][1]=="r")
        {
            FUNC2();
        }
        if(gen_tab[temp][1]=="c")
        {
            FUNC3();
        }
        tp=biaoshifubiao[token[ip].code];
        ip++;
    }
    int returnNum=ARRAY();
      if(returnNum==0)
        {
           back++;
            return 0;
        }
        if(returnNum==2){
             length=changshubiao[token[ip-2].code];
             type=1;
        }

    if(!((token[ip].content[0]=='p')&&(token[ip].code==4)))//p4为等于号
    {
        back++;//p4为等于号
        return 0;
    }
    else
    {
        ip++;
    }

    if(EXPRESSION()==0)
    {
        back++;
        return 0;
    }

    QUATFUZHI(length,type);

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int EXPRESSION()
{
    int back=0;
    if(TERM()==0)
    {
        back++;
        return 0;
    }

    while(((token[ip].content[0]=='p')&&(token[ip].code==7))||((token[ip].content[0]=='p')&&(token[ip].code==8)))//p7为加号
    {
            ip++;
        if(TERM()==0)
        {
            back++;
            return 0;
        }
        if(((token[ip].content[0]=='p')&&(token[ip].code==7)))
        QUATJIA();
        else
        QUATJIAN();
        jilu++;
    }
    FUNC5();
    FUNC6();
    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int TERM()
{
    int back=0;
    if(FACTOR()==0)
    {
        back++;
        return 0;
    }//否则FACTOR（）执行一遍，再判断是否递归执行
    while(((token[ip].content[0]=='p')&&(token[ip].code==5))||((token[ip].content[0]=='p')&&(token[ip].code==6)))//p5为乘号
    {
        ip++;
        if(FACTOR()==0)
        {
            back++;
            return 0;
        }
        if(((token[ip].content[0]=='p')&&(token[ip].code==5)))
        QUATCHENGE();
        else
        QUATCHU();
        jilu++;
    }

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int FACTOR()
{
    string str;
    int back=0;
    if((token[ip].content[0]=='i')||(token[ip].content[0]=='c'))/*是标识符或常量*/
    {
        if(token[ip].content[0]=='i')
        {
            str=biaoshifubiao[token[ip].code];
            ip++;
            int returnNum=ARRAY();
            if(returnNum==1||returnNum==2)
            {
                if(returnNum==2){
                   string length=changshubiao[token[ip-2].code];
                   str+="["+length+"]";
                }
            s.Push(str);
            return 1;
            }else
             s.Push(str);
        }

        if(token[ip].content[0]=='c')
        {
            s.Push(changshubiao[token[ip].code]);
            ip++;
            return 1;
        }



    }

    if((token[ip].content[0]=='p')&&(token[ip].code==10))/*是左括号*/
    {
    ip++;
    }
    else
    {
        back++;
        return 0;
    }

    if(EXPRESSION()==0)
    {
        back++;
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==11))/*是右括号*/
    {
        ip++;
    }
    else
    {
        back++;
        return 0;
    }
    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
//声明语句、赋值语句及算术表达式语法分析结束

//条件语句和循环语句语法分析的开始
int CONDITION()
{
    int back=0;
    if(!((token[ip].content[0]=='k')&&(token[ip].code==7)))/*不是if*/
    {
        back++;
        return 0;
    }
     else
    {
        ip++;
    }
    if(BOOL()==0)
    {
        back++;
        return 0;
    }
     if(!((token[ip].content[0]=='k')&&(token[ip].code==8)))//k8为then
    {
        back++;
        return 0;
    }
    else
    {
        QUATTHEN();
        jilu++;//很重要，不遗漏
        ip++;
    }
    if(SEN_SEQUENCE()==0)
    {
        back++;
        return 0;
    }

    if(((token[ip].content[0]=='k')&&(token[ip].code==9)))/*是else*/
    {
        QUATELSE();
         ip++;
       if(SEN_SEQUENCE()==0)
         {
           back++;
           return 0;
         }
        if((token[ip].content[0]=='k')&&(token[ip].code==12))/*是ifend*/
        {
            QUATIFEND();
            ip++;
        }
    }

    //QUATIFEND();

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int BOOL()
{
    int back=0;
    if(FACTOR()==0)
{
 back++;
 return 0;
}
if(!(token[ip].content[0]=='p'))
{
 back++;
 return 0;
}

if(!((token[ip].code==12)||(token[ip].code==13)||(token[ip].code==14)))
{
 back++;
 return 0;
}
else
{
    if(token[ip].code==12)//p12为小于号
    {
        bo="<";
    }
    if(token[ip].code==13)//p13为大于号
    {
        bo=">";
    }
    if(token[ip].code==14)//p14为判断是否相等
    {
        bo="@";
    }
 ip++;
}

if(FACTOR()==0)
{
 back++;
 return 0;
}
QUATBOOL();

if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int CIRCLE()
{
    int back=0;
    if(!((token[ip].content[0]=='k')&&(token[ip].code==10)))/*不是while*/
    {
        back++;
        return 0;
    }
    else
    {
    QUATWHILE();
     ip++;
    }
    if(BOOL()==0)
    {
         back++;
         return 0;
    }
    if(!((token[ip].content[0]=='k')&&(token[ip].code==11)))/*不是do*/
    {
        back++;
        return 0;
    }
    else
    {
        QUATDO();
        jilu++;//很重要，不遗漏
         ip++;
    }
    if(COM_SENTENCE()==0)
    {
       back++;
      return 0;
    }

    QUATWHILEEND();

    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }


}
//条件语句和循环语句语法分析结束

//子程序相关函数
int ANOUNCE_FUNCTION()
{
    string str_id,str_type;
    int returnNum;
    Function fun;//用于保存子程序信息
    int back=0;
    if((token[ip].content[0]=='k')&&(token[ip].code==1))/*是var*/
    {
        ip++;
    }
    else
    {
        back++;
        return 0;
    }
    if(token[ip].content[0]=='i')/*正确识别一个标示符*/
        {
            str_id=biaoshifubiao[token[ip].code];
            SEARCH1(biaoshifubiao[token[ip].code]);
            fun.name=biaoshifubiao[token[ip].code];
            fun.fn=0;
            for(int i=0;i<10;i++)
            {
            fun.params[i]="#";
            fun.types[i]="#";
            fun.lens[i]=0;
            }
            ip++;
        }
    else
    {
        back++;
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==10))/*是(*/
    {
        ip++;
    }
     else
    {
        back++;
        return 0;
    }
    if(token[ip].content[0]=='i')/*正确识别一个标示符*/
    {
        int k=fun.fn;
        fun.params[k]=biaoshifubiao[token[ip].code];
        fun.fn++;
        ip++;
    }
    else
    {
        back++;
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==2))/*是：*/
    {
        ip++;
    }
    else
    {
        back++;
        return 0;
    }

    returnNum=TYPE();
    int k=fun.fn-1;
    if(returnNum==1)/*是type*/
    {
        fun.types[k]="i";
        fun.lens[k]=4;

    }else if(returnNum==2)
    {
        fun.types[k]="r";
        fun.lens[k]=8;

    }else if(returnNum==3)
    {
       fun.types[k]="c";
        fun.lens[k]=1;
    }
    else/*不是type*/
    {
        back++;
        return 0;
    }

     while(((token[ip].content[0]=='p')&&(token[ip].code==1)))//当是，时
    {
         ip++;
         if(token[ip].content[0]=='i')/*正确识别一个标示符*/
        {
            int k=fun.fn;
            fun.params[k]=biaoshifubiao[token[ip].code];
            fun.fn++;
            ip++;
        }
        else
        {
        back++;
        return 0;
        }
        if((token[ip].content[0]=='p')&&(token[ip].code==2))/*是：*/
        {
            ip++;
        }
       else/*是：*/
       {
          back++;
          return 0;
       }
        returnNum=TYPE();
        int k=fun.fn-1;
        if(returnNum==1)/*是type*/
        {
            fun.types[k]="i";
            fun.lens[k]=4;

        }else if(returnNum==2)
        {
            fun.types[k]="r";
            fun.lens[k]=8;

        }else if(returnNum==3)
        {
            fun.types[k]="c";
            fun.lens[k]=1;
        }
       else
       {
        back++;
        return 0;
       }
    }/*while结束*/

    if((token[ip].content[0]=='p')&&(token[ip].code==11))/*是)*/
    {
        ip++;
    }
     else
    {
        back++;
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==2))/*是：*/
        {
            ip++;
        }
       else/*不是：*/
       {
          back++;
          return 0;
       }

        returnNum=TYPE();
        if(returnNum==1)/*是type*/
        {
            str_type="interger";
            fun.type="i";
            fun.len=4;

        }else if(returnNum==2)
        {
            str_type="real";
            fun.type="r";
            fun.len=8;

        }else if(returnNum==3)
        {
            str_type="char";
            fun.type="c";
            fun.len=1;
        }
       else
       {
        back++;
        return 0;
       }
    QUATHANSHUSHENGMING(str_id,str_type);
    if((token[ip].content[0]=='p')&&(token[ip].code==17))/*是{,code为17*/
    {
        ip++;
    }
    else
       {
        back++;
        return 0;
       }
       if(FUN_SENTENCE()==1)/*是*/
       {

       }
       else
       {

        back++;
        return 0;
       }
       if((token[ip].content[0]=='p')&&(token[ip].code==18))/*是}，code为18*/
    {
        ip++;
    }
    else
       {
        back++;
        return 0;
       }
    func10(fun);
    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int FUN_SENTENCE()
{
    int back=0;
    if((token[ip].content[0]=='k')&&(token[ip].code==5))/*是begin*/
    {
        QUATBEGIN();
        ip++;
    }
    else
    {
        back++;
        return 0;
    }

    if(!((SEN_SEQUENCE()==1)||(CONDITION()==1)||(CIRCLE()==1)))
    {

            back++;
            return 0;
    }
    while(((token[ip].content[0]=='p')&&(token[ip].code==3)))
    {
         ip++;
            if(!((SEN_SEQUENCE()==1)||(CONDITION()==1)||(CIRCLE()==1)))
            {

                back++;
            return 0;
            }
    }
    if(RETURN()==1)
    {
     QUATRETURN();
    }
    else
    {

        back++;
        return 0;
    }
    if(!((token[ip].content[0]=='k')&&(token[ip].code==6)))//k6为end
    {

        back++;
        return 0;
    }
    else
    {
           QUATLAST();
         ip++;

    }
    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int RETURN()
{
    int back=0;
    if((token[ip].content[0]=='k')&&(token[ip].code==13))/*是return*/
    {
        ip++;
    }
     else
    {
        back++;
        return 0;
    }
    if(FACTOR()==1)
    {

    }
    else
    {

        back++;
        return 0;
    }
    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int FUNCTION()
{
    string str_id;
    int back=0;
    if(token[ip].content[0]=='i')/*正确识别第一个标示符*/
        {
            str_id=biaoshifubiao[token[ip].code];
            ip++;
            //cout<<"识别函数名"<<endl;
        }
    else
    {
        back++;
        return 0;
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==10))/*是(*/
    {
        ip++;
    }
     else
    {
        back++;
        return 0;
    }
    if(token[ip].content[0]=='i')/*正确识别第一个标示符*/
        {
            cout<<"识别第一个参数"<<endl;
            ip++;
        }
    else
    {
        back++;
        return 0;
    }
    while(((token[ip].content[0]=='p')&&(token[ip].code==1)))/*p1是逗号*/
    {
        ip++;
        if(token[ip].content[0]=='i')
        {
            ip++;
        }
        else
        {
            back++;
            return 0;
        }
    }
    if((token[ip].content[0]=='p')&&(token[ip].code==11))/*是)*/
    {
        ip++;
    }
     else
    {
        back++;
        return 0;
    }
    QUATDIAOYONG(str_id);
    if(back>0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
