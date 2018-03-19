/*lab1_calculator_0.2_wxm*
factorial and sign added； priority fixed/
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
};   
Token ans('A',0);/*added*/               //
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
        case'*':case'/': case'!':                                               //
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
        case'A':{/*added*/
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
            }                                                                       //
        default:                                                        //
            while(getchar() != ';' ){        
                    cin.sync();
                    cin.clear();}   /*added*/      
            error("Bad token");                                 //
    }                                                                   //
}                                                                       //
/*==================finsish=============================================*/
/*=====================================*/
int factorial(double n){
        int n_ = int(n); 
        if(n_ == n){
            if(n_ == 0){
                return 1;
            }else if(n < 0){
                error("negative fct err");
            }else{
                int res = 1;
                for(int i = 1; i <= n_; i++){
                    res *= i;
                }
                return res;
            }
        }
        else error("float fct err");
}
/*--------grammar_functions---------*/
Token_stream ts; 
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
    Token t = ts.get(); 
    double result;                                      //
    switch(t.kind){                                         //
        case'(':                                             //
            {                                                //
                double d = expression();                     //
                t = ts.get();                                //
                if(t.kind != ')'){error("')'expected");}     //
                result = d; break;                                    //
            }                                                //
        case'D':                                             //
            result = t.value; break;
        case'A':/*added*/
            result = ans.value;break;   
        case'+': 
            {
                double d = primary();
                result = d; break;
            } 
        case'-': 
            {
                double d = primary();//good way to deal ++-- and -5!
                result = -d; break;
            }                          //
        default:                                             //
            error("primary expected");                       //
    } 
    t = ts.get();
    if(t.kind == '!') return factorial(result);  
    else ts.putback(t);return result;                                                     //
}                                                            //
/*=============finish========================================*/

int main(){/*added*/
    double val = 0;
    bool flag = true;
    while(true){
                /*swift*/
    try{
            if(flag)cout<<">";
            Token t = ts.get();
            if(t.kind == 'q')break;
            if(t.kind == ';'){
                flag = true;/*added*/
                cout<<'='<<val<<endl;
                ans.value = val;/*added*/
            }else{
                flag = false;/*added*/
                ts.putback(t);
                val = expression();
            }
        }
    catch(runtime_error& e){
        cerr<<e.what()<<endl;
    }
    catch(...){
        cerr<<"unknow error"<<endl;
    }
    }
    return 0;
}
