#pragma once

#include <vector>
#include <memory>

#include "tokenizer.h"
#include "ast.h"

class Parser
{
private:
    std::vector<Token> tokens;
    size_t current;

public:
    Parser(const std::vector<Token>& tokens);

    std::unique_ptr<AstNode> parse();

private:
    std::unique_ptr<AstNode> parseExpression();
    std::unique_ptr<AstNode> parseTerm();
    std::unique_ptr<AstNode> parseFactor();

    Token peek() const;
    Token advance();

    void consume(TokenType expectedType);
};