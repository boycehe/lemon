/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 1 "calculator.y"

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

#line 56 "calculator.cpp"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 20
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE  Token 
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  Token yy30;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE             26
#define YYNRULE              16
#define YY_MAX_SHIFT         25
#define YY_MIN_SHIFTREDUCE   32
#define YY_MAX_SHIFTREDUCE   47
#define YY_MIN_REDUCE        48
#define YY_MAX_REDUCE        63
#define YY_ERROR_ACTION      64
#define YY_ACCEPT_ACTION     65
#define YY_NO_ACTION         66
/************* End control #defines *******************************************/

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE

**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (56)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */     9,   10,    7,    8,    6,    9,   10,    7,    8,    6,
 /*    10 */    46,   48,    2,    5,    5,   47,   65,    1,   33,   19,
 /*    20 */    20,    4,    4,   45,   45,    9,   10,    7,    8,    6,
 /*    30 */     9,   10,    7,    8,    6,   44,    7,    8,    6,   25,
 /*    40 */    15,   11,    3,   13,   12,   14,   21,    6,   22,   23,
 /*    50 */     3,   35,   24,   17,   18,   16,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,    3,    4,    5,    1,    2,    3,    4,    5,
 /*    10 */    11,    0,   13,    2,    2,   11,   15,   16,    7,    8,
 /*    20 */     8,   10,   10,   12,   12,    1,    2,    3,    4,    5,
 /*    30 */     1,    2,    3,    4,    5,   11,    3,    4,    5,   17,
 /*    40 */    18,    9,   10,   18,   18,   18,   18,    5,   18,   18,
 /*    50 */    10,    7,   18,   18,   18,   18,
};
#define YY_SHIFT_USE_DFLT (-2)
#define YY_SHIFT_COUNT (25)
#define YY_SHIFT_MIN   (-1)
#define YY_SHIFT_MAX   (44)
static const signed char yy_shift_ofst[] = {
 /*     0 */    -2,   11,   12,   12,   12,   12,   12,   12,   12,   12,
 /*    10 */    12,   12,   -1,    4,   24,   29,   29,   33,   33,   32,
 /*    20 */    40,   42,   42,   42,   42,   44,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (11)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (37)
static const signed char yy_reduce_ofst[] = {
 /*     0 */     1,   22,   25,   26,   27,   28,   30,   31,   34,   35,
 /*    10 */    36,   37,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    50,   64,   64,   64,   64,   64,   64,   64,   64,   64,
 /*    10 */    64,   64,   64,   64,   64,   53,   52,   55,   54,   64,
 /*    20 */    64,   59,   58,   57,   56,   64,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "PLUS",          "MINUS",         "DIVIDE",      
  "TIMES",         "POW",           "NOT",           "NEWLINE",     
  "NAME",          "EQ",            "LP",            "RP",          
  "NUM",           "COMMA",         "error",         "main",        
  "in",            "program",       "expr",        
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "main ::= in",
 /*   1 */ "in ::= in NEWLINE",
 /*   2 */ "in ::=",
 /*   3 */ "in ::= in program NEWLINE",
 /*   4 */ "program ::= NAME EQ expr",
 /*   5 */ "program ::= expr",
 /*   6 */ "expr ::= expr MINUS expr",
 /*   7 */ "expr ::= expr PLUS expr",
 /*   8 */ "expr ::= expr TIMES expr",
 /*   9 */ "expr ::= expr DIVIDE expr",
 /*  10 */ "expr ::= expr POW expr",
 /*  11 */ "expr ::= MINUS expr",
 /*  12 */ "expr ::= LP expr RP",
 /*  13 */ "expr ::= NUM",
 /*  14 */ "expr ::= NAME LP expr RP",
 /*  15 */ "expr ::= NAME LP expr COMMA expr RP",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
      /* TERMINAL Destructor */
    case 1: /* PLUS */
    case 2: /* MINUS */
    case 3: /* DIVIDE */
    case 4: /* TIMES */
    case 5: /* POW */
    case 6: /* NOT */
    case 7: /* NEWLINE */
    case 8: /* NAME */
    case 9: /* EQ */
    case 10: /* LP */
    case 11: /* RP */
    case 12: /* NUM */
    case 13: /* COMMA */
{
#line 32 "calculator.y"
 token_destructor((yypminor->yy0)); 
#line 486 "calculator.cpp"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yyidx>=0 );
  yytos = &pParser->yystack[pParser->yyidx--];
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
#ifndef YYPARSEFREENEVERNULL
  if( pParser==0 ) return;
#endif
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    if( i==YY_SHIFT_USE_DFLT ) return yy_default[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
      if( iLookAhead>0 ){
#ifdef YYFALLBACK
        YYCODETYPE iFallback;            /* Fallback token */
        if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
               && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
          }
#endif
          assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
          iLookAhead = iFallback;
          continue;
        }
#endif
#ifdef YYWILDCARD
        {
          int j = i - iLookAhead + YYWILDCARD;
          if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
            j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
            j<YY_ACTTAB_COUNT &&
#endif
            yy_lookahead[j]==YYWILDCARD
          ){
#ifndef NDEBUG
            if( yyTraceFILE ){
              fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
                 yyTracePrompt, yyTokenName[iLookAhead],
                 yyTokenName[YYWILDCARD]);
            }
#endif /* NDEBUG */
            return yy_action[j];
          }
        }
#endif /* YYWILDCARD */
      }
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yystack[yypParser->yyidx].major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yystack[yypParser->yyidx].major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 15, 1 },
  { 16, 2 },
  { 16, 0 },
  { 16, 3 },
  { 17, 3 },
  { 17, 1 },
  { 18, 3 },
  { 18, 3 },
  { 18, 3 },
  { 18, 3 },
  { 18, 3 },
  { 18, 2 },
  { 18, 3 },
  { 18, 1 },
  { 18, 4 },
  { 18, 6 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */
  yygotominor = yyzerominor;

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
      case 1: /* in ::= in NEWLINE */
      case 3: /* in ::= in program NEWLINE */ yytestcase(yyruleno==3);
#line 47 "calculator.y"
{
  yy_destructor(yypParser,7,&yymsp[0].minor);
}
#line 788 "calculator.cpp"
        break;
      case 4: /* program ::= NAME EQ expr */
#line 52 "calculator.y"
{
	if(yymsp[-2].minor.yy0.symt->funcptr || yymsp[-2].minor.yy0.symt->funcptr2)
	{
		cout << yymsp[-2].minor.yy0.symt->name<<"is a function! Must type in rightside!\n"<<endl;
		yymsp[-2].minor.yy0.symt->value = 0.0;
	}else{
		yymsp[-2].minor.yy0.symt->value = yymsp[0].minor.yy30.value;
	}
  yy_destructor(yypParser,9,&yymsp[-1].minor);
}
#line 802 "calculator.cpp"
        break;
      case 5: /* program ::= expr */
#line 62 "calculator.y"
{cout << "= " << yymsp[0].minor.yy30.value - C.value ;}
#line 807 "calculator.cpp"
        break;
      case 6: /* expr ::= expr MINUS expr */
#line 64 "calculator.y"
{yygotominor.yy30.value = yymsp[-2].minor.yy30.value + yymsp[0].minor.yy30.value;  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 813 "calculator.cpp"
        break;
      case 7: /* expr ::= expr PLUS expr */
#line 66 "calculator.y"
{yygotominor.yy30.value = yymsp[-2].minor.yy30.value + yymsp[0].minor.yy30.value;  yy_destructor(yypParser,1,&yymsp[-1].minor);
}
#line 819 "calculator.cpp"
        break;
      case 8: /* expr ::= expr TIMES expr */
#line 68 "calculator.y"
{yygotominor.yy30.value = yymsp[-2].minor.yy30.value * yymsp[0].minor.yy30.value;  yy_destructor(yypParser,4,&yymsp[-1].minor);
}
#line 825 "calculator.cpp"
        break;
      case 9: /* expr ::= expr DIVIDE expr */
#line 71 "calculator.y"
{
    if(yymsp[0].minor.yy30.value != 0)
    {
     yygotominor.yy30.value = yymsp[-2].minor.yy30.value / yymsp[0].minor.yy30.value;
    }else{
        cout << "divide by zero\n" <<endl;
        exit(1);
    }
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 839 "calculator.cpp"
        break;
      case 10: /* expr ::= expr POW expr */
#line 81 "calculator.y"
{yygotominor.yy30.value = pow(yymsp[-2].minor.yy30.value,yymsp[0].minor.yy30.value);  yy_destructor(yypParser,5,&yymsp[-1].minor);
}
#line 845 "calculator.cpp"
        break;
      case 11: /* expr ::= MINUS expr */
#line 83 "calculator.y"
{yygotominor.yy30.value = -yymsp[0].minor.yy30.value;  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 851 "calculator.cpp"
        break;
      case 12: /* expr ::= LP expr RP */
#line 85 "calculator.y"
{yygotominor.yy30.value = yymsp[-1].minor.yy30.value;  yy_destructor(yypParser,10,&yymsp[-2].minor);
  yy_destructor(yypParser,11,&yymsp[0].minor);
}
#line 858 "calculator.cpp"
        break;
      case 13: /* expr ::= NUM */
#line 88 "calculator.y"
{
                if(yymsp[0].minor.yy0.symt->funcptr || yymsp[0].minor.yy0.symt->funcptr2)
                {
                    cout<< yymsp[0].minor.yy0.symt->name<<" is a function! Must type like "<<yymsp[0].minor.yy0.symt->name<< " ( number )!"<<endl;
                    yygotominor.yy30.value = 0.0;
                }else{
                    yygotominor.yy30.value = yymsp[0].minor.yy0.symt->value;
                }
        }
#line 871 "calculator.cpp"
        break;
      case 14: /* expr ::= NAME LP expr RP */
#line 98 "calculator.y"
{
            if(yymsp[-3].minor.yy0.symt->funcptr)
            {
                yygotominor.yy30.value = (yymsp[-3].minor.yy0.symt->funcptr) (yymsp[-1].minor.yy30.value);
            }else{
                cout << yymsp[-3].minor.yy0.symt->name << " function undifined!";
                exit(1);
            }
          yy_destructor(yypParser,10,&yymsp[-2].minor);
  yy_destructor(yypParser,11,&yymsp[0].minor);
}
#line 886 "calculator.cpp"
        break;
      case 15: /* expr ::= NAME LP expr COMMA expr RP */
#line 108 "calculator.y"
{
                if(yymsp[-5].minor.yy0.symt->funcptr2)
                {
                    yygotominor.yy30.value = (yymsp[-5].minor.yy0.symt->funcptr2) (yymsp[-3].minor.yy30.value,yymsp[-1].minor.yy30.value);
                }else{
                    cout << yymsp[-5].minor.yy0.symt->name<<" function undifined! "<<endl;
                    yygotominor.yy30.value = yymsp[-5].minor.yy0.symt->value;
                }
              yy_destructor(yypParser,10,&yymsp[-4].minor);
  yy_destructor(yypParser,13,&yymsp[-2].minor);
  yy_destructor(yypParser,11,&yymsp[0].minor);
}
#line 902 "calculator.cpp"
        break;
      default:
      /* (0) main ::= in */ yytestcase(yyruleno==0);
      /* (2) in ::= */ yytestcase(yyruleno==2);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno>=0 && yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ) yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    /* If the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
      yyTraceShift(yypParser, yyact);
    }else{
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
/************ Begin %syntax_error code ****************************************/
#line 41 "calculator.y"

	cout<< "Syntax error!\n"<<endl;
	exit(1);
#line 974 "calculator.cpp"
/************ End %syntax_error code ******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
#line 37 "calculator.y"

	printf("parsing complete!\n");
#line 998 "calculator.cpp"
/*********** End %parse_accept code *******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sInitialize. Empty stack. State 0\n",
              yyTracePrompt);
    }
#endif
  }
  yyminorunion.yy0 = yyminor;
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      if( yyact > YY_MAX_SHIFT ) yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
#ifndef NDEBUG
  if( yyTraceFILE ){
    int i;
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE,"%c%s", i==1 ? '[' : ' ', 
              yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
#line 117 "calculator.y"


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

#line 1437 "calculator.cpp"
