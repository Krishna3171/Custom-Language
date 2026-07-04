#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;



enum class TokenType
{
    Number,
    Identifier,
    Keyword,
    Literal,
    Operator,
    Separator,
    Comment,
    Whitespace,
    EndOfFile
};

class Token
{
public:
    Token(TokenType t, const string &v) : type(t), value(v) {}

    TokenType getType() const { return type; }
    string getValue() const { return value; }

private:
    string value;
    TokenType type;
};

bool isdigit(const string &str);
bool isIdentifier(const string &str);
bool isAlpha(const string &str);

vector<Token> tokenize(const string &sourceCode)
{
    vector<Token> tokens;

    vector<string> keywords = {"if", "else", "while", "for", "return", "int", "float", "double", "char", "void"};

    vector<string> operators = {"+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "%"};

    vector<string> separators = {"(", ")", "{", "}", "[", "]", ";", ","};

    vector<string> literals = {"true", "false", "null"};

    vector<string> comments = {"//", "/*", "*/"};

    vector<string> whitespace = {" ", "\t", "\n"};

    //parsing the src char by char and tokenizing it based on the defined keywords, operators, separators, literals, comments, and whitespace
    istringstream iss(sourceCode);

    string code = sourceCode;
    while (code.length() > 0)
    {
        string tokenValue = code.substr(0, 1);
        code.erase(0, 1); // Remove the first character from the source code

        bool canBeNegativeNumber = false;
        if (tokenValue == "-" && !code.empty() && isdigit(code.substr(0, 1)))
        {
            if (tokens.empty())
            {
                canBeNegativeNumber = true;
            }
            else
            {
                const Token &prev = tokens.back();
                if (prev.getType() == TokenType::Operator || prev.getType() == TokenType::Separator || prev.getType() == TokenType::Whitespace)
                {
                    canBeNegativeNumber = true;
                }
                else if (prev.getType() == TokenType::Keyword && prev.getValue() == "return")
                {
                    canBeNegativeNumber = true;
                }
            }
        }

        if (find(keywords.begin(), keywords.end(), tokenValue) != keywords.end())
        {
            tokens.push_back(Token(TokenType::Keyword, tokenValue));
        }
        else if ((!tokenValue.empty() && isdigit(tokenValue)) || canBeNegativeNumber)
        {
            while (!code.empty() && (isdigit(code.substr(0, 1)) ))
            {
                tokenValue += code.substr(0, 1);
                code.erase(0, 1);
            }
            tokens.push_back(Token(TokenType::Number, tokenValue));
        }
        else if (find(operators.begin(), operators.end(), tokenValue) != operators.end())
        {
            tokens.push_back(Token(TokenType::Operator, tokenValue));
        }
        else if (find(separators.begin(), separators.end(), tokenValue) != separators.end())
        {
            tokens.push_back(Token(TokenType::Separator, tokenValue));
        }
        else if (find(literals.begin(), literals.end(), tokenValue) != literals.end())
        {
            tokens.push_back(Token(TokenType::Literal, tokenValue));
        }
        else if (find(comments.begin(), comments.end(), tokenValue) != comments.end())
        {
            tokens.push_back(Token(TokenType::Comment, tokenValue));
        }
        else if (find(whitespace.begin(), whitespace.end(), tokenValue) != whitespace.end())
        {
            tokens.push_back(Token(TokenType::Whitespace, tokenValue));
        }
        
        else if (!tokenValue.empty() && isAlpha(tokenValue))
        {
            while (!code.empty() && isAlpha(code.substr(0, 1)))
            {
                tokenValue += code.substr(0, 1);
                code.erase(0, 1);
            }
            tokens.push_back(Token(TokenType::Identifier, tokenValue));
        }
        else
        {
            cerr << "Unknown token: " << tokenValue << endl;
        }
    }
    return tokens;
}

bool isdigit(const string &str)   
{
    if (str.empty())
        return false;

    for (char c : str){
        if ((c < '0' || c > '9') && c != '.')
            return false;
    }
    return true;
}

bool isAlpha(const string &str)
{
    if (str.empty() || !isalpha(str[0]))
        return false;

    for (char c : str)
    {
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}


int main()
{
    string sourceCode = "int main() { return 10-100; }";
    vector<Token> tokens = tokenize(sourceCode);

    for (const Token &token : tokens)
    {
        cout << "Token: " << token.getValue() << ", Type: ";
        switch (token.getType())
        {
        case TokenType::Number:
            cout << "Number";
            break;
        case TokenType::Identifier:
            cout << "Identifier";
            break;
        case TokenType::Keyword:
            cout << "Keyword";
            break;
        case TokenType::Literal:
            cout << "Literal";
            break;
        case TokenType::Operator:
            cout << "Operator";
            break;
        case TokenType::Separator:
            cout << "Separator";
            break;
        case TokenType::Comment:
            cout << "Comment";
            break;
        case TokenType::Whitespace:
            cout << "Whitespace";
            break;
        case TokenType::EndOfFile:
            cout << "EndOfFile";
            break;
        }
        cout << endl;
    }

    return 0;
}