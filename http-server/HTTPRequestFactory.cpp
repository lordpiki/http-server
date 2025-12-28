#include <sstream>
#include <iostream>

#include "HTTPRequestFactory.h"
#include "HTTPException.h"

std::unique_ptr<HTTPRequest> HTTPRequestFactory::get_request(const HTTPMessage& message)
{
    std::string method;
    std::string request_target;
    std::string version;

    std::stringstream ss(message.get_startline());

    std::getline(ss, method, ' ');
    std::getline(ss, request_target, ' ');
    std::getline(ss, version);

    if (HTTP_VERSION != version)
    {
        throw HTTPException(
            400,
            "Unsupported HTTP version"
        );
    }


    if ("GET" == method)
    {
        return std::make_unique<HTTPGetRequest>(message, request_target);
    }

    throw HTTPException(
        400,
        "Unsupported or invalid HTTP method"
    );
}
