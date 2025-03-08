#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <ctype.h>
#include <algorithm>

using namespace std;


enum type_of_lex {
    LEX_NULL,                                                               /*0*/
    LEX_AND,   LEX_BREAK,  LEX_BOOL,     LEX_DO,    LEX_ELSE,    LEX_IF,    /*6*/
    LEX_FALSE, LEX_INT,    LEX_NOT,      LEX_OR,    LEX_PROGRAM, LEX_READ,  /*12*/
    LEX_THEN,  LEX_TRUE,   LEX_WHILE,    LEX_WRITE, LEX_STRING,  LEX_FOR,   /*18*/
    LEX_GOTO,  LEX_STRUCT,                                                  /*20*/
    LEX_FIN,                                                                /*21*/
    LEX_SEMICOLON, LEX_COMMA,   LEX_COLON,  LEX_ASSIGN,   LEX_LPAREN,       /*26*/
    LEX_RPAREN,    LEX_EQ,      LEX_LSS,    LEX_GTR,      LEX_PLUS,         /*31*/
    LEX_MINUS,     LEX_LBRACE,  LEX_RBRACE, LEX_TIMES,    LEX_SLASH,        /*36*/
    LEX_LEQ,       LEX_NEQ,     LEX_GEQ,    LEX_POINT,                      /*40*/
    LEX_NUM,                                                                /*41*/
    LEX_ID,                                                                 /*42*/
    LEX_STR,                                                                /*43*/
    POLIZ_LABEL,                                                            /*44*/ 
    POLIZ_ADDRESS,                                                          /*45*/
    POLIZ_GO,                                                               /*46*/
    POLIZ_FGO,                                                              /*47*/
    POLIZ_MINUS,                                                            /*48*/
    LEX_OBJECT                                                              /*49*/
};  

class Lex {
    type_of_lex   t_lex;
    int           v_lex;
    string str;
public:
    Lex ( type_of_lex t = LEX_NULL, int v = 0, string s = "" ): t_lex (t), v_lex (v), str(s) { }
    type_of_lex  get_type () const { 
    	  return t_lex; 
    }
    int get_value () const { 
    	  return v_lex; 
    }
    string get_string() const {
        return str;
    }
  friend ostream & operator<< ( ostream &s, Lex l );
};

class Ident {
    string      name;
    bool        declare;
    type_of_lex type;
    bool        assign;
    int         value;
    string str;
public:
    Ident() { 
        declare = false; 
        assign  = false; 
        str = "";
    }
    bool operator== ( const string& s ) const { 
        return name == s; 
    }
    Ident ( const string n ) {
        name    = n;
        declare = false; 
        assign  = false;
        str = "";
    }
    string get_name () const { 
      return name; 
    }
    bool get_declare () const { 
      return declare; 
    }
    void put_declare () { 
      declare   = true; 
    }
    type_of_lex get_type () const { 
      return type; 
    }
    void put_type ( type_of_lex t ) { 
      type      = t; 
    }
    bool get_assign () const { 
      return assign; 
    }
    void put_assign () { 
      assign    = true; 
    }
    int  get_value () const { 
      return value; 
    }
    void put_value ( int v ) { 
      value     = v; 
    }
    string get_string() {
        return str;
    }
    void put_value(string s) {
        str = s;
    }
};

vector<Ident> TID;
 
int put ( const string & buf ) {
    vector<Ident>::iterator k;
 
    if ( ( k = find ( TID.begin (), TID.end (), buf ) ) != TID.end () )
        return k - TID.begin();
    TID.push_back ( Ident(buf) );
    return TID.size () - 1;
}

class Scanner {
    FILE * fp;
    char   c;
    int look ( const string buf, const char ** list ) {
        int i = 0;
        while ( list[i] ) {
            if ( buf == list[i] )
                return i;
            ++i;
        }
        return 0;
    }
    void gc () {
        c = fgetc (fp);
    }
public:
    static const char * TW [], * TD [];
    Scanner ( const char * program ) {
        if ( !(fp = fopen ( program, "r" )) ) 
            throw  "can't open file" ;
    }
    Lex get_lex ();
};

const char *
Scanner::TW    [] = { "", "and", "break", "bool", "do", "else", "if", "false", "int", "not", "or", "program",
                      "read", "then", "true", "while", "write", "string", "for", "goto", "struct", NULL };
 
const char *
Scanner::TD    [] = { "@", ";", ",", ":", "=", "(", ")", "=", "<", ">", "+", "-", "{", "}", "*", "/", "<=", "!=", ">=", ".", NULL };
 
