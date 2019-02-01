

#include <memory>
#include <string.h>
#include <sstream>
#include "ArithmeticExpresionEvaluatorApi.hpp"
#include <microhttpd.h>

/////////////////////////////////////////////////////////////////////////
/// @brief  parse the json buffer
///
/// @param jsonBuffer  [in]: the json buffer
/// @param urlList     [out]: the list of the url
/// @param vehiculeId [out] : the vehicule id
///
/// @return true or false
///
bool ArithmeticExpressionEvaluator::getDataFromJsonBuffer(const char *jsonBuffer)
{

    m_expressionList.clear();
    Json::Reader jsonReader;
    Json::Value jsonConfig;

    std::cout << jsonBuffer <<std::endl;

    if( !jsonReader.parse(jsonBuffer,jsonConfig))
    {
        std::cout << "Error in json parsing !";
        //        LOG(INFO) <<  "Error in json parsing !";
        return false;
    }

    if(!jsonConfig.isMember("Expressions") ) return false;

    for(auto expression : jsonConfig["Expressions"])
    {
        m_expressionList.push_back(expression.asString());
    }


    return true;


}
bool ArithmeticExpressionEvaluator::isUrlValid(const char* path, const char* method){

    if(strcmp(path, "/evaluator") == 0 && strcmp("POST", method) == 0){
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////
/// @brief handle the client Request.
/// @param connection [in] :  the connection identifying the client
/// @param url [in] : the URL requested by the client;
/// @param method [in] : the HTTP method used by the client (GET, PUT, DELETE, POST, etc.);
/// @param upload_data [in] : the data being uploaded (excluding headers)
/// @param upload_data_size [in] : set initially to the size of the upload_data provided
///
int ArithmeticExpressionEvaluator::handleRequest(struct MHD_Connection* connection,
                                                 const char* url, const char* method, const char* upload_data,
                                                 size_t* upload_data_size)
{
    std::stringstream response_string;
    // this->createResponce(connection, url, method, upload_data, upload_data_size, response_string);


    Json::Value jsonRootValue;
    Json::Value jsonResult;


    Json::Value jsonArray;



   int result;

    for(std::string expression : m_expressionList){

        m_parser->parse(m_root,expression);
        m_root.calculate(result);

        jsonResult["expression"] = expression;
        jsonResult["result"] = result;

        jsonArray.append(jsonResult);
    }
    jsonRootValue["result"] = jsonArray;

    response_string << jsonRootValue.toStyledString();
    struct MHD_Response * response = MHD_create_response_from_buffer(strlen(response_string.str().c_str()),
                                                                     (void*)response_string.str().c_str(), MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    jsonArray.clear();
    return ret;
}

void ArithmeticExpressionEvaluator::createResponce(struct MHD_Connection * connection,
                                                   const char * url, const char * method, const char * upload_data,
                                                   size_t * upload_data_size, std::stringstream& response){

    time_t time_cur;
    time(&time_cur);
    struct tm* time_now = localtime(&time_cur);
    response << "OK";
}
