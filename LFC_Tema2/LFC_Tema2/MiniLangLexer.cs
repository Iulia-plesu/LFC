//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     ANTLR Version: 4.13.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from c:/Users/Plesu/Documents/LFC/LFC_Tema2/LFC_Tema2/MiniLang.g4 by ANTLR 4.13.1

// Unreachable code detected
#pragma warning disable 0162
// The variable '...' is assigned but its value is never used
#pragma warning disable 0219
// Missing XML comment for publicly visible type or member '...'
#pragma warning disable 1591
// Ambiguous reference in cref attribute
#pragma warning disable 419

using System;
using System.IO;
using System.Text;
using Antlr4.Runtime;
using Antlr4.Runtime.Atn;
using Antlr4.Runtime.Misc;
using DFA = Antlr4.Runtime.Dfa.DFA;

[System.CodeDom.Compiler.GeneratedCode("ANTLR", "4.13.1")]
[System.CLSCompliant(false)]
public partial class MiniLangLexer : Lexer {
	protected static DFA[] decisionToDFA;
	protected static PredictionContextCache sharedContextCache = new PredictionContextCache();
	public const int
		T__0=1, T__1=2, T__2=3, INT=4, FLOAT=5, STRING=6, VOID=7, DOUBLE=8, IF=9, 
		ELSE=10, FOR=11, WHILE=12, RETURN=13, ID=14, NUMERIC=15, STRING_LITERAL=16, 
		PLUS=17, MINUS=18, MULT=19, DIV=20, EQ=21, NEQ=22, LT=23, LTE=24, GT=25, 
		GTE=26, AND=27, OR=28, NOT=29, ASSIGN=30, PLUS_ASSIGN=31, MINUS_ASSIGN=32, 
		MULT_ASSIGN=33, DIV_ASSIGN=34, LPAREN=35, RPAREN=36, LBRACE=37, RBRACE=38, 
		COMMA=39, SEMICOLON=40, WHITESPACE=41, COMMENT=42, LINE_COMMENT=43, GLOBAL=44, 
		INCREMENT=45, DECREMENT=46;
	public static string[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static string[] modeNames = {
		"DEFAULT_MODE"
	};

	public static readonly string[] ruleNames = {
		"T__0", "T__1", "T__2", "INT", "FLOAT", "STRING", "VOID", "DOUBLE", "IF", 
		"ELSE", "FOR", "WHILE", "RETURN", "ID", "NUMERIC", "STRING_LITERAL", "PLUS", 
		"MINUS", "MULT", "DIV", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "AND", 
		"OR", "NOT", "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN", "MULT_ASSIGN", "DIV_ASSIGN", 
		"LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "SEMICOLON", "WHITESPACE", 
		"COMMENT", "LINE_COMMENT", "GLOBAL", "INCREMENT", "DECREMENT"
	};


	public MiniLangLexer(ICharStream input)
	: this(input, Console.Out, Console.Error) { }

	public MiniLangLexer(ICharStream input, TextWriter output, TextWriter errorOutput)
	: base(input, output, errorOutput)
	{
		Interpreter = new LexerATNSimulator(this, _ATN, decisionToDFA, sharedContextCache);
	}

	private static readonly string[] _LiteralNames = {
		null, "'struct'", "'constructor'", "'destructor'", "'int'", "'float'", 
		"'string'", "'void'", "'double'", "'if'", "'else'", "'for'", "'while'", 
		"'return'", null, null, null, "'+'", "'-'", "'*'", "'/'", "'=='", "'!='", 
		"'<'", "'<='", "'>'", "'>='", "'&&'", "'||'", "'!'", "'='", "'+='", "'-='", 
		"'*='", "'/='", "'('", "')'", "'{'", "'}'", "','", "';'", null, null, 
		null, "'global'", "'++'", "'--'"
	};
	private static readonly string[] _SymbolicNames = {
		null, null, null, null, "INT", "FLOAT", "STRING", "VOID", "DOUBLE", "IF", 
		"ELSE", "FOR", "WHILE", "RETURN", "ID", "NUMERIC", "STRING_LITERAL", "PLUS", 
		"MINUS", "MULT", "DIV", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "AND", 
		"OR", "NOT", "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN", "MULT_ASSIGN", "DIV_ASSIGN", 
		"LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "SEMICOLON", "WHITESPACE", 
		"COMMENT", "LINE_COMMENT", "GLOBAL", "INCREMENT", "DECREMENT"
	};
	public static readonly IVocabulary DefaultVocabulary = new Vocabulary(_LiteralNames, _SymbolicNames);

	[NotNull]
	public override IVocabulary Vocabulary
	{
		get
		{
			return DefaultVocabulary;
		}
	}

	public override string GrammarFileName { get { return "MiniLang.g4"; } }

	public override string[] RuleNames { get { return ruleNames; } }

	public override string[] ChannelNames { get { return channelNames; } }

	public override string[] ModeNames { get { return modeNames; } }

	public override int[] SerializedAtn { get { return _serializedATN; } }

	static MiniLangLexer() {
		decisionToDFA = new DFA[_ATN.NumberOfDecisions];
		for (int i = 0; i < _ATN.NumberOfDecisions; i++) {
			decisionToDFA[i] = new DFA(_ATN.GetDecisionState(i), i);
		}
	}
	private static int[] _serializedATN = {
		4,0,46,309,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
		6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
		7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
		7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
		7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
		7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
		7,42,2,43,7,43,2,44,7,44,2,45,7,45,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
		2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,
		1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,
		8,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,
		1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,5,13,180,8,13,10,13,12,13,
		183,9,13,1,14,4,14,186,8,14,11,14,12,14,187,1,14,1,14,4,14,192,8,14,11,
		14,12,14,193,3,14,196,8,14,1,15,1,15,5,15,200,8,15,10,15,12,15,203,9,15,
		1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,20,1,20,1,20,1,21,
		1,21,1,21,1,22,1,22,1,23,1,23,1,23,1,24,1,24,1,25,1,25,1,25,1,26,1,26,
		1,26,1,27,1,27,1,27,1,28,1,28,1,29,1,29,1,30,1,30,1,30,1,31,1,31,1,31,
		1,32,1,32,1,32,1,33,1,33,1,33,1,34,1,34,1,35,1,35,1,36,1,36,1,37,1,37,
		1,38,1,38,1,39,1,39,1,40,4,40,266,8,40,11,40,12,40,267,1,40,1,40,1,41,
		1,41,1,41,1,41,5,41,276,8,41,10,41,12,41,279,9,41,1,41,1,41,1,41,1,41,
		1,41,1,42,1,42,1,42,1,42,5,42,290,8,42,10,42,12,42,293,9,42,1,42,1,42,
		1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,44,1,44,1,44,1,45,1,45,1,45,1,277,
		0,46,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,
		14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,
		26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,
		38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,91,46,1,0,6,3,0,65,90,95,
		95,97,122,4,0,48,57,65,90,95,95,97,122,1,0,48,57,2,0,34,34,92,92,3,0,9,
		10,13,13,32,32,2,0,10,10,13,13,316,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,
		0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,
		0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,
		0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,
		1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,
		0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,
		1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,
		0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,
		1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,1,93,1,0,0,
		0,3,100,1,0,0,0,5,112,1,0,0,0,7,123,1,0,0,0,9,127,1,0,0,0,11,133,1,0,0,
		0,13,140,1,0,0,0,15,145,1,0,0,0,17,152,1,0,0,0,19,155,1,0,0,0,21,160,1,
		0,0,0,23,164,1,0,0,0,25,170,1,0,0,0,27,177,1,0,0,0,29,185,1,0,0,0,31,197,
		1,0,0,0,33,206,1,0,0,0,35,208,1,0,0,0,37,210,1,0,0,0,39,212,1,0,0,0,41,
		214,1,0,0,0,43,217,1,0,0,0,45,220,1,0,0,0,47,222,1,0,0,0,49,225,1,0,0,
		0,51,227,1,0,0,0,53,230,1,0,0,0,55,233,1,0,0,0,57,236,1,0,0,0,59,238,1,
		0,0,0,61,240,1,0,0,0,63,243,1,0,0,0,65,246,1,0,0,0,67,249,1,0,0,0,69,252,
		1,0,0,0,71,254,1,0,0,0,73,256,1,0,0,0,75,258,1,0,0,0,77,260,1,0,0,0,79,
		262,1,0,0,0,81,265,1,0,0,0,83,271,1,0,0,0,85,285,1,0,0,0,87,296,1,0,0,
		0,89,303,1,0,0,0,91,306,1,0,0,0,93,94,5,115,0,0,94,95,5,116,0,0,95,96,
		5,114,0,0,96,97,5,117,0,0,97,98,5,99,0,0,98,99,5,116,0,0,99,2,1,0,0,0,
		100,101,5,99,0,0,101,102,5,111,0,0,102,103,5,110,0,0,103,104,5,115,0,0,
		104,105,5,116,0,0,105,106,5,114,0,0,106,107,5,117,0,0,107,108,5,99,0,0,
		108,109,5,116,0,0,109,110,5,111,0,0,110,111,5,114,0,0,111,4,1,0,0,0,112,
		113,5,100,0,0,113,114,5,101,0,0,114,115,5,115,0,0,115,116,5,116,0,0,116,
		117,5,114,0,0,117,118,5,117,0,0,118,119,5,99,0,0,119,120,5,116,0,0,120,
		121,5,111,0,0,121,122,5,114,0,0,122,6,1,0,0,0,123,124,5,105,0,0,124,125,
		5,110,0,0,125,126,5,116,0,0,126,8,1,0,0,0,127,128,5,102,0,0,128,129,5,
		108,0,0,129,130,5,111,0,0,130,131,5,97,0,0,131,132,5,116,0,0,132,10,1,
		0,0,0,133,134,5,115,0,0,134,135,5,116,0,0,135,136,5,114,0,0,136,137,5,
		105,0,0,137,138,5,110,0,0,138,139,5,103,0,0,139,12,1,0,0,0,140,141,5,118,
		0,0,141,142,5,111,0,0,142,143,5,105,0,0,143,144,5,100,0,0,144,14,1,0,0,
		0,145,146,5,100,0,0,146,147,5,111,0,0,147,148,5,117,0,0,148,149,5,98,0,
		0,149,150,5,108,0,0,150,151,5,101,0,0,151,16,1,0,0,0,152,153,5,105,0,0,
		153,154,5,102,0,0,154,18,1,0,0,0,155,156,5,101,0,0,156,157,5,108,0,0,157,
		158,5,115,0,0,158,159,5,101,0,0,159,20,1,0,0,0,160,161,5,102,0,0,161,162,
		5,111,0,0,162,163,5,114,0,0,163,22,1,0,0,0,164,165,5,119,0,0,165,166,5,
		104,0,0,166,167,5,105,0,0,167,168,5,108,0,0,168,169,5,101,0,0,169,24,1,
		0,0,0,170,171,5,114,0,0,171,172,5,101,0,0,172,173,5,116,0,0,173,174,5,
		117,0,0,174,175,5,114,0,0,175,176,5,110,0,0,176,26,1,0,0,0,177,181,7,0,
		0,0,178,180,7,1,0,0,179,178,1,0,0,0,180,183,1,0,0,0,181,179,1,0,0,0,181,
		182,1,0,0,0,182,28,1,0,0,0,183,181,1,0,0,0,184,186,7,2,0,0,185,184,1,0,
		0,0,186,187,1,0,0,0,187,185,1,0,0,0,187,188,1,0,0,0,188,195,1,0,0,0,189,
		191,5,46,0,0,190,192,7,2,0,0,191,190,1,0,0,0,192,193,1,0,0,0,193,191,1,
		0,0,0,193,194,1,0,0,0,194,196,1,0,0,0,195,189,1,0,0,0,195,196,1,0,0,0,
		196,30,1,0,0,0,197,201,5,34,0,0,198,200,8,3,0,0,199,198,1,0,0,0,200,203,
		1,0,0,0,201,199,1,0,0,0,201,202,1,0,0,0,202,204,1,0,0,0,203,201,1,0,0,
		0,204,205,5,34,0,0,205,32,1,0,0,0,206,207,5,43,0,0,207,34,1,0,0,0,208,
		209,5,45,0,0,209,36,1,0,0,0,210,211,5,42,0,0,211,38,1,0,0,0,212,213,5,
		47,0,0,213,40,1,0,0,0,214,215,5,61,0,0,215,216,5,61,0,0,216,42,1,0,0,0,
		217,218,5,33,0,0,218,219,5,61,0,0,219,44,1,0,0,0,220,221,5,60,0,0,221,
		46,1,0,0,0,222,223,5,60,0,0,223,224,5,61,0,0,224,48,1,0,0,0,225,226,5,
		62,0,0,226,50,1,0,0,0,227,228,5,62,0,0,228,229,5,61,0,0,229,52,1,0,0,0,
		230,231,5,38,0,0,231,232,5,38,0,0,232,54,1,0,0,0,233,234,5,124,0,0,234,
		235,5,124,0,0,235,56,1,0,0,0,236,237,5,33,0,0,237,58,1,0,0,0,238,239,5,
		61,0,0,239,60,1,0,0,0,240,241,5,43,0,0,241,242,5,61,0,0,242,62,1,0,0,0,
		243,244,5,45,0,0,244,245,5,61,0,0,245,64,1,0,0,0,246,247,5,42,0,0,247,
		248,5,61,0,0,248,66,1,0,0,0,249,250,5,47,0,0,250,251,5,61,0,0,251,68,1,
		0,0,0,252,253,5,40,0,0,253,70,1,0,0,0,254,255,5,41,0,0,255,72,1,0,0,0,
		256,257,5,123,0,0,257,74,1,0,0,0,258,259,5,125,0,0,259,76,1,0,0,0,260,
		261,5,44,0,0,261,78,1,0,0,0,262,263,5,59,0,0,263,80,1,0,0,0,264,266,7,
		4,0,0,265,264,1,0,0,0,266,267,1,0,0,0,267,265,1,0,0,0,267,268,1,0,0,0,
		268,269,1,0,0,0,269,270,6,40,0,0,270,82,1,0,0,0,271,272,5,47,0,0,272,273,
		5,42,0,0,273,277,1,0,0,0,274,276,9,0,0,0,275,274,1,0,0,0,276,279,1,0,0,
		0,277,278,1,0,0,0,277,275,1,0,0,0,278,280,1,0,0,0,279,277,1,0,0,0,280,
		281,5,42,0,0,281,282,5,47,0,0,282,283,1,0,0,0,283,284,6,41,0,0,284,84,
		1,0,0,0,285,286,5,47,0,0,286,287,5,47,0,0,287,291,1,0,0,0,288,290,8,5,
		0,0,289,288,1,0,0,0,290,293,1,0,0,0,291,289,1,0,0,0,291,292,1,0,0,0,292,
		294,1,0,0,0,293,291,1,0,0,0,294,295,6,42,0,0,295,86,1,0,0,0,296,297,5,
		103,0,0,297,298,5,108,0,0,298,299,5,111,0,0,299,300,5,98,0,0,300,301,5,
		97,0,0,301,302,5,108,0,0,302,88,1,0,0,0,303,304,5,43,0,0,304,305,5,43,
		0,0,305,90,1,0,0,0,306,307,5,45,0,0,307,308,5,45,0,0,308,92,1,0,0,0,9,
		0,181,187,193,195,201,267,277,291,1,6,0,0
	};

	public static readonly ATN _ATN =
		new ATNDeserializer().Deserialize(_serializedATN);


}
