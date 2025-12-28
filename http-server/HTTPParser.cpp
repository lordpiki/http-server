#include "HTTPParser.h"

#include <sstream>
#include <iostream>

HTTPMessage HTTPParser::parse(const std::string& message)
{
    /*
    Split the message into 3 sections:
    
    Start line
    Headers
    Body
    */

    std::string start_line;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    std::string stripped_message = replace_crlf(message);

    std::stringstream ss(stripped_message);

    // First line is the start line
    std::getline(ss, start_line, '\n');

    std::string line;

    // Getting headers until there is a new line
    while (std::getline(ss, line, '\n') and "\n" != line and not line.empty())
    {
        headers.insert(parse_header(line));
    }

    // Leftover is the body
    std::getline(ss, body);

    return HTTPMessage(start_line, headers, body);
}

std::pair<std::string, std::string> HTTPParser::parse_header(const std::string& line)
{
    std::stringstream ss(line);

    std::string key;
    std::string value;

    std::getline(ss, key, ':');

    // If ':' was not found, getline consumed entire line and hit EOF
    if (ss.eof()) {
        throw HTTPException(
            400,  // Bad Request
            "Malformed HTTP header: missing ':' delimiter in line " + line
        );
    }

    std::getline(ss, value);

    trim(key);
    trim(value);

    if (key.empty()) {
        throw HTTPException(
            400,
            "Malformed HTTP header: empty header name"
        );
    }

    return {key, value};
}

std::string HTTPParser::trim(const std::string& s)
{
    size_t start = 0;
    while (start < s.size() &&
        std::isspace(static_cast<unsigned char>(s[start])))
        ++start;

    size_t end = s.size();
    while (end > start &&
        std::isspace(static_cast<unsigned char>(s[end - 1])))
        --end;

    return s.substr(start, end - start);
}

std::string HTTPParser::replace_crlf(const std::string& s)
{
    std::string fixed = s;

    for (std::size_t pos = 0;
        (pos = fixed.find("\r\n", pos)) != std::string::npos;
        ++pos)
    {
        fixed.replace(pos, 2, "\n");
    }
    
    return fixed;
}
