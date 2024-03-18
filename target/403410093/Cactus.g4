// The grammar for Cactus language
grammar Cactus;
// Parser rules
token : (NUM|ELSE |FI|IF|INT|MAIN|RETURN|WHILE|READ|WRITE|ID|Fat1|Fat2|Fat3|Fat4|Fat5|Fat6|Fat7|Fat8|Fat9|Fat10|Fat11|Fat12|Fat13|Fat14|Fat15|Fat16|Fat17|Fat18|Fat19|Fat20)*;
ELSE : 'else';
FI : 'fi';
IF : 'if';
INT : 'int';
MAIN : 'main';
RETURN : 'return';
WHILE : 'while';
READ : 'read';
WRITE : 'write';
NUM :([0-9])+;
ID:([a-zA-Z]|[_])([a-zA-Z]|[_]|[0-9])*;
Fat1 :'+';
Fat2 :'-';
Fat3 :'*';
Fat4 :'/';
Fat5 :'%';
Fat6 :'==';
Fat7 :'!=';
Fat8 :'>';
Fat9 :'>=';
Fat10 :'<';
Fat11 :'<=';
Fat12 :'&&';
Fat13 :'||';
Fat14 :'!';
Fat15 :'=';
Fat16 :'(';
Fat17 :')';
Fat18 :'{';
Fat19 :'}';
Fat20 :';';
COMMENT : '/*' .*? '*/' -> skip ;
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines