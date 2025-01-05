using System;
using System.IO;
using System.Collections.Generic;
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using System.Linq;

namespace LFC_Tema2
{
    public class MiniLangVisitor : MiniLangBaseVisitor<object>
    {
        private HashSet<string> globalVariables = new HashSet<string>();  
        private Dictionary<string, HashSet<string>> localVariables = new Dictionary<string, HashSet<string>>(); 
        private HashSet<string> functionNames = new HashSet<string>(); 
        private string currentFunctionName = "";  
        private void CheckFunctionUniqueness(string functionName, List<string> parameterNames)
        {
            if (functionNames.Contains(functionName))
            {
                throw new Exception($"Eroare: Functia '{functionName}' este deja definita!");
            }
            functionNames.Add(functionName);
        }

        private bool IsTypeCompatible(string declaredType, string value)
        {
            switch (declaredType)
            {
                case "int":
                    return int.TryParse(value, out _);
                case "float":
                    return float.TryParse(value, out _);
                case "double":
                    return double.TryParse(value, out _);
                case "string":
                    return value.StartsWith("\"") && value.EndsWith("\"");
                default:
                    return false;
            }
        }

        public override object VisitGlobalDeclaration(MiniLangParser.GlobalDeclarationContext context)
        {
            string variableName = context.ID().GetText();
            string type = context.type().GetText();

            if (globalVariables.Contains(variableName))
            {
                throw new Exception($"Eroare: Variabila globala '{variableName}' este deja declarata!");
            }

            globalVariables.Add(variableName);
            Console.WriteLine($"Variabila globala declarata: {variableName} de tip {type}");
            return base.VisitGlobalDeclaration(context);
        }

        private bool IsVariableGlobal(string variableName)
        {
            return globalVariables.Contains(variableName);
        }

        public override object VisitFunctionDeclaration(MiniLangParser.FunctionDeclarationContext context)
        {
            string functionName = context.ID().GetText();
            List<string> parameterNames = context.parameterList()?.parameter()?.Select(p => p.ID().GetText()).ToList() ?? new List<string>();

            CheckFunctionUniqueness(functionName, parameterNames);

            currentFunctionName = functionName;
            Console.WriteLine($"\nFunctia '{functionName}' a fost declarata cu parametrii: {string.Join(", ", parameterNames)}");

            if (!localVariables.ContainsKey(functionName))
            {
                localVariables[functionName] = new HashSet<string>();
            }

            foreach (var param in parameterNames)
            {
                if (localVariables[functionName].Contains(param))
                {
                    throw new Exception($"Eroare: Parametrul '{param}' este deja declarat in functia '{functionName}'!");
                }
                localVariables[functionName].Add(param);
                Console.WriteLine($"Parametru local '{param}' declarat in functia '{functionName}'");
            }

            return base.VisitFunctionDeclaration(context);
        }

        public override object VisitDeclaration(MiniLangParser.DeclarationContext context)
        {
            string variableName = context.ID().GetText();
            string type = context.type().GetText();
            string value = context.expression().GetText();

            if (!IsTypeCompatible(type, value))
            {
                Console.WriteLine($"\nAvertisment: Tip incompatibil pentru variabila '{variableName}'. Se astepta un '{type}', dar s-a gasit '{value}'.");
            }

            if (currentFunctionName != "")
            {
                if (!localVariables.ContainsKey(currentFunctionName))
                {
                    localVariables[currentFunctionName] = new HashSet<string>();
                }

                if (localVariables[currentFunctionName].Contains(variableName))
                {
                    throw new Exception($"Eroare: Variabila '{variableName}' este deja declarata in functia '{currentFunctionName}'!");
                }

                localVariables[currentFunctionName].Add(variableName);
                Console.WriteLine($"Variabila locala '{variableName}' declarata in functia '{currentFunctionName}' de tip {type} cu valoarea {value}");
            }
            else
            {
                if (globalVariables.Contains(variableName))
                {
                    throw new Exception($"Eroare: Variabila globala '{variableName}' este deja declarata!");
                }

                globalVariables.Add(variableName);
                Console.WriteLine($"Variabila globala '{variableName}' declarata de tip {type} cu valoarea {value}");
            }

            return base.VisitDeclaration(context);
        }

        public override object VisitAssignment(MiniLangParser.AssignmentContext context)
        {
            string variableName = context.ID().GetText();
            string value = context.expression().GetText();

            if (!IsVariableGlobal(variableName) && !IsVariableDeclaredInCurrentScope(variableName))
            {
                throw new Exception($"Eroare: Variabila '{variableName}' nu a fost declarata inainte de a fi utilizata!");
            }

            Console.WriteLine($"\nAsignare valida: {variableName} = {value}");
            return base.VisitAssignment(context);
        }

        private bool IsVariableDeclaredInCurrentScope(string variableName)
        {
            if (currentFunctionName != "" && localVariables.ContainsKey(currentFunctionName))
            {
                return localVariables[currentFunctionName].Contains(variableName);
            }
            return false;
        }

        public override object VisitStructDeclaration(MiniLangParser.StructDeclarationContext context)
        {
            string structName = context.ID().GetText();
            Console.WriteLine($"\nStructura '{structName}' a fost declarata.");

            foreach (var field in context.children)
            {
                if (field is MiniLangParser.DeclarationContext fieldDecl)
                {
                    string fieldName = fieldDecl.ID().GetText();
                    string fieldType = fieldDecl.type().GetText();
                    Console.WriteLine($"Variabila '{fieldName}' de tip '{fieldType}' declarata in structura '{structName}'");
                }
            }

            return base.VisitStructDeclaration(context);
        }

        public override object VisitFunctionCall(MiniLangParser.FunctionCallContext context)
        {
            string functionName = context.ID().GetText();

            if (!functionNames.Contains(functionName))
            {
                throw new Exception($"Eroare: Functia '{functionName}' este apelata, dar nu a fost definita!");
            }

            Console.WriteLine($"Apel functie valid: {functionName}");
            return base.VisitFunctionCall(context);
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            string inputFile = "program.txt";

            try
            {
                string inputCode = File.ReadAllText(inputFile);

                AntlrInputStream inputStream = new AntlrInputStream(inputCode);
                MiniLangLexer lexer = new MiniLangLexer(inputStream);
                CommonTokenStream tokens = new CommonTokenStream(lexer);
                MiniLangParser parser = new MiniLangParser(tokens);

                parser.RemoveErrorListeners();
                parser.AddErrorListener(new ErrorListener());

                IParseTree tree = parser.program();

                MiniLangVisitor visitor = new MiniLangVisitor();
                visitor.Visit(tree);

                Console.WriteLine("Program analizat cu succes!");

                foreach (var token in tokens.GetTokens())
                {
                    Console.WriteLine($"Token: {token.Text}, Tip: {token.Type}");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare: {ex.Message}");
            }
        }
    }

    public class ErrorListener : BaseErrorListener
    {
        public void SyntaxError(
            IRecognizer recognizer,
            IToken offendingSymbol,
            int line,
            int charPositionInLine,
            string msg,
            RecognitionException e)
        {
            Console.WriteLine($"Eroare sintactica: linia {line}, coloana {charPositionInLine}: {msg}");
        }
    }
}
