/*lab1_calculator_0.1_wxm*/
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
};Token ans('A',0);             //
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
/*build-in function----------------------------------*/                 //
Token_stream::Token_stream()                                            //
    :full(false), buffer(0)                                             //
{                                                                       //
}                                                                       //
/*method----putback----------------------------------*/                 //
void Token_stream::putback(Token t)                                     //
{                                                                       //
    if(full){error("putback() into a full buffer.");}                   //
    buffer = t;                                                         //
    full = true;                                                        //
} 
                                                                       //
/*method----get(Token)-------------------------------*/                 //
Token Token_stream::get()                                               //
{                                                                     //
    if(full){                                                           //
        full = false;                                                   //
        return buffer;                                                  //
    }                                                                  //
    char ch;                                                            //
    cin>>ch;                                                           //
    switch(ch){                                                         //
        case';':                                                        //
        case'q':                                                        //
        case'(':case')':                                                //
        case'+':case'-':                                                //
        case'*':case'/':                                                //
            return Token(ch);                                            //
        case'.':                                                        //
        case'0':case'1':case'2':case'3':case'4':                        //
        case'5':case'6':case'7':case'8':case'9':                        //
            {                                                           //
                double val;                                             //
                cin.putback(ch);//put the char back to cin's buffer     //
                cin>>val;//cin can read the number including 'ch'       //
                return Token('D',val);                                  //
            }
        case'A':{
                char a1; char a2;
                cin>>a1>>a2;
                if(a1 == 'N'&& a2 == 'S')return ans;
                else{
                    while(getchar() != ';' ){        
                        cin.sync();
                        cin.clear();
                    } /*added*/
                    error("Bad token");
                }
            }                                                           //
        default: 
            while(getchar() != ';' ){        
                    cin.sync();
                    cin.clear();}                                       //
            error("Bad token");                                         //
    }                                                                   //
};Token_stream ts;                                                                     //
/*==================finsish=============================================*/

/*--------grammar_functions---------*/
                   //
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
        switch(t.kind){             //
            case'*':                //
                left *= term();     //
                t = ts.get();       //
                break;              //
            case'/':                //
                left /= term();     //
                t = ts.get();       //
                break;              //
            default:                //
                ts.putback(t);      //
                return left;        //
        }                           //
    }                               //
}                                   //
/*-----------------------------------------------------------*/
double primary(){                                            //
    Token t = ts.get();                                      //
    switch(t.kind){                                          //
        case'(':                                             //
            {                                                //
                double d = expression();                     //
                t = ts.get();                                //
                if(t.kind != ')'){error("')'expected");}     //
                return d;                                    //
            }                                                //
        case'D':                                             //
            return t.value;  
        case'A': 
            return ans.value;                                //
        default:                                             //
            error("primary expected");                       //
    }                                                        //
}                                                            //
/*=============finish========================================*/

int main(){
    try{
        Token ans('A',0);
        bool flag = true;
        double val = 0;
        while(true){
            if(flag)cout<<">";
            Token t = ts.get();
            if(t.kind == 'q')break;
            if(t.kind == ';'){
                flag = true;
                cout<<'='<<val<<endl;
                ans.value = val;
            }else{
                flag = false;
                ts.putback(t);
                val = expression();
            }
        }
    }catch(runtime_error& e){
        cerr<<e.what()<<endl;
    }
    catch(...){
        cerr<<"unknow error"<<endl;
    }
}
