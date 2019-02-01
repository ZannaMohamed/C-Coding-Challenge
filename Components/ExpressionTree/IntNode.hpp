#ifndef __INT_NODE__
#define __INT_NODE__



#include <iostream>
#include "Node.hpp"

namespace arithmetic_expression_evaluator {

class intNode : public Node
{
private:

    int m_data; /*!< the value of operande */

public:

    /////////////////////////////////////////////////////////////////////////
    /// @brief  A constructor with paramaeters
    /// @param val [in] : the value of the node
    ///
    intNode(int val);

    /////////////////////////////////////////////////////////////////////////
    /// @brief  A virtual function to calculate the mathematic expression
    /// @param result [out] : the output result of the operation
    ///
    virtual void calculate(int &result);

};

}

#endif
