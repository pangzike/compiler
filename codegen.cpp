//
//  codegen.cpp
//  complier
//
//  Created by 杨可 on 2022/7/8.
//

#include "codegen.hpp"

int compa()
{
    int i;
    int k=0;
    for (i=0;siyuanshi1[i].length()!=0;i++){
    if ((siyuanshi1[i]=="(while,_,_,_)")||(siyuanshi1[i]=="(proc,_,_,_)")||(siyuanshi1[i]=="(func,_,_,_)")||(siyuanshi1[i]=="(ifend,_,_,_)")||(siyuanshi1[i]=="(lable,_,_,_)"))
        {
            if (siyuanshi2[k].length()==0)
            siyuanshi2[k]=siyuanshi1[i];
            else
                k++;
            siyuanshi2[k]=siyuanshi1[i];
        }
     else if((siyuanshi1[i].substr(0,6)=="(goto,")||(siyuanshi1[i].substr(0,6)=="(then,")||(siyuanshi1[i].substr(0,6)==("(else,"))||(siyuanshi1[i].substr(0,6)=="(whend"||(siyuanshi1[i].substr(0,6)=="(do,_,")||(siyuanshi1[i].substr(0,6)=="(call,")))
            {//cout<<"**********"<<endl;
                siyuanshi2[k]+=siyuanshi1[i];
                //cout<<base[k]<<endl;
                k++;
            }
     else if(siyuanshi1[i].substr(0,3)=="(=,")
            {//cout<<"**********"<<endl;
            //for (j=0;j<=(i-temp);j++,record++)
                siyuanshi2[k]+=siyuanshi1[i];
                k++;
            }
    else if(siyuanshi1[i].substr(0,7)=="(return")
                continue;
            else siyuanshi2[k]+=siyuanshi1[i];
    }
    cout<<"基本块划分为："<<endl;
    for(i=0;siyuanshi2[i].length()!=0;i++)
            cout<<"("<<(i+1)<<")"<<siyuanshi2[i]<<endl;
           // cout<<ch[19]<<endl;
       return 0;
}

int isOperator(string ch){
        if (ch=="then")
            return 1;
        if  (ch=="else")
            return 2;
        if (ch=="+")
            return 3;
        if (ch=="-")
            return 4;
        if (ch=="*")
            return 5;
        if (ch=="/")
            return 6;
        if (ch=="=")
            return 7;
        if (ch=="<")
            return 8;
        if (ch=="ifend")
            return 9;
        if (ch==">")
            return 10;
        if (ch=="while")
            return 11;
        if (ch=="do")
            return 12;
        if (ch=="whend")
            return 13;
        if (ch=="fun2")
            return 14;
        if (ch=="@")
            return 8;
        else return 0;
}
void Operator_Number(){
  int i;
  string p=siyuanshi2[j];
    int pointer = 0;
  while (p[pointer]=='('){
      pointer++;
      while (p[pointer]!=','){
          Operate[mm].operationName+=p[pointer];
          pointer++;
      }
      pointer++;
      for (i=0;p[pointer]!=',';i++){
          Operate[mm].opp1[i]=p[pointer];
          pointer++;
      }
      pointer++;
      for (i=0;p[pointer]!=',';i++){
          Operate[mm].opp2[i]=p[pointer];
          pointer++;
      }
      pointer++;
      while (p[pointer]!=')'){
          Operate[mm].ans+=p[pointer];
          pointer++;
      }
      pointer++;
      Operate[mm].temp=isOperator(Operate[mm].operationName);
//      cout<<Operate[mm].temp;
      mm++;
  }
}

string OperatorToString(int i){
    switch(i){
        case 0:
            return "";
        case 1:
            return "JUMP0";
        case 2:
            return "JMP";
        case 3:
            return "ADD";
        case 4:
            return "SUB";
        case 5:
            return "MUL";
        case 6:
            return "DIV";
        case 7:
            return " ";
        case 8:
            return "COMPARE";
        case 9:
            return "";
        case 10:
            return "COMPARE";
        case 11:
            return "";
        case 12:
            return "JUMP0";
        case 13:
            return "JMP";
        case 14:
            return "FUN";
        default:
            return "";
    }
}

