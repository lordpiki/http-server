#pragma once

#include "HTTPGetRequest.h"

class HTTPRequestFactory
{
public:
	HTTPRequestFactory() = delete;

	static std::unique_ptr<HTTPRequest> get_request(const HTTPMessage& message);

};

