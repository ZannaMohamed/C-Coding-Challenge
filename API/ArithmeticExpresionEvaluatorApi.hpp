
#ifndef __ARITHMETIC_EXPRESSION_EVALUATOR__
#define __ARITHMETIC_EXPRESSION_EVALUATOR__

#include <iostream>
#include "HttpServer/HttpController.hpp"
#include "json/json.h"
#include "ExpressionTree/Parser.hpp"


class ArithmeticExpressionEvaluator : public HttpController
{
public:
    ArithmeticExpressionEvaluator(std::shared_ptr<arithmetic_expression_evaluator::Parser> parser ,
                                  arithmetic_expression_evaluator::ExpressionNode &root) : m_parser(parser),m_root(root){
        m_expressionList.clear();
    }


    virtual bool isUrlValid(const char* path, const char* method);

    virtual void createResponce(struct MHD_Connection * connection,
        const char * url, const char * method, const char * upload_data,
        size_t * upload_data_size, std::stringstream& response);



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



private:

    /////////////////////////////////////////////////////////////////////////
    /// @brief  parse the json buffer
    ///
    /// @param jsonBuffer  [in]: the json buffer
    /// @param urlList     [out]: the list of the url
    /// @param vehiculeId [out] : the vehicule id
    ///
    /// @return true or false
    ///
    virtual bool getDataFromJsonBuffer(const char* jsonBuffer);

    std::vector<std::string> m_expressionList;

    std::shared_ptr<arithmetic_expression_evaluator::Parser> m_parser;
    arithmetic_expression_evaluator::ExpressionNode& m_root;

};

#endif
