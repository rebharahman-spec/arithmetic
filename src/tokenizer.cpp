#include "tokenizer.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

vector<Token> tokenize(string input)
{
    vector<Token> tokens;

    int position = 0;

    while (position < input.length())
    {
        char ch = input[position];

        // Number
        if (isdigit(ch))
        {
            int start = position;

            while (position < input.length() &&
                isdigit(input[position]))
            {
                position++;
            }

            string text =
                input.substr(start,
                    position - start);

            Token t;
            t.type = TokenType::Number;
            t.text = text;

            tokens.push_back(t);
        }

        // Plus
        else if (ch == '+')
        {
            Token t;
            t.type = TokenType::Plus;
            t.text = "+";

            tokens.push_back(t);

            position++;
        }

        // Minus
        else if (ch == '-')
        {
            Token t;
            t.type = TokenType::Minus;
            t.text = "-";

            tokens.push_back(t);

            position++;
        }

        // Multiply
        else if (ch == '*')
        {
            Token t;
            t.type = TokenType::Multiply;
            t.text = "*";

            tokens.push_back(t);

            position++;
        }

        // Divide
        else if (ch == '/')
        {
            Token t;
            t.type = TokenType::Divide;
            t.text = "/";

            tokens.push_back(t);

            position++;
        }

        // Modulo
        else if (ch == '%')
        {
            Token t;
			t.type = TokenType::Modulo;
            t.text = "%";

            tokens.push_back(t);

            position++;
        }

        // Left Parenthesis
        else if (ch == '(')
        {
            Token t;
            t.type = TokenType::LeftParen;
            t.text = "(";

            tokens.push_back(t);

            position++;
        }

        // Right Parenthesis
        else if (ch == ')')
        {
            Token t;
            t.type = TokenType::RightParen;
            t.text = ")";

            tokens.push_back(t);

            position++;
        }

        // Whitespace
        else if (isspace(ch))
        {
            position++;
        }

        // Invalid character
        else
        {
            Token t;
            t.type = TokenType::Invalid;
            t.text = string(1, ch);

            tokens.push_back(t);

            break;
        }
    }

    Token endToken;
    endToken.type = TokenType::End;
    endToken.text = "";

    tokens.push_back(endToken);

    return tokens;
}