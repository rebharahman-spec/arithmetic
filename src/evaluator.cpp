#include "evaluator.h"
#include "ast.h"
 

#include <stdexcept>
int evaluate(const AstNode* node)
{
    // NumberNode
    if (auto number = dynamic_cast<const NumberNode*>(node))
    {
        return number->value;
    }

    // BinaryOpNode
    if (auto binary = dynamic_cast<const BinaryOpNode*>(node))
    {
        int leftValue = evaluate(binary->left.get());
        int rightValue = evaluate(binary->right.get());

        switch (binary->op)
        {
        case    TokenType::Plus:
            return leftValue + rightValue;

        case TokenType::Minus:
            return leftValue - rightValue;

        case TokenType::Multiply:
            return leftValue * rightValue;

        case TokenType::Divide:
            if (rightValue == 0)
            {
                throw std::runtime_error("RUNTIME ERROR:   \n Division by zero");
            }
            return leftValue / rightValue;

        case TokenType::Modulo:
            if (rightValue == 0)
            {
                throw std::runtime_error("RUNTIME ERROR:  \n Modulo by zero");
            }
            return leftValue % rightValue;

        default:
            throw std::runtime_error("Unknown operator");
        }
    }

    throw std::runtime_error("Unknown AST node");
}