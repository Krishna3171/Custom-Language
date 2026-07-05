#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Token.h"

//------------------------------------------------------
// Base Node
//------------------------------------------------------

enum class NodeType
{
    // Statements
    ExpressionStmt,
    VarDeclStmt,
    BlockStmt,
    IfStmt,
    WhileStmt,
    ForStmt,
    ReturnStmt,
    FunctionDeclStmt,

    // Expressions
    LiteralExpr,
    VariableExpr,
    BinaryExpr,
    UnaryExpr,
    AssignExpr,
    CallExpr
};

class Node
{
public:
    explicit Node(NodeType kind);
    virtual ~Node();

    NodeType getKind() const;
private:
    NodeType kind;
};

//------------------------------------------------------
// Base Statement / Expression
//------------------------------------------------------

class Stmt : public Node
{
public:
    explicit Stmt(NodeType kind);
    virtual ~Stmt();
};

class Expr : public Node
{
public:
    explicit Expr(NodeType kind);
    virtual ~Expr();
};

using ExprPtr = std::unique_ptr<Expr>;
using StmtPtr = std::unique_ptr<Stmt>;

//------------------------------------------------------
// Expressions
//------------------------------------------------------
enum class LiteralType
{
    Integer,
    Float,
    String,
    Boolean,
    Null
};

class LiteralExpr : public Expr
{
public:
    explicit LiteralExpr(LiteralType type, std::string value);

    LiteralType literaltype;
    std::string value;
};

class VariableExpr : public Expr
{
public:
    explicit VariableExpr(Token name);

    Token name;
};

class UnaryExpr : public Expr
{
public:
    UnaryExpr(
        Token op,
        ExprPtr operand);

    Token op;
    ExprPtr operand;
};

class BinaryExpr : public Expr
{
public:
    BinaryExpr(
        ExprPtr left,
        Token op,
        ExprPtr right);

    ExprPtr left;
    Token op;
    ExprPtr right;
};

class AssignExpr : public Expr
{
public:
    AssignExpr(
        Token variable,
        ExprPtr value);

    Token variable;
    ExprPtr value;
};

class CallExpr : public Expr
{
public:
    CallExpr(
        ExprPtr callee,
        std::vector<ExprPtr> arguments);

    ExprPtr callee;
    std::vector<ExprPtr> arguments;
};

//------------------------------------------------------
// Statements
//------------------------------------------------------

class ExpressionStmt : public Stmt
{
public:
    explicit ExpressionStmt(ExprPtr expression);

    ExprPtr expression;
};

class VarDeclStmt : public Stmt
{
public:
    VarDeclStmt(
        Token type,
        Token name,
        ExprPtr initializer);

    Token type;
    Token name;
    ExprPtr initializer;
};

class BlockStmt : public Stmt
{
public:
    BlockStmt();

    std::vector<StmtPtr> statements;
};

class IfStmt : public Stmt
{
public:
    IfStmt(
        ExprPtr condition,
        StmtPtr thenBranch,
        StmtPtr elseBranch);

    ExprPtr condition;
    StmtPtr thenBranch;
    StmtPtr elseBranch;
};

class WhileStmt : public Stmt
{
public:
    WhileStmt(
        ExprPtr condition,
        StmtPtr body);

    ExprPtr condition;
    StmtPtr body;
};

class ForStmt : public Stmt
{
public:
    ForStmt(
        StmtPtr initializer,
        ExprPtr condition,
        ExprPtr increment,
        StmtPtr body);

    StmtPtr initializer;
    ExprPtr condition;
    ExprPtr increment;
    StmtPtr body;
};

class ReturnStmt : public Stmt
{
public:
    explicit ReturnStmt(ExprPtr value);

    ExprPtr value;
};

struct Parameter
{
    Token type;
    Token name;
};

class FunctionDeclStmt : public Stmt
{
public:
    FunctionDeclStmt(
        Token returnType,
        Token functionName,
        std::vector<Parameter> parameters,
        std::unique_ptr<BlockStmt> body);

    Token returnType;
    Token functionName;

    std::vector<Parameter> parameters;

    std::unique_ptr<BlockStmt> body;
};

//------------------------------------------------------
// Root Program
//------------------------------------------------------

class Program
{
public:
    Program() = default;

    std::vector<StmtPtr> statements;
};