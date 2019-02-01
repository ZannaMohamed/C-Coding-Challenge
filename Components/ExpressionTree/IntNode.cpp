


#include "IntNode.hpp"


using namespace arithmetic_expression_evaluator;


/////////////////////////////////////////////////////////////////////////
/// @brief  A constructor with paramaeters
/// @param val [in] : the value of the node
///
intNode::intNode(int val) :
    m_data(val)
{
}

/////////////////////////////////////////////////////////////////////////
/// @brief  A virtual function to calculate the mathematic expression
/// @param result [out] : the output result of the operation
///
void intNode::calculate(int &result)
{
    result =  m_data;
}
