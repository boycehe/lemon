/*Page 108*/
struct lemon {
  struct state **sorted;  /*是有穷状态机的状态，而状态的刻画描述在LEMON中用的是state结构，
                            我们看到的是sorted是指针的指针，它可以理解一个指针数组，
                            准确的说，变量指向已排序好了的状态哈希数组*/
  struct rule *rule;      /*存储的是大家输入的各条文法规则或曰产生式，
                            他是指针，指向由许多rule结构实例作为节点而形成的一条链表的头部*/
  int nstate;             /*他存储此语法分析器的另一个结果，状态的数量*/
  int nrule;              /*语法文件中给定的产生式数目*/
  int nsymbol;            /*语法文件中给定的终结符与非终结符的数目*/
  int nterminal;          /*仅是终结符的数目*/
  struct symbol **symbols;/*存放的是有关符号的，也就是所有终结符和非终结符的相关内容。
                            这里的symbols变量，指向已排好了的符号好细数组*/
  int errorcnt;           /*存放已出错的数目*/
  struct symbol *errsym;  /*一个具有symbol结构的变量，它的作用是存放标识错误的符号
                            ，一般也就是error这个非终结符*/
  char *name;             /*由LEMON程序所自动生成的分析器名字--一般约定为Parse，
                            但根据处理需要，可变换为自己指定的不同名字*/
  char *arg;              /*存放的是aParse函数调用的第四个参数。它由%extra_argument特殊申明符专门指定*/
  char *tokentype;        /*进行语法分析时，终结符的所使用的结构数据类型。
                            它由%token_type这个特殊申明符来进行专门指定*/
  char *vartype;          /*是非终结符默认的类型，它由%default_type特殊申明符来为非终结符指定默认的统一数据类型*/
  char *start;            /*是语法文件指定从什么地方开始进行分析的哪个非终结符符号。
                            一般情况下，都是第一条产生式左边的哪个非终结符。但是，有时，为了分析的需要，
                            也可以在语法文件中，以%start_symbol特殊指定符指定某一个产生式左边的哪个非终结符作为语法分析的开始符号*/
  char *stacksize;        /*存放着语法分析堆栈的大小，既可搁置的符号数目，
                            也即语法分析堆栈中的元素。可由%stack_size指定*/
  char *include;          /*防止语法文件.y开始由%include特殊申明符指定的那些包含代码，
                            一般是一些include头文件，但也可以是数据定义，函数等*/
  int  includeln;         /*存放语法文件.y中%include特殊申明符指定的那些包含代码开始处的行号*/
  char *error;            /*存放着当输入了错误符号时才用于执行的代码，一般是一些纠错措施。
                            他由%syntax_error特殊申明符在语法在语法文件.y中指定*/
  int  errorln;           /*上述 error错误处理代码开始处的行号*/
  char *overflow;         /*是当语法分析栈在工作过程中,当发生了溢出时用于执行的代码。
                            它由%stack_overf1ow特殊申明符指定。*/
  int  overflowln;        /*上述处理堆栈溢出代码开始处的行号*/
  char *failure;          /*当语法分析失败时予以执行的代码。它由%parse_failure特殊申明符予以指定*/
  int  failureln;         /*是语法分析失败时执行代码的开始行号*/
  char *accept;           /*是当语法分析结束时于以接受时进行处理的代码。它由%parse_accept特殊申明符予以指定*/
  int  acceptln;          /*语法分析结束时处理予以接受的代码开始行号*/
  char *extracode;        /*是用于存放语法文件y中由号%code特殊申明符指定的C或C++代码块,
                            并把它们附加于整个语法分析器程序的后部,它一般包含了词法分析器( Tokenizer)、
                            输入输出部分,以及分析器中main主函数,等等。大家在计算器的设计中早已熟悉*/
  int  extracodeln;       /*上述附加代码开始处的行号*/
  char *tokendest;        /*是用于摧毁终结符的执行代码,一般而言是回收由终结符占用的内存资源。
                            它由 %token_destructor特殊申明符,指定“摧毁”非终结符并且释放由它占用的内存的那部分代码块,
                            也就是大家大家非常熟悉的所谓析构器*/
  int  tokendestln;       /*上述代码的开始行号*/
  char *vardest;          /*是默认用于摧毁非终结符的执行代码,
                            由%default_destructor特殊申明符指定一种统一的非终结符析构器作为默认的析构器*/
  int  vardestln;         /*上述非终结符析构器代码的开始行号*/
  char *filename;         /*输入的语法文件名,一般是具有后缀y的文件*/
  char *outname;          /*是生成的输出的语法分析器名称,默认的是c语言文件,
                            但也可以通过动一点“小手术,输出cpp文件。
                            如果有合适的配套模板文件(以后会提到的 lempar.c文件是其中的一  种),可以输出Java,C#等语言文件*/
  char *tokenprefix;      /*是在h头文件中为每一个记号前加上的前缀—几个字母,在语法文件y中 %token_prefix特殊申明符指定。*/
  int nconflict;          /*是在分析结束后,发现语法中有移进一归约和归约一归约的冲突总数量*/
  int tablesize;          /*是哈希表的大小*/
  int basisflag;          /*是当大家在命令行输入选项“b”时,表示需要打印输出核心项目(基本项目)而不是全部项目的标志*/
  int has_fallback;       /*存放的是语法文件中的一些特别申明了的符号,这些符号之所以特别,
                            是因为在当前的语法文件中,它们还并不是特殊符号,因而可以当成一般的标记符使用。
                            所以这些特殊符号“回滚”成了普通的标记符。比如,在 SQLite嵌人式数据库的编制中,有一些SQL92
                            标准的功能没有实现,说明有些特殊符号没有用上。在将来的改进中,
                            SQLite会一步一步地实现所有的SQL92功能,从而把所有的特殊符号都用完。
                            在目前阶段,就会有一些特殊符号被“降级”为一般的标识符。这些符号都放在 has_fa11back成员中*/
  char *argv0;            /*存放着本程序的名称“行不改姓,坐不改名”,仍 LEMON是也*/
};

