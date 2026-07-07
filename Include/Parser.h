#pragma once

#include <vector>
#include <memory>

#include "Token.h"
#include "AST.h"

class Parser
{
public:
    explicit Parser(const std::vector<Token>& tokens);

    

    Program parse();

private:
    const std::vector<Token>& tokens;
    size_t current = 0;
};