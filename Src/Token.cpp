#include "D:\computer science\Custom Language\Include\Token.h"

Token::Token(
    TokenType type,
    const std::string &lexeme,
    int line)
    : lexeme(lexeme),
      type(type),
      line(line)
{
}

TokenType Token::getType() const
{
    return type;
}

const std::string &Token::getLexeme() const
{
    return lexeme;
}

int Token::getLine() const
{
    return line;
}

std::string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::NUMBER:
        return "NUMBER";
    case TokenType::STRING:
        return "STRING";

    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::STAR:
        return "STAR";
    case TokenType::SLASH:
        return "SLASH";
    case TokenType::MODULO:
        return "MODULO";

    case TokenType::EQUAL:
        return "EQUAL";
    case TokenType::EQUAL_EQUAL:
        return "EQUAL_EQUAL";

    case TokenType::BANG:
        return "BANG";
    case TokenType::BANG_EQUAL:
        return "BANG_EQUAL";

    case TokenType::LESS:
        return "LESS";
    case TokenType::LESS_EQUAL:
        return "LESS_EQUAL";

    case TokenType::GREATER:
        return "GREATER";
    case TokenType::GREATER_EQUAL:
        return "GREATER_EQUAL";

    case TokenType::AND_AND:
        return "AND_AND";
    case TokenType::OR_OR:
        return "OR_OR";

    case TokenType::PLUS_PLUS:
        return "PLUS_PLUS";
    case TokenType::MINUS_MINUS:
        return "MINUS_MINUS";

    case TokenType::PLUS_EQUAL:
        return "PLUS_EQUAL";
    case TokenType::MINUS_EQUAL:
        return "MINUS_EQUAL";
    case TokenType::STAR_EQUAL:
        return "STAR_EQUAL";
    case TokenType::SLASH_EQUAL:
        return "SLASH_EQUAL";

    case TokenType::LEFT_PAREN:
        return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN:
        return "RIGHT_PAREN";

    case TokenType::LEFT_BRACE:
        return "LEFT_BRACE";
    case TokenType::RIGHT_BRACE:
        return "RIGHT_BRACE";

    case TokenType::LEFT_BRACKET:
        return "LEFT_BRACKET";
    case TokenType::RIGHT_BRACKET:
        return "RIGHT_BRACKET";

    case TokenType::COMMA:
        return "COMMA";
    case TokenType::DOT:
        return "DOT";
    case TokenType::SEMICOLON:
        return "SEMICOLON";

    case TokenType::IF:
        return "IF";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::WHILE:
        return "WHILE";
    case TokenType::FOR:
        return "FOR";
    case TokenType::RETURN:
        return "RETURN";
    case TokenType::FUNCTION:
        return "FUNCTION";

    case TokenType::TRUE:
        return "TRUE";
    case TokenType::FALSE:
        return "FALSE";
    case TokenType::NULL_TOKEN:
        return "NULL";

    case TokenType::INT:
        return "INT";
    case TokenType::FLOAT:
        return "FLOAT";
    case TokenType::DOUBLE:
        return "DOUBLE";
    case TokenType::BOOL:
        return "BOOL";
    case TokenType::CHAR:
        return "CHAR";

    case TokenType::END_OF_FILE:
        return "EOF";

    case TokenType::ERROR:
        return "ERROR";
    }

    return "UNKNOWN";
}