//Page 112
struct s_x1 {

  int size;


  int count;
  struct s_x1node *tbl;
  struct s_x1node **ht;

};
s_x1 这个结构中的成员共4项，一是为可装置数据的数目size，这是容量大小。代码要求它大小必须大于1，且还得是2的指数。二是已放置了数据的数目count，
这标示实际已占用多少。三是为一个指向s_xlnode结构的指针，代码作者说明，需要放量的数据都放在此结构中。
四为同样的一个s_xlnode结构的指针的指针，它指向一张哈希表，或者是哈希数组，让人们在寻找数据时得以运用。

typedef struct s_x1node {

  char *data;
  struct s_x1node *next;
  struct s_x1node **from;

} x1node;

接着又定义了上面提到的s_x1node结构。s_x1node结构的成员是：首先的一个是放置字符串的data指针，然后是指向下一个本类数据结构实例的指针next，
以及指向上一个本类数据结构实例的指针的指from。
对于next指针的解释：对于占据相同hash（哈希）值的数据们，由它指向下个数据。而from的说明是：指内先前的链接，但是，注意到from的定义是指针的指针，
即它有两个星号，应该预期它不会是直接指向一个节点的指针，随着代码的展开，我们再来探索
并且，还定义了s_x1node结构的x1node变量。

//Page116

