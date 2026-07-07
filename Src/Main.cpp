#include "D:\computer science\Custom Language\Include/Lexer.h"
#include "D:\computer science\Custom Language\Include/Parser.h"
#include <iostream>



int main()
{
    std::string sourceCode = "int x = 42; int y = 0; if (x >= 0) { x == x / y + 1; }";
    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.tokenize();

    for (const Token &token : tokens)
    {
        std::cout << "Token: " << token.getLexeme()
                  << ", Type: " << tokenTypeToString(token.getType())
                  << ", Line: " << token.getLine() << '\n';
    }

    return 0;
}