#pragma once

#include <string>
#include <vector>

enum class TokenType      {
    Number,     
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulo,
    LeftParen,
    RightParen,
    End,
    Invalid
};

struct Token
{
    TokenType type;
    std::string text;
};
std::vector<Token> tokenize(std::string input);
