

#include "Server.hpp"
#include <microhttpd.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <cstddef>
#include <thread>
#include <memory>


/////////////////////////////////////////////////////////////////////////
/// @brief Http Server construtor
/// @param port [in] : port to bind to
///
Server::Server(int port)
{
    this->port = port;
    this->daemon = 0;

}

void Server:: addHttpController(std::shared_ptr<HttpController> httpController)
{
    HttpControllers.push_back(httpController);
}

int Server::start()
{

   daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
        this->port, NULL, NULL, &request_handler, this, MHD_OPTION_END); 
    if(!daemon)
        return 1;

    while(1){
        sleep(10000);
    }

    MHD_stop_daemon(daemon);
    return 0;
}

int Server::request_handler(void* cls, struct MHD_Connection* connection,
    const char* url, const char* method, const char* version,
    const char* upload_data, size_t* upload_data_size, void** ptr) 
    {
    struct postStatus *post = NULL ;
    Server* server = reinterpret_cast<Server*>(cls);

    

    int ind = -1;

    for(int i = 0; i < server->HttpControllers.size(); i++){

        if(server->HttpControllers.at(i)->isUrlValid(url, method)){
           ind = i;
            break;
        }
    }

    if(ind == -1){
        std::cout << "Path not found.\n";
        struct MHD_Response* response = MHD_create_response_from_buffer(0, 0, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response (connection, MHD_HTTP_NOT_FOUND, response);
    }else{
       
        post  = (struct postStatus*) *ptr;

        if( post == NULL) {
            post  = (struct postStatus * ) malloc( sizeof( struct postStatus));
            post->status = false;
            *ptr = post;
        }
    
        if (!post->status ){
            post->status = true;
            return MHD_YES;
        }else{
            if(*upload_data_size !=0){
                post->buffer = (char*) malloc(*upload_data_size + 1);
                snprintf(post->buffer,*upload_data_size+1,"%s",upload_data);
                *upload_data_size = 0;
                return MHD_YES;
            }else{
                if(!server->HttpControllers.at(ind)->getDataFromJsonBuffer(post->buffer)) {
                    std::cout << "Json Parser  error.\n";
                    struct MHD_Response* response = MHD_create_response_from_buffer(0,
                                                                                    NULL, MHD_RESPMEM_PERSISTENT);
                    return MHD_queue_response (connection, MHD_HTTP_BAD_REQUEST, response);
                    MHD_destroy_response(response);

                } else{

                    server->HttpControllers.at(ind)->handleRequest(connection, url, method, upload_data, upload_data_size);
                }

                free(post->buffer);

            }

        }

    }
    if( post != NULL) free(post);
    return 1;
}

