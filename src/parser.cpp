#include "parser.h"
#include <string>
#include<memory>


#include <stdexcept>

// Constructor
Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0)
{ }



Token Parser::peek() const  // current token only
{
    return tokens[current];
}


Token Parser::advance()   // move to next token
{
	if (current < tokens.size())
	{
		return tokens[current++];
	}
	else
	{
		return Token{ TokenType::End, "" };
	}
}


// Checks whether current token matches expected type

void Parser::consume(TokenType expectedType)
{
    if (peek().type != expectedType)
    {
        throw std::runtime_error("Unexpected token");
    }

    advance();
}




std::unique_ptr<AstNode> Parser::parseFactor()      //parsefactor handles numbers and parentheses
{
   
    if (peek().type == TokenType::Number)
    {
        
		int value = std::stoi(peek().text);      //if token is a number create a NumberNode
        consume(TokenType::Number);
        return std::make_unique<NumberNode>(value);
    }

    // If current token is '('
    if (peek().type == TokenType::LeftParen)
    {
       
        consume(TokenType::LeftParen);       //if ( ,parse the expression inside parenthesis
        auto node = parseExpression();
        if (peek().type != TokenType::RightParen)
        {
            throw std::runtime_error(
                "SYNTAX ERROR: Missing closing parenthesis");
        }

        consume(TokenType::RightParen);

        return node;
    }


    throw std::runtime_error("SYNTAX ERROR: Expected operand");   //else syntax error 

}

std::unique_ptr<AstNode> Parser::parseTerm()      //parseTerm handles multiplication and division
{
	auto node = parseFactor();
	while (peek().type == TokenType::Multiply || peek().type == TokenType::Divide||peek().type == TokenType::Modulo){
		Token op = advance();
		auto right = parseFactor();
		node = std::make_unique<BinaryOpNode>(op.type, std::move(node), std::move(right));
	}
	return node;
}

std::unique_ptr<AstNode> Parser::parseExpression()  //parseExpression handles addition and subtraction
{
	auto node = parseTerm();
	while (peek().type == TokenType::Plus || peek().type == TokenType::Minus) {
		Token op = advance();
		auto right = parseTerm();
		node = std::make_unique<BinaryOpNode>(op.type, std::move(node), std::move(right));
	}
	return node;
}
std::unique_ptr<AstNode> Parser::parse()
{
    auto node = parseExpression();

    consume(TokenType::End);

    return node;
}