#pragma once

#include <string>

using namespace std;

enum class TokenType
{
    // literals
    IDENTIFIER,
    NUMBER,
    STRING,

    // operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    MODULO,

    EQUAL,
    EQUAL_EQUAL,

    BANG,
    BANG_EQUAL,

    LESS,
    LESS_EQUAL,

    GREATER,
    GREATER_EQUAL,

    AND_AND,
    OR_OR,

    PLUS_PLUS,
    MINUS_MINUS,

    // assignment
    PLUS_EQUAL,
    MINUS_EQUAL,
    STAR_EQUAL,
    SLASH_EQUAL,

    // punctuation
    LEFT_PAREN,
    RIGHT_PAREN,

    LEFT_BRACE,
    RIGHT_BRACE,

    LEFT_BRACKET,
    RIGHT_BRACKET,

    COMMA,
    DOT,
    SEMICOLON,

    // keywords
    IF,
    ELSE,
    WHILE,
    FOR,
    RETURN,

    FUNCTION,

    TRUE,
    FALSE,
    NULL_TOKEN,

    END_OF_FILE,

    INT,
    FLOAT,
    DOUBLE,
    BOOL,
    CHAR,

    ERROR
};

class Token
{
public:
    Token(TokenType t, const string &v, int l)
        : Lexeme(v), type(t), line(l)
    {
    }

    TokenType getType() const { return type; }
    string getLexeme() const { return Lexeme; }
    int getLine() const { return line; }

private:
    string Lexeme;
    TokenType type;
    int line;
};
