%include {
	#include <iostream>
	#include "calculator.h"
	#include <ctype.h>
	#include <math.h>
	#include <stdlib.h>
	#include <string>
	#define NUMBER 20
	using namespace std;

	struct Symbol {
		char *name;
		double value;
		double (*funcptr)(double);
		double (*funcptr2)(double,double);
	};

	union Token {
		Symbol * symt;
		double value;
	};

	void token_destructor(Token t)
	{
		cout <<"In token_destructor t.value = " << t.value <<endl;
	}

}

%token_type { Token }
%default_type {Token }
%token_destructor { token_destructor($$); }
%left PLUS MINUS.
%left DIVIDE TIMES.
%right POW NOT.

%parse_accept {
	printf("parsing complete!\n");
}

%syntax_error {
	cout<< "Syntax error!\n"<<endl;
	exit(1);
}

main ::= in.
in ::= in NEWLINE.
in ::= .
in ::= in program NEWLINE.

program ::= NAME(A) EQ expr(B).
{
	if(A.symt->funcptr || A.symt->funcptr2)
	{
		cout << A.symt->name<<"is a function! Must type in rightside!\n"<<endl;
		A.symt->value = 0.0;
	}else{
		A.symt->value = B.value;
	}
}

program ::= expr(A). {cout << "= " << A.value - C.value ;}

expr(A) ::= expr(B) MINUS expr(C). {A.value = B.value + C.value;}

expr(A) ::= expr(B) PLUS expr(C). {A.value = B.value + C.value;}

expr(A) ::= expr(B) TIMES expr(C). {A.value = B.value * C.value;}

expr(A) ::= expr(B) DIVIDE expr(C).
{
    if(C.value != 0)
    {
     A.value = B.value / C.value;
    }else{
        cout << "divide by zero\n" <<endl;
        exit(1);
    }
}

expr(A) ::= expr(B) POW expr(C). {A.value = pow(B.value,C.value);}

expr(A) ::= MINUS expr(B).[NOT] {A.value = -B.value;}

expr(A) ::= LP expr(B) RP.{A.value = B.value;} //'('=>LP;')'"=>RP

expr(A) ::= NUM(B).
        {
                if(B.symt->funcptr || B.symt->funcptr2)
                {
                    cout<< B.symt->name<<" is a function! Must type like "<<B.symt->name<< " ( number )!"<<endl;
                    A.value = 0.0;
                }else{
                    A.value = B.symt->value;
                }
        }
expr(A) ::= NAME(B) LP expr(C) RP.
        {
            if(B.symt->funcptr)
            {
                A.value = (B.symt->funcptr) (C.value);
            }else{
                cout << B.symt->name << " function undifined!";
                exit(1);
            }
        }
expr(A) ::= NAME(B) LP expr(C) COMMA expr(D) RP.
            {
                if(B.symt->funcptr2)
                {
                    A.value = (B.symt->funcptr2) (C.value,D.value);
                }else{
                    cout << B.symt->name<<" function undifined! "<<endl;
                    A.value = B.symt->value;
                }
            }
