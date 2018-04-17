#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include"error_handing.h"  
using namespace std;     


/**************Token*************/
class Token{                    // 单词类，是表达式的基本元素
public:                         // 包括 数字 符号 ANS 
    char kind;                  //
    double value;               //
    Token(char ch)              // 符号子类
        :kind(ch), value(0){}   //
    Token(char ch, double val)  // 数字子类 包含数字的值
        :kind(ch),value(val){}  //
};                              //
/*==============================*/
struct Fomula{
    string exp;
    double ans;
    Fomula(string s, double a)
        :exp(s),ans(a){}
    Fomula(string s)
        :exp(s),ans(0){}
    Fomula()
        :exp(""),ans(0){};
    void clean(){
        exp = "",
        ans = 0;
    };
    
    void exp_adding(const char&t){
        if(t != ';'){
            exp += t;
        }
    }

    void exp_adding(const Token ans){
            stringstream d2s;
            d2s<<ans.value;
            exp += d2s.str();
            //exp += to_string(ans.value);
    };
    void exp_adding(const double &t){
        stringstream d2s;
        d2s<<t;
        exp += d2s.str();
        //exp += to_string(t);
    }
};

static vector<Fomula> history;
static Fomula present;
stringstream expStr;

static Token ans('A',0);               // 全局变量ans 用来持续记录每次表达式的结果


/************************Token_stream ***********************************/
class Token_stream{                                                     /* 这个类用来读取表达式，是对cin做了一个出口改装*/
public:                                                                 //
    Token_stream();                                                     //
    Token get();                                                        /* 读一个Token*/
    void putback(Token t);                                              /* 放回一个Token*/
private:                                                                //
    bool full;                                                          /* 缓存一个Token*/ 
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
    if(full){error("putback() into a full buffer.");}                   //
    buffer = t;                                                         //
    full = true;                                                        //
}                                                                       //                                                                     
/*----------get(Token)--------------------------------------------------*/
Token Token_stream::get()                                               //
{                                                                       //
    if(full){                                                           //
        full = false;                                                   //
        return buffer;                                                  //
    }      
    char ch; 
                                                              //
    expStr >> ch; 
    if(ch == ';'){expStr.clear();expStr.sync();}                                                            //
                                                             //
    switch(ch){                                                         //
        case ';':                                                     //
        case 'q':                                                      //
        case'!':                                                        // 
        case'(':case')':                                                // 
        case'+':case'-':                                                //
        case'*':case'/':case'%':  
            present.exp_adding(ch);                                       //           
            return Token(ch);                                                        // 符号类型 返回char  
        case'.':                                                        //
        case'0':case'1':case'2':case'3':case'4':                        //
        case'5':case'6':case'7':case'8':case'9':                        //
            {                                                           // 数字类型，还得用cin来读
                double val;                                             //
                expStr.putback(ch);//判断后的放回                            //
                expStr>>val;//cin的读取数据的方式  
                present.exp_adding(val);                           //
                return Token('D',val);                                  //
            }                                                           //
        case'A':{//ANS类型                                               // ANS
                char a1; char a2;                                       // A_ _不是ANS也报错
                expStr>>a1>>a2;                                           //
                if(a1 == 'N'&& a2 == 'S'){
                    present.exp_adding(ans);
                    return ans;}           // 
                else error("Bad token");                                //
            }                                                           //
        default:                                                        //
            error("Bad token");                                         //
    }                                                                   //
}                                                                       //
/*======================================================================*/

static Token_stream ts;                                //全局变量ts，用来持续读取表达式

/***************factorial()阶乘函数***************/
int factorial(double n){                        //
        int n_ = int(n);                        // 整数判断
        if(n_ == n){                            //
            if(n_ == 0){                        //
                return 1;                       //
            }else if(n < 0){                    // 符号判断
                error("negative fct err");      //
            }else{                              //
                int res = 1;                    //
                for(int i = 1; i <= n_; i++){   // 阶乘
                    res *= i;                   //
                }                               //
                return res;                     //
            }                                   //
        }                                       //
        else{                                   //
            error("float fct err");             //
            }                                   //
}                                               //
/*==============================================*/                                               
                             
/*--------------------词法函数-----------------------*/
double expression();                                // primary()要用，先声明一下

