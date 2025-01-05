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

program: (
		globalDeclaration
		| functionDeclaration
		| structDeclaration
		| statement
	)* EOF;

statement:
	globalDeclaration
	| declaration
	| assignment
	| expressionStatement
	| ifStatement
	| whileStatement
	| forStatement
	| returnStatement
	| functionCall;

GLOBAL: 'global';

globalDeclaration: GLOBAL type ID ASSIGN NUMERIC SEMICOLON;

declaration:
	type ID ASSIGN expression SEMICOLON
	| type ID SEMICOLON
	| type ID LPAREN parameterList? RPAREN block;

// Structura declarată în MiniLang
structDeclaration: 'struct' ID LBRACE structMember* structEnd;

// Membru al structurii: câmpuri și constructori
structMember:
	type ID SEMICOLON // câmpuri de tipul structurilor
	| functionDeclaration // declararea funcțiilor pentru structuri
	| constructorDeclaration // constructorul structurii
	| destructorDeclaration // destructorul structurii
	| assignment; // atribuiri

// Constructorul structurii
constructorDeclaration:
	'constructor' LPAREN parameterList? RPAREN block;

// Destructorul structurii
destructorDeclaration: 'destructor' LPAREN RPAREN block;

// Finalul structurii
structEnd: '}' SEMICOLON;

functionDeclaration: type ID LPAREN parameterList? RPAREN block;

block: LBRACE statement* RBRACE;

parameterList: parameter (COMMA parameter)*;

parameter: type ID;

functionCall: ID LPAREN expressionList? RPAREN SEMICOLON;

assignment:
	ID ASSIGN expression SEMICOLON
	| ID PLUS_ASSIGN expression SEMICOLON
	| ID MINUS_ASSIGN expression SEMICOLON
	| ID MULT_ASSIGN expression SEMICOLON
	| ID DIV_ASSIGN expression SEMICOLON
	| ID '=' expression ';';

expressionStatement: expression SEMICOLON;

ifStatement: IF LPAREN expression RPAREN block (ELSE block)?;

whileStatement: WHILE LPAREN expression RPAREN block;

forStatement:
	FOR LPAREN forInit expression SEMICOLON expression RPAREN block;

forInit: declaration | assignment;

returnStatement: RETURN expression SEMICOLON;

expression:
	term (binaryOp term)*
	| functionCall
	| INT
	| ID
	| expression ('+' | '-' | '*' | '/') expression;

term: factor (multiplicativeOp factor)*;

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

INCREMENT: '++';
DECREMENT: '--';