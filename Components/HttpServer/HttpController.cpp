

#include "HttpController.hpp"

#include <microhttpd.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////
/// @brief HttpController construtor
///
HttpController::HttpController()
{

}
/////////////////////////////////////////////////////////////////////////
/// @brief HttpController distrutor
///
HttpController::~HttpController()
{

}
/////////////////////////////////////////////////////////////////////////
/// @brief handle the client Request.
/// @param connection [in] :  the connection identifying the client
/// @param url [in] : the URL requested by the client;
/// @param method [in] : the HTTP method used by the client (GET, PUT, DELETE, POST, etc.);
/// @param upload_data [in] : the data being uploaded (excluding headers)
/// @param upload_data_size [in] : set initially to the size of the upload_data provided
///
int HttpController::handleRequest(struct MHD_Connection* connection,
                                const char* url, const char* method, const char* upload_data,
                                size_t* upload_data_size)
{
    std::stringstream response_string;
    // this->createResponce(connection, url, method, upload_data, upload_data_size, response_string);

    response_string << "";
    //Send the  response.
    struct MHD_Response * response = MHD_create_response_from_buffer(strlen(response_string.str().c_str()),
                                                                      (void*)response_string.str().c_str(), MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}
