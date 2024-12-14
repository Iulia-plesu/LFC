//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     ANTLR Version: 4.13.1
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Generated from c:/Users/Plesu/Desktop/LFC_Tema2/LFC_Tema2/MiniLang.g4 by ANTLR 4.13.1

// Unreachable code detected
#pragma warning disable 0162
// The variable '...' is assigned but its value is never used
#pragma warning disable 0219
// Missing XML comment for publicly visible type or member '...'
#pragma warning disable 1591
// Ambiguous reference in cref attribute
#pragma warning disable 419

using Antlr4.Runtime.Misc;
using Antlr4.Runtime.Tree;
using IToken = Antlr4.Runtime.IToken;

/// <summary>
/// This interface defines a complete generic visitor for a parse tree produced
/// by <see cref="MiniLangParser"/>.
/// </summary>
/// <typeparam name="Result">The return type of the visit operation.</typeparam>
[System.CodeDom.Compiler.GeneratedCode("ANTLR", "4.13.1")]
[System.CLSCompliant(false)]
public interface IMiniLangVisitor<Result> : IParseTreeVisitor<Result> {
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.program"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitProgram([NotNull] MiniLangParser.ProgramContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.statement"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitStatement([NotNull] MiniLangParser.StatementContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.globalDeclaration"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitGlobalDeclaration([NotNull] MiniLangParser.GlobalDeclarationContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.declaration"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitDeclaration([NotNull] MiniLangParser.DeclarationContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.parameterList"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitParameterList([NotNull] MiniLangParser.ParameterListContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.parameter"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitParameter([NotNull] MiniLangParser.ParameterContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.block"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitBlock([NotNull] MiniLangParser.BlockContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.assignment"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitAssignment([NotNull] MiniLangParser.AssignmentContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.expressionStatement"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitExpressionStatement([NotNull] MiniLangParser.ExpressionStatementContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.ifStatement"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitIfStatement([NotNull] MiniLangParser.IfStatementContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.whileStatement"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitWhileStatement([NotNull] MiniLangParser.WhileStatementContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.forStatement"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitForStatement([NotNull] MiniLangParser.ForStatementContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.forInit"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitForInit([NotNull] MiniLangParser.ForInitContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.returnStatement"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitReturnStatement([NotNull] MiniLangParser.ReturnStatementContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.expression"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitExpression([NotNull] MiniLangParser.ExpressionContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.term"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitTerm([NotNull] MiniLangParser.TermContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.factor"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitFactor([NotNull] MiniLangParser.FactorContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.binaryOp"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitBinaryOp([NotNull] MiniLangParser.BinaryOpContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.multiplicativeOp"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitMultiplicativeOp([NotNull] MiniLangParser.MultiplicativeOpContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.expressionList"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitExpressionList([NotNull] MiniLangParser.ExpressionListContext context);
	/// <summary>
	/// Visit a parse tree produced by <see cref="MiniLangParser.type"/>.
	/// </summary>
	/// <param name="context">The parse tree.</param>
	/// <return>The visitor result.</return>
	Result VisitType([NotNull] MiniLangParser.TypeContext context);
}
