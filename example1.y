%include {
	#include <iostream>
	#include "example1.h"
	using namespace std;
}

%token_type { int }
%left PLUS MINUS.
%right DIVIDE TIMES.

%syntax_error {
	cout << "Syntax error!\n" << endl;
	exit(1);
}

program ::= expr(A).{ cout << "Result = " << A << "\n" <<endl;}

expr(A) ::= expr(B) MINUS expr(C). { A = B - C; cout<<"执行减法-->"<<"B:"<<B<<"C:"<<C<< "\n"<<endl;}

expr(A) ::= expr(B) PLUS expr(C). { A = B + C;cout<<"执行加法-->"<<"B"<<B<<"c:"<<C<< "\n"<<endl; }

expr(A) ::= expr(B) TIMES expr(C). { A = B * C; cout<<"执行乘法-->"<<B<<"C:"<<C<< "\n"<<endl;}

expr(A) ::= expr(B) DIVIDE expr(C). 
{ 
	if(C != 0){
		A = B / C;
	}else{
		std:cout << "divide by zeor" << std::endl;
	}
	cout<<"执行除法-->"<<endl;
}

expr(A) ::= INTEGER(B). { A = B; }

%code {
	int main()
	{
		void* pParser = ParseAlloc(malloc);
		Parse(pParser,INTEGER,1);
		Parse(pParser,PLUS,0);
		Parse(pParser,INTEGER,2);
		Parse(pParser,0,0);
		ParseFree(pParser,free);


	}
}