struct symbol {
  char *name;             /* 符号的字符串名字 */
  int index;              /*符号的索引号*/
  enum {
    TERMINAL,
    NONTERMINAL
  } type;                 /*指定此符号是终结符还是非终结符*/
  struct rule *rule;      /*如果这个结构里安装的符号是非终结符，
                            则它总要联系一个或几个产生式。这一个或儿个产生式，
                            就用一个链表来串接，而rule成员就是该链表的表首指针
                            */
  struct symbol *fallback;/*当这个符号是不必进行语法分析的符号时，表示它的“身份”是一 般的标识符。
                            这种性质的符号必须将它们“回退”成标识符。藏在此处是往回撤退到的那个符号的指针*/
  int prec;               /*如果对这个符号(-般是运算符)定义了优先级，则符号优先级的级别能用一个整数的数值来表示。
                            如果没有对这个符号定义优先级，则就干脆用- 1值*/
  enum e_assoc {
    LEFT,
    RIGHT,
    NONE,
    UNK
  } assoc;                /*如果定义了该符号 的优先级，也要定义该运算符的左结合性(LEFT)、
                            右结合性(RIGHT)不能结合性(NONE)和不知道(UNK)四种情况*/
  char *firstset;         /*在所有产生式中， 与这个符号有关的 First集合中的各个符号。
                            First集合中的各个符号应是终结符。*/
  Boolean lambda;         /*这是 一个逻辑符号。当为“真"时，说明这个非终结符右边的产生式可以是一个空串(只有非终结符才有此性质)。*/
  char *destructor;       /*此处存放着 些C代码。当此符号从语法分析栈中弹出时，则存放在此处的c代码将从事释放掉该符号所占用内存这样-一些扫尾工作。
                            它实际上存放着由语法文件.y中，该非终结符由%destructor特殊申明符所指定的那些C语言代码。
                            关于sdeatructor 特殊申明符的说明请见第18页*/
  int destructorln;       /*处装载的东西很简单，它“藏”的是语法文件y中标示destructor特殊申明符的那个行数*/
  char *datatype;         /*当这个符号为非终结符时,此处存放着非终结符的数据类型。在语法文件:y中由typ特殊申明符所指定。
                            比如上面的gelect非终结符，由%type指定的数据类型是solect*。在我们编写的计算器程序里，
                            因为所有的符号,包括终结符也包括非终结符，都是Token结构，所以在那里的语法文件.y里，
                            没有为任何非终结符另外指定新的数据类型*/

  int dtnum;              /*与此非终结符相关数据类型的代号。在语法分析器中，
                            所有参与语法分析的非终结符和终结符的数据类型，可能有许多种。
                            为了归并多种多样的数据类型，LEMON中用了一种手段，把所有的数据类型归并成一个联合( union)的数据结构。
                            而联合中的.yy%d元素就是与此非终结符相关的数据类型*/

};

//Page 115

struct s_x2 {
  int size;

  int count;
  struct s_x2node *tbl;
  struct s_x2node **ht;
};

typedef struct s_x2node {
  struct symbol *data;
  char *key;
  struct s_x2node *next;
  struct s_x2node **from;
} x2node;

//Page 119
struct s_x3 {
  int size;


  int count;
  struct s_x3node *tbl;
  struct s_x3node **ht;
};

typedef struct s_x3node {
  struct state *data;
  struct config *key;
  struct s_x3node *next;
  struct s_x3node **from;
} x3node;

//Page 209
struct s_x4 {
  int size;


  int count;
  struct s_x4node *tbl;
  struct s_x4node **ht;
};


typedef struct s_x4node {
  struct config *data;
  struct s_x4node *next;
  struct s_x4node **from;
} x4node;

struct plink {
  struct config *cfp;
  struct plink *next;
};

//Page 121

struct config {
  struct rule *rp;        /*就是产生式,是为此项目的“真身”,所有的项目都它的“化身”*/
  int dot;                /*用它可把一个项目拦腰分为两段——已经进分析栈的部分与尚留在分析栈之外的部分。
                            一般在教科书中,两者之间的分界符是点(·)或星号(*),
                            但在此结构中,用了一个整型的数值dot来表示。
                            它的数值即为已进栈了的符号数量所以也就代表了当前处理符号的位置*/
  char *fws;              /*项目结构还含有一个 Follow集,集中放有这个项目所具有的可以立即跟随的所有终结符*/
  struct plink *fplp;     /*是一个链表的头部指针,指向 Follow集顺向传播项目*/
  struct plink *bplp;     /*也是一个链表的头部指针,指向 Follow集逆向传播项目*/
  struct state *stp;      /*是一个指向包含着此项目的状态指针。通过这个变量,我们可以从项目“倒退”回包含它的状态中去*/
  enum {
    COMPLETE,
    INCOMPLETE
  } status;             /* 是一个状态变量，用于指示处理Follow集的过程是否结束。
                           如果还没有结束,则为INCOMPLETE，如果已经解除，则为COMPLETE另外,它也作为计算移进的指示标志next,
                           是一个指针,指向在同一个状态中那条所有项目链表中的下一个项目*/
  struct config *next;    /*是一个指针,指向在同一个状态中那条所有项目链表中的下一个项目*/
  struct config *bp;      /*也是一个指针,指向在同一个状态中那条基本项目链表中的下一个项目*/
};