int displayOperations1(int k, FILE * out){
    if (OperatorToString(Operate[k].temp)=="")
        return 0;
    else{
        if ((Operate[k].temp==1)||(Operate[k].temp==12))
        {
            if(acc == "_" || acc == Operate[k].opp1)
            {
                if(acc != Operate[k].opp1)
                {
                    cout<<"LD"<<"\t"<<"R"<<","<<Operate[k].opp1<<endl;
                    fprintf(out, "LD\tR,%s\n",Operate[k].opp1);
                }
                cout<<OperatorToString(Operate[k].temp)<<"\t"<<"R"<<","<<Operate[k].opp2<<endl;
                fprintf(out, "%s\tR,%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].opp2);
                acc=Operate[k].ans;
            }
            else
            {
                cout<<"ST"<<"\t"<<"R"<<","<<acc<<endl;
                fprintf(out, "ST\tR,%s\n",acc.c_str());
                cout<<"LD"<<"\t"<<"R"<<","<<Operate[k].opp1<<endl;
                fprintf(out, "LD\tR,%s\n",Operate[k].opp1);
                cout<<OperatorToString(Operate[k].temp)<<"\t"<<"R"<<","<<Operate[k].ans<<endl;
                fprintf(out, "%s\tR,%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].ans.c_str());
                acc=Operate[k].ans;
            }
        }
        if ((Operate[k].temp==2)||(Operate[k].temp==13))
        {
            cout<<OperatorToString(Operate[k].temp)<<"\t"<<Operate[k].ans<<endl;
            fprintf(out, "%s\t%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].ans.c_str());
        }
        if ((Operate[k].temp==4)||(Operate[k].temp==6))
        {
            if(acc == "_" || acc == Operate[k].opp1)
            {
                if(acc != Operate[k].opp1)
                {
                    cout<<"LD"<<"\t"<<"R"<<","<<Operate[k].opp1<<endl;
                    fprintf(out, "LD\tR,%s\n",Operate[k].opp1);
                }
                cout<<OperatorToString(Operate[k].temp)<<"\t"<<"R"<<","<<Operate[k].opp2<<endl;
                fprintf(out, "%s\tR,%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].opp2);
                acc=Operate[k].ans;
            }
            {
                cout<<"ST"<<"\t"<<"R"<<","<<acc<<endl;
                fprintf(out, "ST\tR,%s\n",acc.c_str());
                cout<<"LD"<<"\t"<<"R"<<","<<Operate[k].opp1<<endl;
                fprintf(out, "LD\tR,%s\n",Operate[k].opp1);
                cout<<OperatorToString(Operate[k].temp)<<"\t"<<"R"<<","<<Operate[k].ans<<endl;
                fprintf(out, "%s\tR,%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].ans.c_str());
                acc=Operate[k].ans;
            }
        }
        if ((Operate[k].temp==3)||(Operate[k].temp==5))
        {
            cout<<OperatorToString(Operate[k].temp)<<"\t"<<"R"<<","<<Operate[k].opp2<<endl;
            fprintf(out, "%s\tR,%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].opp2);
        }
        if (Operate[k].temp==7)
        {
            if(acc!="_" && acc!=Operate[k].opp1)
            {
                cout<<"ST"<<"\t"<<"R"<<","<<acc<<endl;
                fprintf(out, "ST\tR,%s\n",acc.c_str());
            }
            if(acc!=Operate[k].opp1)
            {
                cout<<"LD"<<"\t"<<"R"<<","<<Operate[k].opp1<<endl;
                fprintf(out, "LD\tR,%s\n",Operate[k].opp1);
            }
            cout<<"ST"<<"\t"<<"R"<<","<<Operate[k].ans<<endl;
            fprintf(out, "ST\tR,%s\n",Operate[k].ans.c_str());
            acc=Operate[k].ans;
        }
        if (Operate[k].temp==8)
        {
            cout<<OperatorToString(Operate[k].temp)<<"\t"<<Operate[k].opp2<<","<<Operate[k].opp1<<endl;
            fprintf(out, "%s\t%s,%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].opp2,Operate[k].opp1);
        }
        if (Operate[k].temp==10)
        {
            cout<<OperatorToString(Operate[k].temp)<<"\t"<<Operate[k].opp1<<","<<Operate[k].opp2<<endl;
            fprintf(out, "%s\t%s,%s\n",OperatorToString(Operate[k].temp).c_str(),Operate[k].opp1,Operate[k].opp2);
        }
        if (Operate[k].temp==14)
        {
            cout<<OperatorToString(Operate[k].temp)<<":"<<endl;
            fprintf(out, "%s:\n",OperatorToString(Operate[k].temp).c_str());
        }
    }
    return 0;
}

void last(FILE * out){
     int i=0;
    while (siyuanshi2[j].length()!=0){
        Operator_Number();
        j++;
    }
    cout<<"最后生成的汇编代码如下："<<endl;
    for (i=0;Operate[i].operationName.length()!=0;i++){

        displayOperations1(i, out);
    }
}
