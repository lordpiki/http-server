#pragma once
#include "HTTPMessage.h"
#include "HTTPResponse.h"

// Commented methods are not supported yet
enum HTTP_METHOD {
    GET,
    //POST,
    //PUT,
    //DELETE,
    OPTIONS,
    UNKNOWN
};

class HTTPRequest :
    public HTTPMessage
{
public:
    HTTPRequest(const HTTPMessage& message, const std::string& request_target) : HTTPMessage(message), m_request_target(request_target) {};

    virtual HTTPResponse handle() = 0;

protected:
    std::string m_request_target;

};

