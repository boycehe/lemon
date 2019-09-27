%include {

 	
 	struct Token {

 	}

}

%token_type {Token}
%type where_opt {Expr*}
%type select {Select*}
%type orderby_opt {ExprList*}
%type limit_opt {struct LimitVal}
%type selcollist {ExprList*}

cmd ::= CREATE(X) TASK where_opt(Y) AS select(Z).

select ::= SELECT selcollist(W) from(X) where_opt(Y) orderby_opt(Z) limit_opt(L).

selcollist(A) ::= sclp(P) STAR.
selcollist(A) ::= sclp(P) nm(X)

sclp(A) ::= selcollist(X) COMMA. 
sclp(A) ::= .

where_opt(A) ::= .
where_opt(A) ::= WHERE expr(X).{A = X;}

from(A) ::= .                               
from(A) ::= FROM nm(A).

orderby_opt(A) ::= .                  
orderby_opt(A) ::= ORDER BY nm(X).

limit_opt(A) ::= .                    
limit_opt(A) ::= LIMIT expr(X).       

nm(A) ::= ID(X).   
nm(A) ::= STRING(X).  

expr(A) ::= expr(X) AND(OP) expr(Y).         
expr(A) ::= expr(X) OR(OP) expr(Y). 