set(COMMON_SRC
    Node.hpp
    IntNode.hpp
    IntNode.cpp
    ExpressionNode.hpp
    ExpressionNode.cpp
    Parser.hpp
    Parser.cpp
)

# Specifiy target
# ----------------------------------------------------------------------------- 
add_library(lCommon STATIC ${COMMON_SRC} )