Lex Scanner::get_lex () {
    enum    state { H, IDENT, NUMB, COM, COM1, COM2, ALE, NEQ, STR };
    int     d, j;
    string  buf;
    state   CS = H;
    do {
        gc();
        if ( c == EOF && CS != H)
            throw "Unclosed comment or string!";
        else if (c == EOF)
            return (Lex(LEX_FIN));        switch ( CS ) {
            case H:
                if ( c==' ' || c == '\n' || c== '\r' || c == '\t' ); 
                    else if ( isalpha (c) ) {
                        buf.push_back (c);
                        CS  = IDENT;
                    }
                    else if ( isdigit (c) ) {
                        d   = c - '0';
                        CS  = NUMB;
                    } 
                    else if ( c== '/' ) { 
                        CS  = COM1;
                    }
                    else if ( c == '=' || c == '<' || c == '>' ) { 
                        buf.push_back (c);
                        CS  = ALE; 
                    }
                    else if (c == '!') {
                        buf.push_back (c);
                        CS  = NEQ;
                    }
                    else if (c == '"') {
                        CS = STR;
                        cout << "ok" << endl;
                    }
                    else {
                        buf.push_back (c);
                        if ( ( j = look ( buf, TD) ) ){
                            return Lex ( (type_of_lex)( j + (int) LEX_FIN ), j );
                        }
                        else
                            throw c;
                    }
                    break;
            case STR:
                if (c != '"') {
                    buf.push_back(c);
                }
                else {
                    return Lex (LEX_STRING, 0);
                }
                break;
            case IDENT:
                if ( isalpha (c) || isdigit (c) ) {
                    buf.push_back (c); 
                }
                else {
                    ungetc ( c, fp );
                    if ( (j = look ( buf, TW) ) ) {
                        return Lex ( (type_of_lex) j, j );
                        }
                        else {
                        j   = put ( buf );
                        return Lex ( LEX_ID, j );
                    }
                }
                break;
            case NUMB:
                if ( isdigit (c) ) {
                    d = d * 10 + ( c - '0' );
                }
                else {
                    ungetc ( c, fp );
                    return Lex ( LEX_NUM, d );
                }
                break;
            case COM1:
                if (c == '*') {
                    CS = COM;
                }
                else {
                    ungetc (c, fp);
                    return Lex (LEX_SLASH, 15);
                }
                break;
            case COM2:
                if (c == '/') {
                    CS = H;
                }
                else if ( c != '*') {
                    CS = COM;
                }
                break;
            case COM:
                if ( c == '*' ) {
                    CS = COM2;
                }
                break;
            case ALE:
                if ( c == '=' ) {
                    buf.push_back ( c );
                    j   = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_FIN ), j );
                }
                else {
                    ungetc ( c, fp );
                    j   = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_FIN ), j );
                }
                break;
            case NEQ:
                if ( c == '=' ) {
                    buf.push_back(c);
                    j   = look ( buf, TD );
                    return Lex ( LEX_NEQ, j );
                }
                else
                    throw '!';
                break;
    } //end switch
  } while (true);
}  

ostream & operator<< ( ostream &s, Lex l ) {
    string t;
    if ( l.t_lex <= LEX_WRITE )
        t = Scanner::TW[l.t_lex];
    else if ( l.t_lex >= LEX_FIN && l.t_lex <= LEX_GEQ )
        t = Scanner::TD[ l.t_lex - LEX_FIN ];
    else if ( l.t_lex == LEX_NUM )
        t = "NUMB";
    else if ( l.t_lex == LEX_ID )
        t = TID[l.v_lex].get_name ();
    else if ( l.t_lex == POLIZ_LABEL )
        t = "Label";
    else if ( l.t_lex == POLIZ_ADDRESS )
        t = "Addr";
    else if ( l.t_lex == POLIZ_GO )
        t = "!";
    else if ( l.t_lex == POLIZ_FGO ) 
        t = "!F";
    else if (l.t_lex == LEX_STRING) {
        t = "string";
    }
    else
        throw l;
    if (l.str != "") {
        s << '(' << t << ',' << l.str << ");" << endl;
    }
    else
        s << '(' << t << ',' << l.v_lex << ");" << endl;
    return s;
}

int main(int argc, char** argv) {
    try {
        Scanner              scanner(argv[1]);
        Lex                  currLex;
        type_of_lex          currType;
        int                  currValue;
        do {
        currLex = scanner.get_lex();
        currType = currLex.get_type();
        cout << currLex << endl;
        } while(currType != LEX_FIN);
        return 0;
    }
    catch (char c) {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex l) {
        cout << "unexpected lexeme" << l << endl;
        return 1;
    }
    catch (const char* c) {
        cout << c << endl;
        return 1;
    }
}