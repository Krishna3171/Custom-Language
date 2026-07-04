#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "Lexer.h"

using namespace std;

unordered_map<string, TokenType> keywords = {
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

bool isDigit(char c) // to check if a character is a digit and different from isdigit() which checks for any digit in any locale
{
    return c >= '0' && c <= '9';
}

bool isAlphaNumeric(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || isdigit(c);
}

bool isAlpha(char c) // to check if a character is an alphabetic character or underscore, different from isalpha() which checks for any alphabetic character in any locale
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

class Lexer
{
public:
    Lexer(const string &source) : source(source)
    {
    }
    vector<Token> tokenize()
    {
        while (!isAtEnd())
        {
            start = current;
            scanToken();
        }
        tokens.emplace_back(TokenType::END_OF_FILE, "", line);
        return tokens;
    }

private:
    string source;
    size_t current = 0;
    size_t start = 0;
    int line = 1;

    vector<Token> tokens;

    bool isAtEnd()
    {
        return current >= source.length();
    }

    char advance()
    {
        return source[current++];
    }

    char peek()
    {
        if (isAtEnd())
            return '\0';
        return source[current];
    }

    char peekNext()
    {
        if (current + 1 >= source.length())
            return '\0';
        return source[current + 1];
    }

    bool match(char expected)
    {
        if (isAtEnd())
            return false;
        if (source[current] != expected)
            return false;
        current++;
        return true;
    }

    void addToken(TokenType type, const string &Lexeme)
    {
        tokens.emplace_back(type, Lexeme, line);
    }

    void number()
    {
        while (isdigit(peek()))
            advance();

        if (peek() == '.' && isdigit(peekNext()))
        {
            advance();

            while (isdigit(peek()))
                advance();
        }
        addToken(TokenType::NUMBER, source.substr(start, current - start));
    }

    void identifierOrKeyword()
    {
        while (isAlphaNumeric(peek()))
            advance();
        string text = source.substr(start, current - start);
        TokenType type = TokenType::IDENTIFIER;

        if (keywords.find(text) != keywords.end())
        {
            type = keywords[text];
        }

        addToken(type, text);
    }

    void stringLiteral()
    {
        while (peek() != '"' && !isAtEnd())
        {
            if (peek() == '\n')
                line++;
            advance();
        }

        if (isAtEnd())
        {
            cerr << "Unterminated string at line " << line << endl;
            return;
        }

        // The closing "
        advance();

        // Trim the surrounding quotes
        string Lexeme = source.substr(start + 1, current - start - 2);
        addToken(TokenType::STRING, Lexeme);
    }

    void skipWhitespace()
    {
        while (true)
        {
            char c = peek();
            switch (c)
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

    void scanToken()
    {
        char c = advance();
        switch (c)
        {
        case '(':
            addToken(TokenType::LEFT_PAREN, "(");
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN, ")");
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE, "{");
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE, "}");
            break;
        case '[':
            addToken(TokenType::LEFT_BRACKET, "[");
            break;
        case ']':
            addToken(TokenType::RIGHT_BRACKET, "]");
            break;
        case ',':
            addToken(TokenType::COMMA, ",");
            break;
        case '.':
            addToken(TokenType::DOT, ".");
            break;
        case ';':
            addToken(TokenType::SEMICOLON, ";");
            break;
        case '+':
            if (match('+'))
            {
                addToken(TokenType::PLUS_PLUS, "++");
            }
            else if (match('='))
            {
                addToken(TokenType::PLUS_EQUAL, "+=");
            }
            else
            {
                addToken(TokenType::PLUS, "+");
            }
            break;
        case '-':
            if (match('-'))
            {
                addToken(TokenType::MINUS_MINUS, "--");
            }
            else if (match('='))
            {
                addToken(TokenType::MINUS_EQUAL, "-=");
            }
            else
            {
                addToken(TokenType::MINUS, "-");
            }
            break;
        case '*':
            if (match('='))
            {
                addToken(TokenType::STAR_EQUAL, "*=");
            }
            else
            {
                addToken(TokenType::STAR, "*");
            }
            break;
        case '/':
            if (match('/'))
            {
                // Handle single-line comment
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
        case '%':
            addToken(TokenType::MODULO, "%");
            break;

        case '=':
        {
            bool isEqualEqual = match('=');
            addToken(isEqualEqual ? TokenType::EQUAL_EQUAL : TokenType::EQUAL, isEqualEqual ? "==" : "=");
            break;
        }

        case '!':
        {
            bool isBangEqual = match('=');
            addToken(isBangEqual ? TokenType::BANG_EQUAL : TokenType::BANG, isBangEqual ? "!=" : "!");
            break;
        }

        case '<':
        {
            bool isLessEqual = match('=');
            addToken(isLessEqual ? TokenType::LESS_EQUAL : TokenType::LESS, isLessEqual ? "<=" : "<");
            break;
        }

        case '>':
        {
            bool isGreaterEqual = match('=');
            addToken(isGreaterEqual ? TokenType::GREATER_EQUAL : TokenType::GREATER, isGreaterEqual ? ">=" : ">");
            break;
        }

        case '&':
            if (match('&'))
            {
                addToken(TokenType::AND_AND, "&&");
            }
            else
            {
                cerr << "Unexpected character: &" << endl;
                addToken(TokenType::ERROR, "&");
            }
            break;

        case '|':
            if (match('|'))
            {
                addToken(TokenType::OR_OR, "||");
            }
            else
            {
                cerr << "Unexpected character: |" << endl;
                addToken(TokenType::ERROR, "|");
            }
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
            else if (c == '"')
            {
                stringLiteral();
            }
            else if (c == ' ' || c == '\r' || c == '\t')
            {
                skipWhitespace();
            }
            else if (c == '\n')
            {
                line++;
            }
            else
            {
                // Handle unexpected characters
                cerr << "Unexpected character: " << c << endl;
                addToken(TokenType::ERROR, string(1, c));
            }
            break;
        }
    }
};

int main()
{
    string sourceCode = "int x = 42;int y = 0; if (x >= 0) { x == x/y + 1; }";
    Lexer lexer(sourceCode);
    vector<Token> tokens = lexer.tokenize();

    for (const Token &token : tokens)
    {
        cout << "Token Type: " << static_cast<int>(token.getType()) << ", Lexeme: " << token.getLexeme() << endl;
    }

    return 0;
}
