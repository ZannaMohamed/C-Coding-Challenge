

#ifndef __HTTP_CONTROLLER__
#define __HTTP_CONTROLLER__

#include <iostream>

class HttpController {
public:

    /////////////////////////////////////////////////////////////////////////
	/// @brief HttpController construtor
	///
    HttpController();

    /////////////////////////////////////////////////////////////////////////
	/// @brief HttpController distrutor
	///
    virtual ~HttpController();

    /////////////////////////////////////////////////////////////////////////
	/// @brief verifie if url is valid or not
	/// @param url [in] : request url
    /// @param method [in] : the HTTP method used by the client (GET, PUT, DELETE, POST, etc.); 
	/// @return bool responce
	///
    virtual bool isUrlValid(const char* url ,const char*  method) = 0;

    /////////////////////////////////////////////////////////////////////////
	/// @brief define http response.
	/// @param connection [in] : the connection identifying the client
    /// @param url [in] : the URL requested by the client; 
	/// @param method [in] : the HTTP method used by the client (GET, PUT, DELETE, POST, etc.); 
    /// @param upload_data [in] : the data being uploaded (excluding headers)
	/// @param upload_data_size [in] : set initially to the size of the upload_data provided
    /// @param responce [in] : response to transmit. 
	///
    virtual void createResponce(struct MHD_Connection* connection,
                            const char* url, const char* method, const char* upload_data,
                            size_t* upload_data_size, std::stringstream& responce) = 0;

    /////////////////////////////////////////////////////////////////////////
	/// @brief handle the client Request.
	/// @param connection [in] :  the connection identifying the client
    /// @param url [in] : the URL requested by the client; 
	/// @param method [in] : the HTTP method used by the client (GET, PUT, DELETE, POST, etc.); 
    /// @param upload_data [in] : the data being uploaded (excluding headers)
	/// @param upload_data_size [in] : set initially to the size of the upload_data provided
	///
    virtual int handleRequest(struct MHD_Connection* connection,
                                const char* url, const char* method, const char* upload_data,
                                size_t* upload_data_size);

    /////////////////////////////////////////////////////////////////////////
    /// @brief  parse the json buffer
    ///
    /// @param jsonBuffer  [in]: the json buffer
    /// @param urlList     [out]: the list of the url
    /// @param vehiculeId [out] : the vehicule id
    ///
    /// @return true or false
    ///
    virtual bool getDataFromJsonBuffer(const char* jsonBuffer) = 0;

};

#endif //  __HTTP_CONTROLLER_
