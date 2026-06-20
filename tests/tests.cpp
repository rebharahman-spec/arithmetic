#include <cassert>
#include <iostream>

#include "src/tokenizer.h"
#include "src/parser.h"
#include "src/evaluator.h"

void testEvaluate(const std::string& expr, int expected)
{
    auto tokens = tokenize(expr);

    Parser parser(tokens);

    auto ast = parser.parse();

    int result = evaluate(ast.get());

    assert(result == expected);
}

void testException(const std::string& expr)
{
    bool exceptionThrown = false;

    try
    {
        auto tokens = tokenize(expr);

        Parser parser(tokens);

        auto ast = parser.parse();

        evaluate(ast.get());
    }
    catch (...)
    {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
}

int main()
{
    // Evaluator Tests
    testEvaluate("10 + 20", 30);
    testEvaluate("10 - 3", 7);
    testEvaluate("10 * 5", 50);
    testEvaluate("20 / 4", 5);
    testEvaluate("20 % 3", 2);

    // Precedence Tests
    testEvaluate("10 + 20 * 3", 70);
    testEvaluate("(10 + 20) * 3", 90);
    testEvaluate("2 + 3 * 4 - 5", 9);

    // Parentheses Tests
    testEvaluate("((2 + 3) * 4)", 20);
    testEvaluate("((((10))))", 10);

    // Single Number
    testEvaluate("42", 42);
    testEvaluate("100", 100);

    // Error Handling Tests
    testException("10 + *");
    testException("(10 + 20");
    testException("10 / 0");
    testException("10 % 0");
    testException("10 + abc");
    testException("@");
    testException(")");
    testException("(");
    testException("10 +");

    std::cout << "All tests passed!" << std::endl;

    return 0;
}