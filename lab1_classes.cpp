/******Construction of Token*****/
class Token{                    //
public:                         //
    char kind;                  //
    double value;               //
    Token(char ch)              //
        :kind(ch), value(0){}   //
    Token(char ch, double val)  //
        :kind(ch),value(val){}  //
};                              //
/*=============finish===========*/

/*Construction of Token_stream */
class Token_stream{
public:
    Token_stream();
    Token get();
    void putback(Token t);
private:
    bool full;
    Token buffer;
};
/*build-in function*/
Token_stream::Token_stream()
    :full(false), buffer(0)
{
}
/*method----putback*/
void Token_stream::putback(Token t)
{
    if(full){error("putback() into a full buffer.");}
    buffer = t;
    full = true;
}
/*method----get_token*/
Token Token_stream::get()
{
    if(full){
        full = false;
        return buffer;
    }
    char ch;
    cin>>ch;
    switch(ch){
        case';':
        case'q':
        case'(':case')':
        case'+':case'-':
        case'*':case'/':
           return Token(ch);
        case'.':
        case'0':case'1':case'2':case'3':case'4':
        case'5':case'6':case'7':case'8':case'9':
            {
                double val;
                cin.putback(ch);//put the char back to cin's buffer  
                cin>>val;//and cin can read the whole number automatically 
                return Token('D',val);
            }
        default:
            error("Bad token");
    }
}
/*==================finsish===================*/
