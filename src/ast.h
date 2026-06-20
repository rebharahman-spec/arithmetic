#pragma once

#include <memory>
#include "tokenizer.h"

struct AstNode
{
    virtual ~AstNode() = default;    // base case for all AST nodes
};

struct NumberNode : AstNode  // represent number
{
    int value;

    NumberNode(int value)
        : value(value)
    {
    }
};

struct BinaryOpNode : AstNode    // to represent binary operators
{
    TokenType op;
    std::unique_ptr<AstNode> left;
    std::unique_ptr<AstNode> right;

    BinaryOpNode(
        TokenType op,
        std::unique_ptr<AstNode> left,
        std::unique_ptr<AstNode> right)
        : op(op),
          left(std::move(left)),
          right(std::move(right))
    {
    }
};
