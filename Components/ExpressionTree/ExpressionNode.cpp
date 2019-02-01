
#include "ExpressionNode.hpp"



using namespace arithmetic_expression_evaluator;

/////////////////////////////////////////////////////////////////////////
/// @brief  A constructor with paramaeters
/// @param op [in] : the operator (+,-,*,/)
/// @param left [in] : left children node
/// @param right [in] : right children node
///
ExpressionNode::ExpressionNode(char op,
        Node *l, Node *r) :
    m_operator(op), m_left(l), m_right(r)
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief  A virtual function to calculate the mathematic expression
/// @param result [out] : the output result of the operation
///
void ExpressionNode::calculate(int &result)
{
    int lVal = 0 ;
    m_left->calculate(lVal);

    int rVal = 0 ;
    m_right->calculate(rVal);


    switch (m_operator)
    {

        case '+':
            result = lVal + rVal;
            break;

        case '-':
            result = lVal - rVal;
            break;

        case '*':
            result = lVal * rVal;
            break;

        case '/':
            result = lVal / rVal;
            break;
    }

}