//Page 122
struct rule {
  struct symbol *lhs;     /*它是 symbo1结构的一个实例指针,它指向本产生式定义符(::=)左边的那个符号。
                            大家知道,产生式左边字符肯定是一个非终结符*/
  char *lhsalias;         /*是一字符串,表示上述lhs符号(产生式左边非终结符)的别名。
                            如果没有别名,  则它就是空指针。
                            所谓的别名,就是下列语法产生式中由圆括号括起来的A,B和C。像MIMUS
                            就没有别名,但是这里的lhsalias专门用于产生式左边的那个非终结符。
                            对于下面的产生式,它就是左边expx的别名A。
                            expr(A) ::= expr(B) MINUS expr(C)。{A = B - C}*/
  int ruleline;           /*一本产生式在所有产生式中排序的序号*/
  int nrhs;               /*产生式右边所有符号的总数,既包括终结符,也包括非终结符*/
  struct symbol **rhs;    /*产生式定义符右边的所有符号。从形式上看,它是指针的指针,即一个指针数组
                            。指针数组的每一个元素都指向一个symbo1类型的元素*/
  char **rhsalias;        /*也是一个指针数组,其元素是指向字符串的指针它的内容是产生式右边各个符号的别名。如果某个符号没有别名,则它为空指针。*/
  int line;               /*在.y语法文件中,这个产生式最右端的C动作代码开始处的行号*/
  char *code;             /*当此产生式进行归约时,相应应该执行的C动作代码放于此处*/
  struct symbol *precsym; /*在产生式中具有左结合、右结合等优先性质的那个符号*/
  int index;              /*此产生式的索引号*/
  Boolean canReduce;      /*表示此产生式可否被归约的状态变量*/
  struct rule *nextlhs;   /*是一个ru1e链表的指针,指向具有同一左边非终结符的下一个产生式*/
  struct rule *next;      /*也是一个xule链表的指针,指向由所有产生式组成的链表的下一个产生式*/
};

//Page 123
struct action {
  struct symbol *sp;    /*这是LALR(1)语法分析器在采取各种动作前,要求先行搜索的,
                          或者是先“张”一眼的那个正等待处理的栈外符号。*/
  enum e_action {
    SHIFT,
    ACCEPT,
    REDUCE,
    ERROR,
    CONFLICT,
    SH_RESOLVED,
    RD_RESOLVED,
    NOT_USED
  } type;               /*这是一个枚举变量,由它对整个语法分析器可执行动作进行分类:SHFT--移进,
                          可把先“张”一眼的那个先行符号(look-ahead- symbol)移进到语法分析栈中
                          ACCEPT—接受,表示整个语法文件.y的内容均分析完成,并且无错误。
                          REDUCE--归约,表示已到达产生式末尾,可对此产生式进行归约。
                          ERROR-出错，表示正在处理的语法符号无法正确解读。 CONFLICT-—在进行归约时,有一些冲突。
                          SH_RESOLVEDRESOLVED--表示已用优先级解决了归约冲突。NOT_USD--由于无用,在压缩时将被删除。*/
  union {
    struct state *stp;
    struct rule *rp;
  } x;                  /*是两个结构变量的联合。如果这个动作是移进(shift)的话，则联合取状态(state),
                          这个状态是指移进语法符号后,将进入的新状态；
                          如果这个动作是归约的话,则联合取产生式(rule),
                          这个产生式是归约所用的那个产生式*/
  struct action *next;  /*是指位于同一状态中的下一个动作*/
  struct action *collide;/*是具有相同哈希码值的下一个动作*/
};

//Page 120
struct state {
  struct config *bp;      /*指向由config结构对象组成链表的链首。config是产生式的变形--在产生式右部的某处加点
                            (LEMON在.out文件中用星号(*)代替了黑点(·))项目。而bp指向链表中所有的项目,
                            都是这个状态中的基本项目,也即核心项目*/
  struct config *cfp;      /*也是指向由config结构对象组成链表的链首。
                             只是它所指向链表中的元素是此状态的所有项目，既包括了bp链表中的基本项目,
                             也包括可由基本项目通过闭包运算得出的其他项目*/
  int index;               /*此状态的索引号,也就是此状态的序号*/
  struct action *ap;       /*action结构的变量。
                             它是在此状态中,所有相关动作合并在一起的一个数组。
                             所谓的动作,就是移进、归约、接受和出错四种*/
  int nTknAct, nNtAct;     /*与动作有关的终结符符号的数量。与动作相关的非终结符符号的数量*/
  int iTknOfst, iNtOfst;   /*在将来计算生成的yy_action[]数组中,终结符位置的偏移值。 在yy_action数组中,非终结符的位置偏移值*/
  int iDflt;               /*在此状态中默认的动作*/
};


