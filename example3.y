%include {
	#include <iostream>
	#include "example3.h"
	#include <ctype.h>
	#include <math.h>
	#include <stdlib.h>
	#include <string>
	#define NUMBER 20
	using namespace std;

	struct Token {
		double value;
		unsigned n;
	};
}

%token_type { Token }
%default_type { Token }
%left PLUS MINUS.
%left DIVIDE TIMES.
%right POW NOT.
%parse_accept {
	printf("parsing complete!\n");
}

%syntax_error {
	cout << "Syntax error!\n" << endl;
	exit(1);
}

main ::= in.
in ::= in NEWLINE.
in ::= .
in ::= in program NEWLINE.

program ::= expr(A).{ 
					 cout << "Result = " << A.value << "\n" <<endl;
					 cout << "count = " << A.n <<endl;
					}

expr(A) ::= expr(B) MINUS expr(C). {
									 A.value = B.value - C.value;
									 A.n = B.n + 1 + C.n + 1;
									 cout<<"执行减法-->"<<"b:"<<B.value<<"c:"<<C.value<< "\n"<<endl;
									}

expr(A) ::= expr(B) PLUS expr(C). { 
									A.value = B.value + C.value;
									A.n = B.n + 1 + C.n + 1;
									cout<<"执行加法-->"<<"b"<<B.value<<"c:"<<C.value<< "\n"<<endl;
								  }

expr(A) ::= expr(B) TIMES expr(C). {
									 A.value = B.value * C.value;
									 A.n = B.n + 1 + C.n + 1;
									 cout<<"执行乘法-->"<<B.value<<"c:"<<C.value<< "\n"<<endl;
									 }

expr(A) ::= expr(B) DIVIDE expr(C). 
{ 
	if(C.value != 0){
		A.value = B.value / C.value;
		A.n = B.n + 1 + C.n + 1;
	}else{
		std:cout << "divide by zeor" << std::endl;
	}
	cout<<"执行除法-->"<<endl;
}

expr(A) ::= expr(B) POW expr(C).{
								A.value = pow(B.value,C.value);
								}

expr(A) ::= MINUS expr(B).[NOT] {
								 A.value = - B.value;
								}
expr(A) ::= LP expr(B) RP. {
							A.value = B.value;
						 }


expr(A) ::= NUM(B). { 
							A.value = B.value;
							A.n = B.n + 1;
 						}

%code {

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
				*tokenType = TIMES;
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
			case '0': case '1':	case '2': case '3':	case '4':
			case '5': case '6':	case '7': case '8':	case '9':
			{
				for(i=1;isdigit(z[i]);i++){}
				if( z[i] == '.' && isdigit(z[i+1])){
					i += 2;
					while(isdigit(z[i]))
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
		if( paz==0 )
		{
			fprintf(stderr,"out of memory\n");
			exit(1);
		}

		strncpy(paz,z,n);
		paz[n] = '\0';
		return paz;

	}

	int main()
	{

		FILE *f;

		f = fopen("record.txt","w");
		ParseTrace(f,"");

		struct Token* t0;
		int n;
		char *z;
		int* tokenType;
		t0 = (Token *)malloc(sizeof(Token));
		if(t0==0)
		{
			fprintf(stderr,"out of memory\n");
			exit(1);
		}

		t0->value = 0.0;
		t0->n = 0;

		tokenType = (int*)malloc(sizeof(int));
		if(tokenType==0 )
		{
			fprintf(stderr,"out of memory\n");
			exit(1);
		}

		z = (char*)malloc(1024);
		if(z==0){
			fprintf(stderr,"out of memory\n");
		}

		void* pParser = ParseAlloc(malloc);


		while(1){
			gets(z);
			if(z== "") break;
			strcat(z,"\n");
			while(*z)
			{
				n = getToken(z,tokenType);

				if(*tokenType == NUM)
				{
					char*s = getstring(z,n);
					t0->value = atof(s);
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

		ParseTrace(NULL,"");
		fclose(f);
		return 0;


	}
}


