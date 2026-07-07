#include "D:\computer science\Custom Language\Include\ast.h"

#include <utility>

using std::move;

//------------------------------------------------------
// Base Node
//------------------------------------------------------

Node::Node(NodeType kind)
    : kind(kind)
{
}

Node::~Node() = default;

NodeType Node::getKind() const
{
    return kind;
}

//------------------------------------------------------
// Base Statement / Expression
//------------------------------------------------------

Stmt::Stmt(NodeType kind)
    : Node(kind)
{
}

Stmt::~Stmt() = default;

Expr::Expr(NodeType kind)
    : Node(kind)
{
}

Expr::~Expr() = default;

//------------------------------------------------------
// Expressions
//------------------------------------------------------

LiteralExpr::LiteralExpr(
    LiteralType literaltype,
    std::string value)
    : Expr(NodeType::LiteralExpr),
      literaltype(literaltype),
      value(move(value))
{
}

VariableExpr::VariableExpr(Token name)
    : Expr(NodeType::VariableExpr),
      name(move(name))
{
}

UnaryExpr::UnaryExpr(
    Token op,
    ExprPtr operand)
    : Expr(NodeType::UnaryExpr),
      op(move(op)),
      operand(move(operand))
{
}

BinaryExpr::BinaryExpr(
    ExprPtr left,
    Token op,
    ExprPtr right)
    : Expr(NodeType::BinaryExpr),
      left(move(left)),
      op(move(op)),
      right(move(right))
{
}

AssignExpr::AssignExpr(
    Token variable,
    ExprPtr value)
    : Expr(NodeType::AssignExpr),
      variable(move(variable)),
      value(move(value))
{
}

CallExpr::CallExpr(
    ExprPtr callee,
    std::vector<ExprPtr> arguments)
    : Expr(NodeType::CallExpr),
      callee(move(callee)),
      arguments(move(arguments))
{
}

//------------------------------------------------------
// Statements
//------------------------------------------------------

ExpressionStmt::ExpressionStmt(
    ExprPtr expression)
    : Stmt(NodeType::ExpressionStmt),
      expression(move(expression))
{
}

VarDeclStmt::VarDeclStmt(
    Token type,
    Token name,
    ExprPtr initializer)
    : Stmt(NodeType::VarDeclStmt),
      type(move(type)),
      name(move(name)),
      initializer(move(initializer))
{
}

BlockStmt::BlockStmt()
    : Stmt(NodeType::BlockStmt)
{
}

IfStmt::IfStmt(
    ExprPtr condition,
    StmtPtr thenBranch,
    StmtPtr elseBranch)
    : Stmt(NodeType::IfStmt),
      condition(move(condition)),
      thenBranch(move(thenBranch)),
      elseBranch(move(elseBranch))
{
}

WhileStmt::WhileStmt(
    ExprPtr condition,
    StmtPtr body)
    : Stmt(NodeType::WhileStmt),
      condition(move(condition)),
      body(move(body))
{
}

ForStmt::ForStmt(
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

ReturnStmt::ReturnStmt(
    ExprPtr value)
    : Stmt(NodeType::ReturnStmt),
      value(move(value))
{
}

FunctionDeclStmt::FunctionDeclStmt(
    Token returnType,
    Token functionName,
    std::vector<Parameter> parameters,
    std::unique_ptr<BlockStmt> body)
    : Stmt(NodeType::FunctionDeclStmt),
      returnType(move(returnType)),
      functionName(move(functionName)),
      parameters(move(parameters)),
      body(move(body))
{
}