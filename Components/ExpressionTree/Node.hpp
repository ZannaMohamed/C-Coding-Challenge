
#ifndef __NODE__
#define __NODE__

#include <iostream>
namespace arithmetic_expression_evaluator {

class Node
{
public:

    virtual ~Node () {} /*!< destructor is virtual then objects will be destrcuted in a order(firstly derived object then base ) */

    /////////////////////////////////////////////////////////////////////////
    /// @brief  A pure virtual function to calculate the mathematic expression
    /// @param result [out] : the output result of the operation
    ///
    virtual void calculate(int &result) = 0;


};

}
#endif
