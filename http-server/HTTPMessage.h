#pragma once
#include <string>
#include <utility>
#include <unordered_map>

class HTTPMessage
{
public:

	HTTPMessage(const std::string& start_line, const std::unordered_map<std::string, std::string>& headers, const std::string& body) : 
		m_start_line(start_line),
		m_headers(headers),
		m_body(body) {};

	std::string to_string();

private:

	std::string m_start_line;
	std::unordered_map<std::string, std::string> m_headers;
	std::string m_body;
};

