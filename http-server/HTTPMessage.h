#pragma once
#include <string>
#include <utility>
#include <unordered_map>

static constexpr char HTTP_VERSION[] = "HTTP/1.1";


class HTTPMessage
{
public:

	HTTPMessage() = default;
	HTTPMessage(const std::string& start_line, const std::unordered_map<std::string, std::string>& headers, const std::string& body) : 
		m_startline(start_line),
		m_headers(headers),
		m_body(body) {};


	std::string to_string();

	// Getters
	std::string get_startline() const { return m_startline; }
	std::string get_header(const std::string& header) const { return m_headers.at(header); }
	std::string get_body() const { return m_body; }

protected:

	std::string m_startline;
	std::unordered_map<std::string, std::string> m_headers;
	std::string m_body;
};