double primary(){                                   // 最高优先级primary()
    Token t = ts.get();      
    if(t.kind == ';') t = ts.get();                       // 包含无符号数字 'D'
    double result;                                  //    有符号数字  '+' '-'
    switch(t.kind){ 
        //case';':break;                                //    括号内部表达书 '('
        case'(':                                    //    primary()的阶乘 '!'
            {                                       // 括号的处理方式同Bjarne
                double d = expression();            //
                t = ts.get();                       //   
                if(t.kind != ')'){                  // 改变了错误种类（参见main()中catch部分注释）
                    throw(')');                     //
                }                                   //    
                else result = d; break;             //
            }                                       //
        case'D':                                    // Digit 代表无符号数字类型
            result = t.value; break;                //
        case'A':                                    // Answer 上次结果类型
            result = ans.value; break;              //
        case'+':                                    // sign 有符号数字类型
            {                                       // 
                double d = primary();               // 递归调用primary(), 最终读取无符号数字
                result = d; break;                  // 递归调用(而非ts.get()读下一位)的优势是处理连续的符号
            }                                       // 返回值d的等级仍然是primary
        case'-':                                    // 
            {                                       // 
                double d = primary();               // 在这里递归调用primary()让阶乘优先级高于负号
                result = -d; break;                 // 返回有符号的数字
            }                                       //
        default: 
                                             //
            cerr<<"bad pri-->"<<t.kind<<"<>"<<t.value<<endl;
                                      //
            error("primary needed");                //
    }                                               //
    t = ts.get();                                   //
    if(t.kind == '!') return factorial(result);     // digit后一位判断阶乘
    else ts.putback(t);return result;               // 有则调用factorial()
}                                                   // 无则吐回，返回原值 
/*--------------------------------------------------*/
double term(){                                      // 第二优先级term()
    double left = primary();                        // 包括primary()之间的'*''/''%'运算
    Token t = ts.get();                             // 
    while(true){                                    //
        switch(t.kind){                             //
            case'*':                                //
                left *= primary();                  //
                t = ts.get();                       //
                break;                              //
            case'/':                                //
                double right;                       // 
                right = primary();                  // primary()仅传递值到right防止判断时再次读取
                if(right != 0){                     // 用right判断
                    left /= right;                  //
                    t = ts.get();                   //
                    break;}                         //
                else{                               //
                    t = ts.get();                   // 第二类报错（参见main()函数catch部分注释）
                    throw('0');}                    //
            case'%':                                //
                double right_;                      // 变量right_同理
                right_ = primary();                 //
                if(right_ !=0                       // 取模的条件判断
                && right_ == int(right_)            //
                && left == int(left) ){             //
                    left = int(left) % int(right_); //
                    t = ts.get();                   //
                    break;                          //
                    }else{                          //
                    t = ts.get();                   // 
                    throw('.');                     // 第二类报错
                    }                               //
            default:                                //
                ts.putback(t);                      //
                return left;                        //
        }                                           //
    }                                               //
}                                                   //
/*--------------------------------------------------*/
double expression(){                                // 最低优先级 expression()
   double left = term();                            //
   Token t = ts.get();                              //
   while(true){                                     //
       switch(t.kind){                              //
            case'+':                                //
                left += term();                     //
                t = ts.get();                       //
                break;                              //
            case'-':                                //
                left -= term();                     //
                t = ts.get();                       //
                break;                              //
            default:                                //
                ts.putback(t);                      //
                return left;                        //       
        }                                           //
    }                                               //
}                                                   //
/*==================================================*/

void calculate(){
    double val = 0;
    bool prompt = true;//prompt作为打印“>”的开关
    while(true){
        try{//一次IO
            if(prompt)cout<<"> ";                 
            Token t = ts.get();
            if(t.kind == ';'){// 分号先处理，解决exp；exp；的情况
                t = ts.get(); // 即ts越过分号，开始处理下一个exp
            }
            if(t.kind == 'q' ){
                break;
            }else{
                ts.putback(t);
            }

            val = expression();
            
            prompt = false; // 开始读取表达式后prompt关闭，避免输出结果打印“>”
            cout<<"= "<<val<<endl;
            cout<<" "<<endl;

            present.ans = val;
            history.push_back(present);
            present.clean();
            ans.value = val;//ANS的赋值 
            
            char end = expStr.get();
            if(end == '\n') prompt = true;//输入达到结尾，打开开关，为下次打印prompt
            else expStr.putback(end);
        }
        
        catch(runtime_error& e){ 
            present.clean();                   //第一类报错（输入不合法）需要清空输入流
            prompt = true;
            cerr<<"error"<<endl;
            cout<<" "<<endl;
            while(getchar() != ';' ){               //cin清空，避免多行重复报错   
                expStr.sync();
                expStr.clear();}
        }
        catch(char& e){
            present.clean();
            prompt = true;                            //第二类报错（数字类型错误无需清空cin）
            cerr<<"error"<<endl;
            cerr<<" "<<endl;
        }catch(...){  
            present.clean();                              //第三类报错（未知原因）
            prompt = true;
            cerr<<"error"<<endl;
            cout<<" "<<endl;
        }
    }
}
double swift(string s){
    s+=';';
    expStr<<s;
    double val;
    //Token t = ts.get();
    val = expression();
    present.ans = val;
    history.push_back(present);
    present.clean();
    ans.value = val;//ANS的赋值 

    expStr.clear();
    expStr.sync();
    expStr.str("");
    return val;
}


int main(){  
    vector<string> sample;
    sample.push_back("11*12/(1+(1/2))+5*(6-4)*31");
    sample.push_back("1+++3;");
    sample.push_back("-2*-9++4*-2");
    sample.push_back("9+222%77*7*8-3*3*33%23");
    sample.push_back("-5!");
    sample.push_back("3/1.5+6*2.5-12*3");

    for(int i = 0;i<6;i++){
        cerr<<"="<<swift(sample[i])<<"\n";
    }
    
    for(int i = 0;i<history.size();i++){
        cerr<<"No."<<i+1<<": "<<history[i].exp<<" = "<<history[i].ans<<"\n";
    }
    return 0;
}
