#ifndef __PARSER__
#define __PARSER__


#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <exception>
#include <regex>


#include "IntNode.hpp"
#include "ExpressionNode.hpp"

namespace arithmetic_expression_evaluator {

class Parser
{
    private:


        std::stack<char> m_operatorLifoStack; /*!< the operator stack */

        std::stack<Node *> m_operandLifoStack; /*!< the operand stack */


        /////////////////////////////////////////////////////////////////////////
        /// @brief function to add a new expression node in tree
        ///
        void addNewNode();

        /////////////////////////////////////////////////////////////////////////
        /// @brief function to get the priority of the operator (*/ >> +-)
        /// @param operation [in] : the operator (+-*/)
        /// @param priority [out] : the output priority of the operator
        ///
        int getPriority(char operation);

    public:

        /////////////////////////////////////////////////////////////////////////
        /// @brief function to parse the arithmetic expression into a tree
        /// @param arithmetic_expression [in] : the arithmetic expression
        /// @param expressionNode [out] : the output arithmetic expression Node
        ///
        void parse(ExpressionNode &expressionNode,std::string& arithmetic_expression);

        /////////////////////////////////////////////////////////////////////////
        /// @brief  A constructor
        ///
        Parser(){}


        class FormatNotAllowed: public std::exception
        {
            public:
                virtual const char* what() const throw (){
                    return "ERROR : The expression is not valid";
                }

        };

        void checkFormat(const std::string& expression) throw (FormatNotAllowed);
};

}
#endif
