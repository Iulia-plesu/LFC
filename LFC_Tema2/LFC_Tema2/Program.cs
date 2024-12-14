using System;
using System.IO;
using Antlr4.Runtime;

namespace LFC_Tema2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string inputFile = "C:\\Users\\Plesu\\Desktop\\LFC_Tema2\\LFC_Tema2\\program.txt"; // Înlocuiește cu calea către fișierul sursă
            string inputCode = File.ReadAllText(inputFile);

            // Cream un input stream din textul citit
            AntlrInputStream inputStream = new AntlrInputStream(inputCode);

            // Cream un lexer (care va imparti input-ul in unitati lexicale)
            MiniLangLexer lexer = new MiniLangLexer(inputStream);

            // Cream un stream de tokens (unitati lexicale)
            CommonTokenStream tokens = new CommonTokenStream(lexer);

            // Cream un parser (care va analiza structura sintactica a codului)
            MiniLangParser parser = new MiniLangParser(tokens);

            // Incepem analiza sintactica
            var context = parser.program(); // Apelam regula de start a gramaticii (program)

            Console.WriteLine("Program analizat cu succes!");

            // Afișează token-urile extrase
            foreach (var token in tokens.GetTokens())
            {
                Console.WriteLine($"Token: {token.Text}, Tip: {token.Type}");
            }
        }
    }
}
