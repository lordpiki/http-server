#pragma once
#include <string>
#include <utility>
#include <unordered_map>

class HTTPMessage
{
public:

	HTTPMessage(const std::string& start_line, const std::unordered_map<std::string, std::string>& headers, const std::string& body) : 
		m_startline(start_line),
		m_headers(headers),
		m_body(body) {};

	std::string to_string();

	// Getters
	std::string get_startline() { return m_startline; }
	std::string get_header(const std::string& header) { return m_headers[header]; }
	std::string get_body() { return m_body; }

protected:

	std::string m_startline;
	std::unordered_map<std::string, std::string> m_headers;
	std::string m_body;
};

