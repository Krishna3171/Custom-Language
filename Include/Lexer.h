#pragma once

#include <string>
#include <vector>

#include "Token.h"

class Lexer
{
public:
    explicit Lexer(const std::string& source);

    // Performs lexical analysis and returns all tokens.
    std::vector<Token> tokenize();

private:
    // Source code
    std::string source;

    // Current scanning positions
    size_t start = 0;
    size_t current = 0;

    // Current line number
    int line = 1;

    // Output tokens
    std::vector<Token> tokens;

    //----------------------------------------------------
    // Core helpers
    //----------------------------------------------------

    bool isAtEnd() const;

    char advance();

    char peek() const;

    char peekNext() const;

    bool match(char expected);

    void addToken(TokenType type, const std::string& lexeme);

    //----------------------------------------------------
    // Token scanners
    //----------------------------------------------------

    void scanToken();

    void number();

    void identifierOrKeyword();

    void stringLiteral();

    void skipWhitespace();

    //----------------------------------------------------
    // Character classification
    //----------------------------------------------------

    static bool isDigit(char c);

    static bool isAlpha(char c);

    static bool isAlphaNumeric(char c);
};