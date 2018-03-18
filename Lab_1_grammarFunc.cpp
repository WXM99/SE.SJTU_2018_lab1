/*--------grammar_functions------------*/
Token_stream ts;
double expression();
double term();
double primary();

double expression(){
   double left = term();
   Token t = ts.get();
   while(true){
       switch(t.kind){
            case'+':
                left += term();
                t = ts.get();
                break;
            case'-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;      
        }
    }
}

double term(){
    double left = primary();
    Token t = ts.get();
    while(true){
        switch(t.kind){
            case'*':
                left *= term();
                t = ts.get();
                break;
            case'/':
                left /= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

double primary(){
    Token t = ts.get();
    switch(t.kind){
        case'(':
            {   
                double d = expression();
                t = ts.get();
                if(t.kind != ')'){error("')'expected");}
                return d;
            }
        case'D':
            return t.value;
        default:
            error("primary expected");
    }
}
