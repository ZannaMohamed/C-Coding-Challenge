# Specify all library source files
# ----------------------------------------------------------------------------- 
set(HTTP_SERVER_SRC
    HttpController.hpp
    HttpController.cpp
    Server.hpp
    Server.cpp
)

# Specifiy target
# ----------------------------------------------------------------------------- 
add_library(lHttpServer STATIC ${HTTP_SERVER_SRC} )
target_link_libraries(lHttpServer  microhttpd  ${JSONCPP_LIBRARY}  )
