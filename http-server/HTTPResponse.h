#pragma once

#include <stdint.h>
#include <string>

#include "HTTPMessage.h"

constexpr uint16_t DEFAULT_RESPONSE_STATUS = 200;
static constexpr char DEFAULT_RESPONSE_MESSAGE[] = "OK";


class HTTPResponse : public HTTPMessage
{
public:
	HTTPResponse() : HTTPResponse("") {};
	HTTPResponse(const std::string& content) : HTTPResponse(DEFAULT_RESPONSE_STATUS, DEFAULT_RESPONSE_MESSAGE, content) {};
	HTTPResponse(uint16_t status, const std::string& reason, const std::string& content, const std::unordered_map<std::string, std::string>& additional_headers = {});
};

