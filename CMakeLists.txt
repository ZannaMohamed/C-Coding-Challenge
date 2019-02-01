cmake_minimum_required(VERSION 2.8)
# -------------------------------------------------------------------
# Author : mohamed ZANNA
# Version : 1.0.0
# Date : 31/01/2019
#--------------------------------------------------------------------

project(cpp-coding-chalenge)

set(COMPONENT_NAME arithmetic-expression-evaluator)

set(CMAKE_C_COMPILER /usr/bin/gcc-4.9)
set(CMAKE_CXX_COMPILER /usr/bin/g++-5)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14")



#--------------------------------------------------------------------
#
# Find JSONCPP library on local system
#
#--------------------------------------------------------------------
find_library(JSONCPP_LIBRARY jsoncpp)
find_path(JSONCPP_INCLUDE_DIR json/json.h PATH_SUFFIXES jsoncpp)


#--------------------------------------------------------------------
#
# Find microhttpd
#
#--------------------------------------------------------------------

option(MICROHTTPD_ENABLE "Enable or disable the requirement of microhttp (http deamon)" ON)
if(MICROHTTPD_ENABLE)
    find_path(MTHD_INCLUDE_DIR
        NAMES
            microhttpd.h
        PATHS
            /opt/local
            /usr/local
            /usr
            ENV "PROGRAMFILES(X86)"
            ENV "HWLOC_ROOT"
        PATH_SUFFIXES
            include)

    find_library(MHTD
        NAMES
            microhttpd
            libmicrohttpd-dll
            libmicrohttpd.lib
        PATHS
            ENV "MICROHTTPD_ROOT"
        PATH_SUFFIXES
            lib)
    if("${MHTD}" STREQUAL "MHTD-NOTFOUND")
        message(FATAL_ERROR "microhttpd NOT found: use `-DMICROHTTPD_ENABLE=OFF` to build without http deamon support")
    else()
        set(LIBS ${LIBS} ${MHTD})
        include_directories(AFTER ${MTHD_INCLUDE_DIR})
    endif()
else()
    add_definitions("-DCONF_NO_HTTPD")
endif()



include_directories(
                    ${OpenCV_INCLUDE_DIRS}
                    ${CMAKE_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/Components
                    ${CMAKE_CURRENT_SOURCE_DIR}/Components/HttpServer
                    ${CMAKE_CURRENT_SOURCE_DIR}/API
                    ${GFLAGS_INCLUDE_DIRS}
                    ${JSONCPP_INCLUDE_DIR}
                   )

add_executable(${COMPONENT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)
target_link_libraries(${COMPONENT_NAME} ${JSONCPP_LIBRARY}   microhttpd lCommon lHttpServer lapi)

add_subdirectory(Components/ExpressionTree)
add_subdirectory(API)
add_subdirectory(Components/HttpServer)


# Include unit tests
# -------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE MATCHES "release")
	add_subdirectory(UnitTests)
endif()
