#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Lexer.h"

using namespace std;

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
    explicit Node(NodeType kind) : kind(kind) {}
    virtual ~Node() = default;

    NodeType kind;
};

//------------------------------------------------------
// Base Statement / Expression
//------------------------------------------------------

class Stmt : public Node
{
public:
    explicit Stmt(NodeType kind)
        : Node(kind)
    {
    }

    virtual ~Stmt() = default;
};

class Expr : public Node
{
public:
    explicit Expr(NodeType kind)
        : Node(kind)
    {
    }

    virtual ~Expr() = default;
};

using ExprPtr = unique_ptr<Expr>;
using StmtPtr = unique_ptr<Stmt>;

//------------------------------------------------------
// Expressions
//------------------------------------------------------

class LiteralExpr : public Expr
{
public:
    string value;

    explicit LiteralExpr(string value)
        : Expr(NodeType::LiteralExpr),
          value(move(value))
    {
    }
};

class VariableExpr : public Expr
{
public:
    string name;

    explicit VariableExpr(string name)
        : Expr(NodeType::VariableExpr),
          name(move(name))
    {
    }
};

class UnaryExpr : public Expr
{
public:
    Token op;
    ExprPtr operand;

    UnaryExpr(Token op, ExprPtr operand)
        : Expr(NodeType::UnaryExpr),
          op(move(op)),
          operand(move(operand))
    {
    }
};

class BinaryExpr : public Expr
{
public:
    ExprPtr left;
    Token op;
    ExprPtr right;

    BinaryExpr(
        ExprPtr left,
        Token op,
        ExprPtr right)
        : Expr(NodeType::BinaryExpr),
          left(move(left)),
          op(move(op)),
          right(move(right))
    {
    }
};

class AssignExpr : public Expr
{
public:
    string variable;
    ExprPtr value;

    AssignExpr(
        string variable,
        ExprPtr value)
        : Expr(NodeType::AssignExpr),
          variable(move(variable)),
          value(move(value))
    {
    }
};

class CallExpr : public Expr
{
public:
    ExprPtr callee;
    vector<ExprPtr> arguments;

    CallExpr(
        ExprPtr callee,
        vector<ExprPtr> arguments)
        : Expr(NodeType::CallExpr),
          callee(move(callee)),
          arguments(move(arguments))
    {
    }
};

//------------------------------------------------------
// Statements
//------------------------------------------------------

class ExpressionStmt : public Stmt
{
public:
    ExprPtr expression;

    explicit ExpressionStmt(ExprPtr expression)
        : Stmt(NodeType::ExpressionStmt),
          expression(move(expression))
    {
    }
};

class VarDeclStmt : public Stmt
{
public:
    string type;
    string name;
    ExprPtr initializer;

    VarDeclStmt(
        string type,
        string name,
        ExprPtr initializer)
        : Stmt(NodeType::VarDeclStmt),
          type(move(type)),
          name(move(name)),
          initializer(move(initializer))
    {
    }
};

class BlockStmt : public Stmt
{
public:
    vector<StmtPtr> statements;

    BlockStmt()
        : Stmt(NodeType::BlockStmt)
    {
    }
};

class IfStmt : public Stmt
{
public:
    ExprPtr condition;
    StmtPtr thenBranch;
    StmtPtr elseBranch;

    IfStmt(
        ExprPtr condition,
        StmtPtr thenBranch,
        StmtPtr elseBranch)
        : Stmt(NodeType::IfStmt),
          condition(move(condition)),
          thenBranch(move(thenBranch)),
          elseBranch(move(elseBranch))
    {
    }
};

class WhileStmt : public Stmt
{
public:
    ExprPtr condition;
    StmtPtr body;

    WhileStmt(
        ExprPtr condition,
        StmtPtr body)
        : Stmt(NodeType::WhileStmt),
          condition(move(condition)),
          body(move(body))
    {
    }
};

class ForStmt : public Stmt
{
public:
    StmtPtr initializer;
    ExprPtr condition;
    ExprPtr increment;
    StmtPtr body;

    ForStmt(
        StmtPtr initializer,
        ExprPtr condition,
        ExprPtr increment,
        StmtPtr body)
        : Stmt(NodeType::ForStmt),
          initializer(move(initializer)),
          condition(move(condition)),
          increment(move(increment)),
          body(move(body))
    {
    }
};

class ReturnStmt : public Stmt
{
public:
    ExprPtr value;

    explicit ReturnStmt(ExprPtr value)
        : Stmt(NodeType::ReturnStmt),
          value(move(value))
    {
    }
};

struct Parameter
{
    string type;
    string name;
};

class FunctionDeclStmt : public Stmt
{
public:
    string returnType;
    string functionName;

    vector<Parameter> parameters;

    unique_ptr<BlockStmt> body;

    FunctionDeclStmt(
        string returnType,
        string functionName,
        vector<Parameter> parameters,
        unique_ptr<BlockStmt> body)
        : Stmt(NodeType::FunctionDeclStmt),
          returnType(move(returnType)),
          functionName(move(functionName)),
          parameters(move(parameters)),
          body(move(body))
    {
    }
};

//------------------------------------------------------
// Root AST
//------------------------------------------------------

class Program
{
public:
    vector<StmtPtr> statements;
};
