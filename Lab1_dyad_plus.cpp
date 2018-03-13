/*Day1-- dyad plus*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
inline void keep_wondow_open(){char ch; cin>>ch;}

int main(){
    cout<<"expression: "<<endl;
    double lval = 0;
    double rval = 0;
    cin>>lval;
    if(!cin){
        error("enter numbers first");
    }
    for(char op; cin>>op; ){
        
        if(op != ';'){
            cin>>rval;
        }
        switch(op){
            case'+': lval += rval; break;
            case'-': lval -= rval; break;
            case'*': lvak *= rval; break;
            case'/': lval /= rval; break;
            default://''
                cout<<"result: "<<lval<<endl;
                keep_window_open();
                return 0;           
        }
    }
}
