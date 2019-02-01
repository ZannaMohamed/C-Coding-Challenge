
#include "Parser.hpp"

using namespace arithmetic_expression_evaluator;


/////////////////////////////////////////////////////////////////////////
/// @brief function to get the priority of the operator (*/ >> +-)
/// @param operation [in] : the operator (+-*/)
/// @param priority [out] : the output priority of the operator
///
int Parser::getPriority( char operation)
{
    switch (operation)
    {
    case '+':
    case '-':
        return 1;

    case '/':
    case '*':
        return 2;

    default:
        return 0;
    }
}


/////////////////////////////////////////////////////////////////////////
/// @brief function to parse the arithmetic expression into a tree
/// @param arithmetic_expression [in] : the arithmetic expression
/// @param expressionNode [out] : the output arithmetic expression Node
///
void  Parser::parse(ExpressionNode &expressionNode,std::string& arithmetic_expression)
{

    std::istringstream inputExpressionStream(arithmetic_expression);
    char token;
    int priority;

    while (inputExpressionStream >> token)
    {
        switch (token)
        {

        case '+':
        case '-':
        case '*':
        case '/':
            priority = getPriority(token);

            while ((!m_operatorLifoStack.empty()) && (priority <= getPriority(
                                                          m_operatorLifoStack.top())))
            {

                this->addNewNode();
                m_operatorLifoStack.pop();
            }

            m_operatorLifoStack.push(token);

            break;

        case ')':
            while (!m_operatorLifoStack.empty() && m_operatorLifoStack.top() != '(')
            {

                this->addNewNode();
                m_operatorLifoStack.pop();
            }

            m_operatorLifoStack.pop();
            break;

        case '(':
            m_operatorLifoStack.push(token);

            break;

        default:

            inputExpressionStream.putback(token);
            double number;

            inputExpressionStream >> number;

            intNode *newNode = new intNode(number);
            m_operandLifoStack.push(newNode);

            continue;
        }
    }


    while (!m_operatorLifoStack.empty())
    {
        this->addNewNode();
        m_operatorLifoStack.pop();
    }



    Node *p = m_operandLifoStack.top();

    expressionNode =  static_cast<ExpressionNode& > (*p);
}

/////////////////////////////////////////////////////////////////////////
/// @brief function to add a new expression node in tree
///
void Parser::addNewNode()
{
    Node *right = m_operandLifoStack.top();

    m_operandLifoStack.pop();

    Node *left = m_operandLifoStack.top();

    m_operandLifoStack.pop();

    ExpressionNode *p = new ExpressionNode(m_operatorLifoStack.top(), left,
                                           right);

    m_operandLifoStack.push(p);
}

void Parser::checkFormat(const std::string& expression)
throw (FormatNotAllowed)
{
    std::regex r("^[0-9+*-/^()., ]+$");

    if (!std::regex_match(expression, r) ){
        std::cout << "format incorrect" << std::endl;
        throw FormatNotAllowed();
    }


}
