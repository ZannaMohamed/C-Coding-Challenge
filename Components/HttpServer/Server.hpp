
#ifndef __SERVER__
#define __SERVER__

#include <iostream>
#include <vector>

#include "HttpController.hpp"
#include <memory>

#include <microhttpd.h>

struct postStatus {
    bool status;
    char *buffer;

};
class Server   {

public:

    Server(){}
    /////////////////////////////////////////////////////////////////////////
	/// @brief Http Server construtor
	/// @param port [in] : port to bind to
    ///
    Server(int port);

    /////////////////////////////////////////////////////////////////////////
	/// @brief add new httpcontroller to the List of controllers
	/// @param httpController [in] : http controller 
    ///
    void addHttpController( std::shared_ptr<HttpController> httpController);

    /////////////////////////////////////////////////////////////////////////
	/// @brief start the server
	/// 
    int start();


    ~Server(){
        if(this->daemon)
            free(this->daemon) ;
    }



private:

    /////////////////////////////////////////////////////////////////////////
	/// @brief callback to handle the client Request.
    /// @param cls [in] : custom value selected at callback registration time
	/// @param connection [in] :  the connection identifying the client
    /// @param url [in] : the URL requested by the client 
	/// @param method [in] : the HTTP method used by the client (GET, PUT, DELETE, POST, etc.)
    /// @param version [in] : the HTTP version string (i.e. HTTP/1.1) 
    /// @param upload_data [in] : the data being uploaded (excluding headers)
	/// @param upload_data_size [in] : set initially to the size of the upload_data provided
	///
    static int request_handler(void * cls, struct MHD_Connection * connection,
                                const char * url, const char * method, const char * version,
                                 const char * upload_data, size_t * upload_data_size, void ** ptr);

    ///////////////////////////////////////////////////////////////////////// 
	/// @brief port to bind to
	///
    ///  
    int port;
    
    ///////////////////////////////////////////////////////////////////////// 
	/// @brief  daemon that manages the connection
	///
    ///
    struct MHD_Daemon* daemon;

    ///////////////////////////////////////////////////////////////////////// 
	/// @brief  List of httpcontrollers this server has
	///
    ///
    std::vector<std::shared_ptr<HttpController>> HttpControllers;


};

#endif // __SERVER__
