#pragma once
#include "HTTPMessage.h"

// Commented methods are not supported yet
enum HTTP_METHOD {
    GET,
    POST,
    PUT,
    DELETE,
    OPTIONS,
    UNKNOWN
};

class HTTPRequest :
    public HTTPMessage
{
public:
    HTTPRequest(const HTTPMessage& message) : HTTPMessage(message) {};

//private:
//    HTTP_METHOD method;
//    std::string request_target;
//    std::string protocol;

};

