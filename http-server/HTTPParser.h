#pragma once

#include <string>
#include "HTTPMessage.h"
#include "HTTPException.h"

class HTTPParser
{
public:
	static HTTPMessage parse(const std::string& message);
	static std::pair<std::string, std::string> parse_header(const std::string& line);
	static std::string trim(const std::string& s);

};

