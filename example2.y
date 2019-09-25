%include {
	#include <iostream>
	#include "example2.h"
	using namespace std;

	struct Token {
		int value;
		unsigned n;
	};
}

%token_type { Token }
%default_type { Token }
%left PLUS MINUS.
%right DIVIDE TIMES.

%syntax_error {
	cout << "Syntax error!\n" << endl;
	exit(1);
}

program ::= expr(A).{ 
					 cout << "Result = " << A.value << "\n" <<endl;
					 cout << "Result = " << A.n <<endl;
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

expr(A) ::= NUM(B). { 
							A.value = B.value;
							A.n = B.n + 1;
 						}

%code {
	int main()
	{
		void* pParser = ParseAlloc(malloc);

		struct Token t0,t1;
		t0.value=4;
		t0.n = 0;
		t1.value = 13;
		t1.n = 0;

		cout << "\t t0.value(4) PLUS t1.value(13) " <<endl;
		Parse(pParser,NUM,t0);
		Parse(pParser,PLUS,t0);
		Parse(pParser,NUM,t1);
		Parse(pParser,0,t0);

		cout << "\t t0.value(4) MINUS t1.value(13) "<<endl;
		Parse(pParser,NUM,t0);
		Parse(pParser,MINUS,t0);
		Parse(pParser,NUM,t1);
		Parse(pParser,0,t0);

		cout << "\t t0.value(4) TIMES t1.value(13) PLUS t1.value(13) PLUS t1.value(13) "<<endl;
		Parse(pParser,NUM,t0);
		Parse(pParser,TIMES,t0);
		Parse(pParser,NUM,t1);
		Parse(pParser,PLUS,t0);
		Parse(pParser,NUM,t1);
		Parse(pParser,PLUS,t0);
		Parse(pParser,NUM,t1);
		Parse(pParser,0,t0);


		ParseFree(pParser,free);


	}
}


