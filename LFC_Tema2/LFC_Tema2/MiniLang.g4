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

ID: [a-zA-Z_][a-zA-Z0-9_]*; // Identifiers

NUMERIC: [0-9]+ ('.' [0-9]+)?; // Numbers (integer or float)

STRING_LITERAL: '"' (~('\\' | '"'))* '"'; // String literals

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
WHITESPACE: [ \t\r\n]+ -> skip; // Skip whitespace
COMMENT: '/*' .*? '*/' -> skip; // Block comments
LINE_COMMENT: '//' ~[\r\n]* -> skip; // Line comments

// Program rules
program: statement*;

// Statement rules
statement:
	globalDeclaration
	| declaration
	| assignment
	| expressionStatement
	| ifStatement
	| whileStatement
	| forStatement
	| returnStatement;

// Global variable declaration
globalDeclaration:
	type ID ASSIGN NUMERIC SEMICOLON; // Global variable declaration

// Function declaration
declaration:
	type ID LPAREN parameterList? RPAREN block // Function with parameters and block
	| type ID ASSIGN expression SEMICOLON; // Variable declaration with assignment

parameterList:
	parameter (COMMA parameter)*; // List of parameters

parameter: type ID; // Parameter definition

block: LBRACE statement+ RBRACE; // Code block enclosed by braces

// Assignment rule
assignment:
	ID ASSIGN expression SEMICOLON
	| ID PLUS_ASSIGN expression SEMICOLON
	| ID MINUS_ASSIGN expression SEMICOLON
	| ID MULT_ASSIGN expression SEMICOLON
	| ID DIV_ASSIGN expression SEMICOLON;

// Expression statement
expressionStatement: expression SEMICOLON;

// If statement
ifStatement:
	IF LPAREN expression RPAREN block (ELSE block)?; // If with optional else

// While loop
whileStatement: WHILE LPAREN expression RPAREN block;

// For loop
forStatement:
	FOR LPAREN forInit expression SEMICOLON expression RPAREN block;
// For loop with initialization, condition, increment

// For loop initialization
forInit:
	declaration
	| assignment; // Handle variable declarations and assignments in for loop

// Return statement
returnStatement: RETURN expression SEMICOLON;

// Expression rules
expression:
	term (binaryOp term)*; // allows binary operators like '+' and '-' between terms

term:
	factor (multiplicativeOp factor)*; // Handle multiplicative expressions

// Unary operators
INCREMENT: '++';
DECREMENT: '--';

factor:
	ID
	| NUMERIC
	| STRING_LITERAL
	| LPAREN expression RPAREN
	| ID LPAREN expressionList? RPAREN // Function calls
	| INCREMENT ID // Prefix increment
	| DECREMENT ID // Prefix decrement
	| ID INCREMENT // Postfix increment
	| ID DECREMENT; // Postfix decrement

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

expressionList:
	expression (COMMA expression)*; // List of expressions for function calls

// Type rules
type: INT | FLOAT | STRING | VOID | DOUBLE;