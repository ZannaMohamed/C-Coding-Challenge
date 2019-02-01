
#ifndef __EXPRESSION_NODE__
#define __EXPRESSION_NODE__

#include "IntNode.hpp"

#include <iostream>

namespace arithmetic_expression_evaluator {



class ExpressionNode : public Node {

public :
    char m_operator; /*!< the operator (+,-,*,/)  */
    Node *m_left; /*!< the left children node   */
    Node *m_right; /*!< the right children node   */

    /////////////////////////////////////////////////////////////////////////
    /// @brief  A constructor
    ///
    ExpressionNode(){}

    /////////////////////////////////////////////////////////////////////////
    /// @brief  A constructor with paramaeters
    /// @param op [in] : the operator (+,-,*,/)
    /// @param left [in] : left children node
    /// @param right [in] : right children node
    ///
    ExpressionNode(char op, Node *left,
                   Node *right);

    /////////////////////////////////////////////////////////////////////////
    /// @brief  A virtual function to calculate the mathematic expression
    /// @param result [out] : the output result of the operation
    ///
    virtual void calculate(int &result);


};

}

#endif