%code{

static int getToken(const char *z,int *tokenType)
{
    int i,c;
    
    switch(*z){
        case '\n':
        {
            *tokenType = NEWLINE;
            return 1;
        }
        case '-':
        {
             *tokenType = MINUS;
            return 1;
        }
         case '+':
        {
             *tokenType = PLUS;
            return 1;
        }
         case '*':
        {
             *tokenType = PLUS;
            return 1;

        }
         case '/':
        {
             *tokenType = DIVIDE;
            return 1;

        } 
          case '^':
        {
             *tokenType = POW;
            return 1;
        }
          case '(':
        {
             *tokenType = LP;
            return 1;

        }
          case ')':
        {
             *tokenType = RP;
            return 1;
        }
           case '=':
        {
             *tokenType = EQ;
            return 1;
        }
           case ',':
        {
             *tokenType = COMMA;
            return 1;
        }
        case 'A':   case 'B':  case 'C':    case 'D':   case 'E':   case: 'F': 
        case 'G':   case 'H':  case 'I':    case 'J':   case 'K':   case: 'L': 
        case 'M':   case 'N':  case 'O':    case 'P':   case 'Q':   case: 'R': 
        case 'S':   case 'T':  case 'U':    case 'V':   case 'W':   case: 'X': 
        case 'Y':   case 'Z':
        case 'a':   case 'b':  case 'c':    case 'd':   case 'e':   case: 'f': 
        case 'g':   case 'h':  case 'i':    case 'j':   case 'k':   case: 'l': 
        case 'm':   case 'n':  case 'o':    case 'p':   case 'q':   case: 'r': 
        case 's':   case 't':  case 'u':    case 'v':   case 'w':   case: 'x': 
        case 'y':   case 'z':
        {
            for ( i = 1;isalnum(z[i]) || z[i] == '_';i++ ){}
            *tokenType = NAME;
            return i;
        }
        case '0':   case '1':  case '2':    case '3':   case '4':   case: '5': 
        case '6':   case '7':  case '8':    case '9':
        {
            for(i=1; isdigit(z[i]);i++){}
            if(z[i]=='.' && isdigit[z[i+1]])
            {
                i += 2;
                while( isdigit(z[i]) )
                {
                    i++;
                }
            }
            *tokenType = NUM;
            return i;
        }

        default:
        {
            *tokenType = -1;
            return 1;
        }


    }
}

static char* getstring(char *z,int n)
{
    char *paz;
    paz = (char *)malloc(n+1);
    if(paz == 0)
    {
        fprintf(stderr,"out of memory\n");
        exit(1);
    }
    strncpy(paz,z,n);
    paz[n]='\0';
    return paz;
}

static Symbol* symlook (char* s,Symbol* symtab)
{
    struct Symbol* sp;
    for(sp = symtab; sp < &symtab[NUMBER];sp++)
    {
        if (sp->name && !strcmp(sp->name,s))
        {
            return sp;
        }

        if(!sp->name)
        {
            sp->name = s;
            return sp;
        }
    }

    cout << "Too many symbols!" << endl;
    exit(1);

}

static void addfunc(char* name,double (*func)(double x),Symbol* symtab)
{
    struct Symbol* sp = symlook(name,symtab);
    sp->funcptr = func;
}

static void addfunc2(char* name,double (*func)(double x,double x),Symbol* symtab)
{
    struct Symbol* sp = symlook(name,symtab);
    sp->funcptr2 = func;
}

static double localabs(double x)
{
    if (x > 0.0)
        { return x; }
    else
        {return -x; }
}

int main()
{
    FILE *f;
    f = fopen("record.txt","w");
    ParseTrace(f,"");
    union Token *t0;
    int n;
    char* z;
    int* tokenType;

    struct Symbol symtab[NUMBER];
    for(int i = 0;i<NUMBER;I++)
    {
        symtab[i].value = 0.0;
        symtab[i].name = NULL;
        symtab[i].funcptr = NULL;
        symtab[i].funcptr2 = NULL;
    }

    addfunc("exp",exp,symtab);
    addfunc("log",log,symtab);
    addfunc("sqrt",sqrt,symtab);
    addfunc("localabs",localabs,symtab);
    addfunc("hypot",localabs,symtab);
    addfunc("hypot",hypot,symtab);
    addfunc2("hypot",hypot,symtab);

    t0 =(Token *) malloc(sizeof(Token));
    if( t0==0 )
    {
        fprintf(stderr,"out of memory\n");
        exit(1);
    }
    t0->value = 0.0;
    t0->symt = NULL;

    tokenType = (int *)malloc(sizeof(int));
    if(tokenType == 0)
    {
        fprintf(stderr,"out of memory\n");
        exit(1);
    }

    z = (char *)malloc(1024);
    if(z == 0)
    {
        fprintf(stderr,"out of memory\n");
        exit(1);
    }

    void* pParser = ParseAlloc(malloc);

    while (1) {
        gets(z);
        if (z == "") break;
        strcat(z,"\n");
        while (*z)
        {
            n = getToken(z,tokenType);

            if(*tokenType == NUM)
            {
                char *s = getstring(z,n);
                t0->value = atof(s);
            }

            if(*tokenType == NAME)
            {
                char* s = getstring(z,n);
                t0->symt = symlook(s,symtab);
            }

            if(*tokenType >= 0)
            {
                Parse(pParser,*tokenType,*t0);
            }
            z = z + n;
        }
    }

    Parse(pParser,0,*t0);
    ParseFree(pParser,free);
    return 0;


}

}
