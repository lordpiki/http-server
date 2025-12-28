#pragma once
#include "HTTPRequest.h"

class HTTPGetRequest :
    public HTTPRequest
{
public:
    HTTPGetRequest(const HTTPMessage& message, const std::string& request_target) : HTTPRequest(message, request_target) {};

    virtual HTTPResponse handle();

};