//Page 143
struct pstate {
  char *filename;      /*不用说,该成员变量中必须储存着被输入的语法文件.y的名字*/
  int tokenlineno;     /*当前正在分析符号(记号)所在位置的行号*/
  int errorcnt;        /*分析过程中已经出错的数量*/
  char *tokenstart;    /*当前字符串形式的符号名字*/
  struct lemon *gp;    /* lemon结构类型的全局变量，他也是被带进此Parse()函数的唯一参数*/
  enum e_state {
    INITIALIZE,         /*顾名思义,标志词法分析的初始状态*/
    WAITING_FOR_DECL_OR_RULE,/*等待着输入产生式或特殊申明符的状态*/
    WAITING_FOR_DECL_KEYWORD,/*等待着输入特殊申明符的状态。*/
    WAITING_FOR_DECL_ARG,/*等待着输入由特殊申明符指定的由大括号围起来参数的状态*/
    WAITING_FOR_PRECEDENCE_SYMBOL,/*等待着输人优先符的状态*/
    WAITING_FOR_ARROW,/*等待着输人产生式的定义符(即::=)*/
    IN_RHS,/*标示着当前正处子分析产生式的右方状态*/
    LHS_ALIAS_1,/*标示当前时状念正在左边文法符号后的左小括号“("后,正等待输人该文法符号的别名*/
    LHS_ALIAS_2,/*标示当前的状态是已经读入左边文法符号的别名,正等输入右小括号“)”*/
    LHS_ALIAS_3,/*标示当前状态是已经读入左边文法符号别名后的右小括号“)”,等待着产生式的定义符号“::=”*/
    RHS_ALIAS_1,/*标示当前的状态正在石边文法符号后的左小括号“(”后,正等待输人该文法符号的别名*/
    RHS_ALIAS_2,/*标示当前的状态是已经读人右边文法符号的别名,正等输人右小括号“)”*/
    PRECEDENCE_MARK_1,/*标示当前的状态是读到“伪”终结符前的“[”符号。*/
    PRECEDENCE_MARK_2,/*标示当前的状态是读到“伪”终结符后的“]”符号*/
    RESYNC_AFTER_RULE_ERROR,/*标示当前产生式出错的状态*/
    RESYNC_AFTER_DECL_ERROR,/*标示由当前特殊申明符后的参数出错状态*/
    WAITING_FOR_DESTRUCTOR_SYMBOL,/*等待着用于输入“摧毁”符号的析构器代码状态*/
    WAITING_FOR_DATATYPE_SYMBOL,/*等待着输入数据类型符号状态*/
    WAITING_FOR_FALLBACK_ID/*等待着输人回滚标志的状态*/
  } state;                  /*为枚举变量。它的枚举值分别是词法分析中会用到的各种各样的状态。
                              枚举变量的全体组成了词法分析中的有穷状态集合*/
  struct symbol *fallback;  /*用于放置将回滚的记号**/
  struct symbol *lhs;       /*当前产生式的左边文法符号,是一非终结符**/
  char *lhsalias;           /*当前产生式左边非终结符的别名*/
  int nrhs;                 /*到目前为止“看”到产生式右边文法符号的数量**/
  struct symbol *rhs[MAXRHS];/*存储产生式右边所有文法符号的数组*/
  char *alias[MAXRHS];      /*存储产生式右边所有文法符号别名的数组(但有些文法符号可能没有别名)*/
  struct rule *prevrule;    /*存放已经分析过的产生式*/
  char *declkeyword;        /*申明用的特殊申明符*/
  char **declargslot;       /*用于放置申明参数的字符串数组*/
  int *decllnslot;          /*放置申明参数的行号*/
  enum e_assoc declassoc;   /*是枚举e_assoc类型变量,它用于指定某一符号的左结合、右结合等优先级类型其e_assoc枚举的定义见第116页的symbo1*/
  int preccounter;          /*存放某一符号的优先数*/
  struct rule *firstrule;   /*指向语法文件中的第一条产生式*/
  struct rule *lastrule;    /*指向到目前为止刚刚分析过的那条产生式*/
};
