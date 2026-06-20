#include <iostream>
#include <string>

#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"

int main()
{
    std::string input;

    while (true)
    {
        std::cout << "expr> ";

        std::getline(std::cin, input);

        if (input == "/quit")
        {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        try
        {
            auto tokens = tokenize(input);

            Parser parser(tokens);

            auto ast = parser.parse();

            int result = evaluate(ast.get());

            std::cout << "Result: " << result << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}