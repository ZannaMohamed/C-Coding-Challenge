#include <iostream>

#include <memory>

#include "ExpressionTree/Parser.hpp"
#include "HttpServer/Server.hpp"
#include "API/ArithmeticExpresionEvaluatorApi.hpp"


int main(int argc, char** argv)
{


    std::shared_ptr<arithmetic_expression_evaluator::Parser> parser = std::make_shared<arithmetic_expression_evaluator::Parser>();
    arithmetic_expression_evaluator::ExpressionNode root ;

    if(argc > 1){ // run http server
        std::cout << " http server is running : port( "<< argv[1] <<")\n";

        std::shared_ptr<ArithmeticExpressionEvaluator> arithmeticExpressionEvaluator = std::make_shared<ArithmeticExpressionEvaluator>(parser,root);

        std::shared_ptr<Server> httpServer = std::make_shared<Server>(atoi(argv[1]));
        httpServer->addHttpController(arithmeticExpressionEvaluator);
        httpServer->start();
    } else {
           std::cout << " put in you Arithmetic Expression"  << '\n';

            std::string expression;
            getline(std::cin, expression);

            parser->checkFormat(expression);
            parser->parse(root,expression);

            int result;
            root.calculate(result);
            std::cout << " result = " << (result) << '\n';


    }




    return 0;
}
