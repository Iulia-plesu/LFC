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

            AntlrInputStream inputStream = new AntlrInputStream(inputCode);

            MiniLangLexer lexer = new MiniLangLexer(inputStream);

            CommonTokenStream tokens = new CommonTokenStream(lexer);

            MiniLangParser parser = new MiniLangParser(tokens);

            var context = parser.program(); 

            Console.WriteLine("Program analizat cu succes!");

            foreach (var token in tokens.GetTokens())
            {
                Console.WriteLine($"Token: {token.Text}, Tip: {token.Type}");
            }
        }
    }
}
