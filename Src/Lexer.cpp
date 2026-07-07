#include "D:\computer science\Custom Language\Include\Lexer.h"

#include <cctype>
#include <iostream>
#include <unordered_map>

namespace
{
    const std::unordered_map<std::string, TokenType> keywords =
        {
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"while", TokenType::WHILE},
            {"for", TokenType::FOR},
            {"return", TokenType::RETURN},

            {"function", TokenType::FUNCTION},

            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"null", TokenType::NULL_TOKEN},

            {"int", TokenType::INT},
            {"float", TokenType::FLOAT},
            {"double", TokenType::DOUBLE},
            {"bool", TokenType::BOOL},
            {"char", TokenType::CHAR}};
}

Lexer::Lexer(const std::string &source)
    : source(source)
{
}

bool Lexer::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool Lexer::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Lexer::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}

bool Lexer::isAtEnd() const
{
    return current >= source.length();
}

char Lexer::advance()
{
    return source[current++];
}

char Lexer::peek() const
{
    if (isAtEnd())
        return '\0';

    return source[current];
}

char Lexer::peekNext() const
{
    if (current + 1 >= source.length())
        return '\0';

    return source[current + 1];
}

bool Lexer::match(char expected)
{
    if (isAtEnd())
        return false;

    if (source[current] != expected)
        return false;

    current++;
    return true;
}

void Lexer::addToken(TokenType type, const std::string &lexeme)
{
    tokens.emplace_back(type, lexeme, line);
}

void Lexer::number()
{
    // Integer part
    while (isDigit(peek()))
    {
        advance();
    }

    // Fractional part
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance(); // consume '.'

        while (isDigit(peek()))
        {
            advance();
        }
    }

    addToken(
        TokenType::NUMBER,
        source.substr(start, current - start));
}

void Lexer::identifierOrKeyword()
{
    while (isAlphaNumeric(peek()))
    {
        advance();
    }

    std::string text = source.substr(start, current - start);

    auto it = keywords.find(text);

    if (it != keywords.end())
    {
        addToken(it->second, text);
    }
    else
    {
        addToken(TokenType::IDENTIFIER, text);
    }
}

void Lexer::stringLiteral()
{
    while (!isAtEnd() && peek() != '"')
    {
        if (peek() == '\n')
        {
            line++;
        }

        advance();
    }

    if (isAtEnd())
    {
        std::cerr << "Lexer Error (line "
                  << line
                  << "): Unterminated string.\n";

        addToken(TokenType::ERROR, "Unterminated string");
        return;
    }

    // Consume closing quote
    advance();

    std::string value =
        source.substr(start + 1, current - start - 2);

    addToken(TokenType::STRING, value);
}

void Lexer::skipWhitespace()
{
    while (!isAtEnd())
    {
        switch (peek())
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;

        case '\n':
            line++;
            advance();
            break;

        default:
            return;
        }
    }
}

void Lexer::scanToken()
{
    char c = advance();

    switch (c)
    {
    // Parentheses
    case '(':
        addToken(TokenType::LEFT_PAREN, "(");
        break;

    case ')':
        addToken(TokenType::RIGHT_PAREN, ")");
        break;

    // Braces
    case '{':
        addToken(TokenType::LEFT_BRACE, "{");
        break;

    case '}':
        addToken(TokenType::RIGHT_BRACE, "}");
        break;

    // Brackets
    case '[':
        addToken(TokenType::LEFT_BRACKET, "[");
        break;

    case ']':
        addToken(TokenType::RIGHT_BRACKET, "]");
        break;

    // Punctuation
    case ',':
        addToken(TokenType::COMMA, ",");
        break;

    case '.':
        addToken(TokenType::DOT, ".");
        break;

    case ';':
        addToken(TokenType::SEMICOLON, ";");
        break;

    // +
    case '+':
        if (match('+'))
            addToken(TokenType::PLUS_PLUS, "++");
        else if (match('='))
            addToken(TokenType::PLUS_EQUAL, "+=");
        else
            addToken(TokenType::PLUS, "+");
        break;

    // -
    case '-':
        if (match('-'))
            addToken(TokenType::MINUS_MINUS, "--");
        else if (match('='))
            addToken(TokenType::MINUS_EQUAL, "-=");
        else
            addToken(TokenType::MINUS, "-");
        break;

    // *
    case '*':
        if (match('='))
            addToken(TokenType::STAR_EQUAL, "*=");
        else
            addToken(TokenType::STAR, "*");
        break;

    // /
    case '/':
        if (match('/'))
        {
            while (peek() != '\n' && !isAtEnd())
                advance();
        }
        else if (match('='))
        {
            addToken(TokenType::SLASH_EQUAL, "/=");
        }
        else
        {
            addToken(TokenType::SLASH, "/");
        }
        break;

    // %
    case '%':
        addToken(TokenType::MODULO, "%");
        break;

    // =
    case '=':
    {
        bool equalEqual = match('=');
        addToken(equalEqual ? TokenType::EQUAL_EQUAL : TokenType::EQUAL,
                 equalEqual ? "==" : "=");
    }
    break;

    // !
    case '!':
        if (match('='))
            addToken(TokenType::BANG_EQUAL, "!=");
        else
            addToken(TokenType::BANG, "!");
        break;

    // <
    case '<':
        if (match('='))
            addToken(TokenType::LESS_EQUAL, "<=");
        else
            addToken(TokenType::LESS, "<");
        break;

    // >
    case '>':
        if (match('='))
            addToken(TokenType::GREATER_EQUAL, ">=");
        else
            addToken(TokenType::GREATER, ">");
        break;

    // &&
    case '&':
        if (match('&'))
        {
            addToken(TokenType::AND_AND, "&&");
        }
        else
        {
            std::cerr << "Unexpected '&' at line "
                      << line << '\n';

            addToken(TokenType::ERROR, "&");
        }
        break;

    // ||
    case '|':
        if (match('|'))
        {
            addToken(TokenType::OR_OR, "||");
        }
        else
        {
            std::cerr << "Unexpected '|' at line "
                      << line << '\n';

            addToken(TokenType::ERROR, "|");
        }
        break;

    // String
    case '"':
        stringLiteral();
        break;

    // Whitespace
    case ' ':
    case '\r':
    case '\t':
        skipWhitespace();
        break;

    case '\n':
        line++;
        break;

    default:

        if (isDigit(c))
        {
            number();
        }
        else if (isAlpha(c))
        {
            identifierOrKeyword();
        }
        else
        {
            std::cerr << "Unexpected character '"
                      << c
                      << "' at line "
                      << line
                      << '\n';

            addToken(
                TokenType::ERROR,
                std::string(1, c));
        }

        break;
    }
}

std::vector<Token> Lexer::tokenize()
{
    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    tokens.emplace_back(
        TokenType::END_OF_FILE,
        "",
        line);

    return tokens;
}

