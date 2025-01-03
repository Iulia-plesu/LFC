grammar MiniLang;

INT: 'int';
FLOAT: 'float';
STRING: 'string';
VOID: 'void';
DOUBLE: 'double';

IF: 'if';
ELSE: 'else';
FOR: 'for';
WHILE: 'while';
RETURN: 'return';

ID: [a-zA-Z_][a-zA-Z0-9_]*;

NUMERIC: [0-9]+ ('.' [0-9]+)?;

STRING_LITERAL: '"' (~('\\' | '"'))* '"';

PLUS: '+';
MINUS: '-';
MULT: '*';
DIV: '/';
EQ: '==';
NEQ: '!=';
LT: '<';
LTE: '<=';
GT: '>';
GTE: '>=';
AND: '&&';
OR: '||';
NOT: '!';
ASSIGN: '=';
PLUS_ASSIGN: '+=';
MINUS_ASSIGN: '-=';
MULT_ASSIGN: '*=';
DIV_ASSIGN: '/=';

LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
COMMA: ',';
SEMICOLON: ';';
WHITESPACE: [ \t\r\n]+ -> skip;
COMMENT: '/*' .*? '*/' -> skip;
LINE_COMMENT: '//' ~[\r\n]* -> skip;

program: statement*;

statement:
	globalDeclaration
	| declaration
	| structDeclaration
	| assignment
	| expressionStatement
	| ifStatement
	| whileStatement
	| forStatement
	| returnStatement;

declaration:
	type ID LPAREN parameterList? RPAREN block
	| type ID ASSIGN expression SEMICOLON;

globalDeclaration: type ID ASSIGN NUMERIC SEMICOLON;

structDeclaration:
	'struct' ID LBRACE structMember* RBRACE SEMICOLON {
        // Aici validăm structura, putem colecta membrii și funcțiile
        // Dacă este necesar, putem valida constructorii sau destructori în această secțiune
    };

structMember:
	type ID SEMICOLON
	| functionDeclaration
	| constructorDeclaration
	| destructorDeclaration;

constructorDeclaration:
	'constructor' LPAREN parameterList? RPAREN block;

destructorDeclaration: 'destructor' LPAREN RPAREN block;

functionDeclaration: type ID LPAREN parameterList? RPAREN block;

parameterList: parameter (COMMA parameter)*;

parameter: type ID;

block: LBRACE statement+ RBRACE;

assignment:
	ID ASSIGN expression SEMICOLON
	| ID PLUS_ASSIGN expression SEMICOLON
	| ID MINUS_ASSIGN expression SEMICOLON
	| ID MULT_ASSIGN expression SEMICOLON
	| ID DIV_ASSIGN expression SEMICOLON;

expressionStatement: expression SEMICOLON;

ifStatement: IF LPAREN expression RPAREN block (ELSE block)?;

whileStatement: WHILE LPAREN expression RPAREN block;

forStatement:
	FOR LPAREN forInit expression SEMICOLON expression RPAREN block;

forInit: declaration | assignment;

returnStatement: RETURN expression SEMICOLON;

expression: term (binaryOp term)*;

term: factor (multiplicativeOp factor)*;

INCREMENT: '++';
DECREMENT: '--';

factor:
	ID
	| NUMERIC
	| STRING_LITERAL
	| LPAREN expression RPAREN
	| ID LPAREN expressionList? RPAREN
	| INCREMENT ID
	| DECREMENT ID
	| ID INCREMENT
	| ID DECREMENT;

binaryOp:
	PLUS
	| MINUS
	| EQ
	| NEQ
	| LT
	| LTE
	| GT
	| GTE
	| AND
	| OR;

multiplicativeOp: MULT | DIV;

expressionList: expression (COMMA expression)*;

type: INT | FLOAT | STRING | VOID | DOUBLE;