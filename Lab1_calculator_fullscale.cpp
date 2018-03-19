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
    //if(full){error("putback() into a full buffer.");}                   //
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
        case'*':case'/':case'%':case'!':                                               //
            return Token(ch);                                            //
        case'.':                                                       //
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
                    error("Bad token");
                    break;
                }
            }                                                                       //
        default:                                                        //    
            error("Bad token");                                 //
    }                                                                   //
}                                                                       //
/*==================finsish=============================================*/

int factorial(double n){
        int n_ = int(n); 
        if(n_ == n){
            if(n_ == 0){
                return 1;
            }else if(n < 0){
                error("negative step err");
            }else{
                int res = 1;
                for(int i = 1; i <= n_; i++){
                    res *= i;
                }
                return res;
            }
        }
        else{
            error("float step err");
            }
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
    Token t = ts.get(); 
    double right;            //
    while(true){                    //
        switch(t.kind){             //
            case'*':    
                right = term();            //
                left *= right;     //
                t = ts.get();       //
                break;              //
            case'/':  
                right = term(); 
                if(right != 0){      //
                    left /= right;     //
                    t = ts.get();       //
                    break;
                }else{
                    t = ts.get();
                    throw('N');
                }
            case'%': 
                    right = term();
                    if(right != 0 && right == int(right)){
                        left = int(left) % int(right);
                        t = ts.get();       //
                        break;  
                    }else{
                        t = ts.get();
                        throw('N');
                    }  //
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
    switch(t.kind){                                     //
        case'(':                                             //
            {                                                //
                double d = expression();                     //
                t = ts.get();                                //
                if(t.kind != ')'){
                    throw(')');
                }     //
                else result = d; break;                                    //
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
        default:    
            t = ts.get();                                         //
            error("primary needed");                       //
    } 
    t = ts.get();
    if(t.kind == '!') return factorial(result);  
    else ts.putback(t);return result;                                                     //
}                                                            //
/*=============finish========================================*/

int main(){/*added*/
    double val = 0;
    bool flag = true;
    while(true){//表达式一定要以(英文全角)分号结尾，否则无法打印结果，或报错后无法开始新一轮循环
        try{
                if(flag)cout<<"> ";
                Token t = ts.get();
                if(t.kind == 'q')break;
                if(t.kind == ';'){//正确表达式读不到分号无法打印
                    cout<<'='<<' '<<val<<endl;
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
            cerr<<e.what()<<endl;//catch的报错是即时的
            while(getchar() != ';' ){//但读不到分号无法退出循环，所以也需要分号       
                cin.sync();//一旦有error，cin清空，避免多行重复报错（表达式中有多个bad token的情况 比如 3+A+f+$;）
                cin.clear();}
        }
        catch(char& e){
            flag = true;
            cerr<<e<<"needed"<<endl;
        }catch(...){
            flag = true;
            cerr<<"unknow error"<<endl;
        }
    }
    return 0;
}
