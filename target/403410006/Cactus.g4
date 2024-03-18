grammar Cactus;

// Parser rules
token:(WS|COMMENT|ELSE|FI|IF|INT|MAIN|RETURN|WHILE|READ|WRITE|ID|INT_CONST|ADD|SUB|MUL|DIV|MOD|EQ|NEQ|GT|GTEQ|LESS|LESSEQ|AND|OR|NOT|ASSIGN|LEFT_PAR|RIGHT_PAR|LEFT_BRA|RIGHT_BRA|SEMI)*;

WS  : [ \t\r\n]+ -> skip ;
COMMENT : '/*'.*?'*/' -> channel(HIDDEN);

ID  : [A-Za-z_][A-Za-z0-9_]*;

ELSE    : 'else';
FI  : 'fi';
IF  : 'if';
INT : 'int';
MAIN    : 'main';
RETURN  : 'return';
WHILE   : 'while';
READ    : 'read';
WRITE   : 'write';

ADD : '+';
SUB : '-';
MUL : '*';
DIV : '/';
MOD : '%';
EQ  : '==';
NEQ : '!=';
GT  : '>';
GTEQ    : '>=';
LESS    : '<';
LESSEQ  : '<=';
AND : '&&';
OR  : '||';
NOT : '!';
ASSIGN  : '=';
LEFT_PAR    : '(';
RIGHT_PAR   : ')';
LEFT_BRA    : '{';
RIGHT_BRA   : '}';
SEMI    : ';';

INT_CONST   : [0-9]+;

