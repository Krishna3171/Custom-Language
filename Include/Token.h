#pragma once

#include <string>

enum class TokenType
{
    // Literals
    IDENTIFIER,
    NUMBER,
    STRING,

    // Operators
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

    // Compound Assignment
    PLUS_EQUAL,
    MINUS_EQUAL,
    STAR_EQUAL,
    SLASH_EQUAL,

    // Punctuation
    LEFT_PAREN,
    RIGHT_PAREN,

    LEFT_BRACE,
    RIGHT_BRACE,

    LEFT_BRACKET,
    RIGHT_BRACKET,

    COMMA,
    DOT,
    SEMICOLON,

    // Keywords
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
    Token(
        TokenType type,
        const std::string& lexeme,
        int line);

    TokenType getType() const;

    const std::string& getLexeme() const;

    int getLine() const;

private:
    std::string lexeme;
    TokenType type;
    int line;
};

// Optional helper for debugging
std::string tokenTypeToString(TokenType type);