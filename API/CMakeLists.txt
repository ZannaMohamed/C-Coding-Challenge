# Specify all library source files
# -----------------------------------------------------------------------------

set(API_SRC
    ArithmeticExpresionEvaluatorApi.hpp
    ArithmeticExpresionEvaluatorApi.cpp
)


# Specifiy target
# -----------------------------------------------------------------------------
add_library(lapi STATIC ${API_SRC})
target_link_libraries(lapi   lCommon microhttpd ${JSONCPP_LIBRARY} -lcurl)
