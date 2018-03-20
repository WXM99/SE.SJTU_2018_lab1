/*lab1_calculator_wxm_submit*/
#include <stdio.h>       //
#include<iostream>       //
#include<cmath>          //
#include<vector>         //
#include<iomanip>        //
#include<string>         //
#include<algorithm>      //
using namespace std;     //
/*-----------------------*/

/**error_function*************/
void error(string s){        //
    throw runtime_error(s);  //
}                            //
/*---------------------------*/

/******Construction of Token*****/
class Token{                    //
public:                         //
    char kind;                  //
    double value;               //
    Token(char ch)              //
        :kind(ch), value(0){}   //
    Token(char ch, double val)  //
        :kind(ch),value(val){}  //
}; Token ans('A',0);            //
                                //
/*=============finish===========*/

/*****************Construction of Token_stream **************************/
class Token_stream{                                                     //
public:                                                                 //
    Token_stream();                                                     //
    Token get();                                                        //
    void putback(Token t);                                              //
private:                                                                //
    bool full;                                                          // 
    Token buffer;                                                       //
};                                                                      //
/*build-in function-----------------------------------------------------*/                
Token_stream::Token_stream()                                            //
    :full(false), buffer(0)                                             //
{                                                                       //
}                                                                       //
/*----------putback(Token)----------------------------------------------*/      
void Token_stream::putback(Token t)                                     //
{                                                                       //
    //if(full){error("putback() into a full buffer.");}                 //
    buffer = t;                                                         //
    full = true;                                                        //
}                                                                       //                                                                     
/*----------get(Token)--------------------------------------------------*/
Token Token_stream::get()                                               //
{                                                                       //
    if(full){                                                           //
        full = false;                                                   //
        return buffer;                                                  //
    }                                                                   //
    char ch;                                                            //
    cin>>ch;                                                            //
    switch(ch){                                                         //
        case';':                                                        //
        case'q':                                                        //
        case'(':case')':                                                //
        case'+':case'-':                                                //
        case'*':case'/':case'%':case'!':                                //                 
            return Token(ch);                                           //
        case'.':                                                        //
        case'0':case'1':case'2':case'3':case'4':                        //
        case'5':case'6':case'7':case'8':case'9':                        //
            {                                                           //
                double val;                                             //
                cin.putback(ch);//put the char back to cin's buffer     //
                cin>>val;//cin can read the number including 'ch'       //
                return Token('D',val);                                  //
            }                                                           //
        case'A':{/*added*/                                              //
                char a1; char a2;                                       //
                cin>>a1>>a2;                                            //
                if(a1 == 'N'&& a2 == 'S')return ans;                    //
                else error("Bad token");                                //
            }                                                           //
        default:                                                        //    
            error("Bad token");                                         //
    }                                                                   //
}                                                                       //
/*==================finsish=============================================*/

/********************factorial******************/
int factorial(double n){                        //
        int n_ = int(n);                        //
        if(n_ == n){                            //
            if(n_ == 0){                        //
                return 1;                       //
            }else if(n < 0){                    //
                error("negative fct err");      //
            }else{                              //
                int res = 1;                    //
                for(int i = 1; i <= n_; i++){   //
                    res *= i;                   //
                }                               //
                return res;                     //
            }                                   //
        }                                       //
        else{                                   //
            error("float fct err");             //
            }                                   //
}                                               //
/*=====================finish===================*/                                               


/*--------grammar_functions---------*/
Token_stream ts;                    //
/*added*/                           //
double expression();                //
double term();                      //
double primary();                   //
/*----------------------------------*/
double expression(){                //
   double left = term();            //
   Token t = ts.get();              //
   while(true){                     //
       switch(t.kind){              //
            case'+':                //
                left += term();     //
                t = ts.get();       //
                break;              //
            case'-':                //
                left -= term();     //
                t = ts.get();       //
                break;              //
            default:                //
                ts.putback(t);      //
                return left;        //       
        }                           //
    }                               //
}                                   //
/*----------------------------------*/
double term(){                      //
    double left = primary();        //
    Token t = ts.get();             //
    while(true){                    //
        switch(t.kind){              //
            case'*':                  //
                left *= primary();     //
                t = ts.get();           //
                break;                   //
            case'/':                      //
                double right;              //
                right = primary();          //
                if(right != 0){              //
                    left /= right;            //
                    t = ts.get();              //
                    break;}                     //
                else{                            //
                    t = ts.get();                 //
                    throw('0');}                   //
            case'%':                                //
                double right_;                       //
                right_ = primary();                   //
                if(right_ !=0 && right_ == int(right_) //
                && left == int(left) )                //
                    {                                //
                    left = int(left) % int(right_); //
                    t = ts.get();                  //
                    break;}                       //
                else{                            //
                    t = ts.get();               //
                    throw('.');                //
                    }                         //
            default:                         //
                ts.putback(t);              //
                return left;               //
        }                                 //
    }                                    //
}                                       //
/*-------------------------------------*/

/***************Grammar functions******************8*/
double primary(){                                   //
    Token t = ts.get();                             //
    double result;                                  //
    switch(t.kind){                                 //
        case'(':                                    //
            {                                       //
                double d = expression();            //
                t = ts.get();                       //
                if(t.kind != ')'){                  //
                    throw(')');                     //
                }                                   //    
                else result = d; break;             //
            }                                       //
        case'D':                                    //
            result = t.value; break;                //
        case'A':/*added*/                           //
            result = ans.value;break;               //
        case'+':                                    //
            {                                       //
                double d = primary();               //
                result = d; break;                  //
            }                                       //
        case'-':                                    //
            {                                       //
                double d = primary();               //
                result = -d; break;                 //
            }                                       //
        default:                                    //
            t = ts.get();                           //
            error("primary needed");                //
    }                                               //
    t = ts.get();                                   //
    if(t.kind == '!') return factorial(result);     //
    else ts.putback(t);return result;               //                                    //
}                                                   //
/*=============finish===============================*/

int main(){/*added*/
    double val = 0;
    bool flag = true;
    while(true){//分号结尾，否则无法打印结果，或报错后无法开始新一轮循环
        try{ 
                if(flag)cout<<"> ";
                Token t = ts.get();
                if(t.kind == 'q')break;
                if(t.kind == ';'){//正确表达式读不到分号无法打印
                    cout<<"= "<<val<<endl;
                    cout<<" "<<endl;
                    flag = true;/*added*/
                    ans.value = val;/*added*/
                }else{
                    flag = false;/*added*/
                    ts.putback(t);
                    val = expression();
                }
            }
        catch(runtime_error& e){
            flag = true;
            cerr<<"error: "<<e.what()<<endl;//catch的报错是即时的
            cout<<" "<<endl;
            while(getchar() != ';' ){//但读不到分号无法退出循环，所以也需要分号       
                cin.sync();//一旦有error，cin清空，避免多行重复报错
                cin.clear();}
        }
        catch(char& e){
            flag = true;
            switch(e){
                case'0':{
                    cerr<<"error: "<<e<<endl;
                    cerr<<" "<<endl;
                    break;}
                case'.':{
                    cerr<<"error: "<<e<<endl;
                    cerr<<" "<<endl;
                    break;}
                case')':{
                    cerr<<"error: "<<e<<endl;
                    cerr<<" "<<endl;
                    break;}
                default:{
                    cerr<<"error: ?"<<endl;
                    cerr<<" "<<endl;
                    }
                }
        }catch(...){
            flag = true;
            cerr<<"error: ?"<<endl;
            cout<<" "<<endl;
        }
    }
    return 0;
}
