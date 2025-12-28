#include "HTTPResponse.h"

HTTPResponse::HTTPResponse(
    uint16_t status,
    const std::string& reason,
    const std::string& content,
    const std::unordered_map<std::string, std::string>& additional_headers 
)
    : HTTPMessage(

    // startline: version status reason
    "HTTP/1.1 " + std::to_string(status) + " " + reason,

    // headers: at least Content-Length and Content-Type
    {
        {"Content-Length", std::to_string(content.size())},
        {"Content-Type", "text/html"}, // Currently only supporting text/html
        {"Connection", "keep-alive"} // Currently only supporting 
    },

    // body
    content

) 
{
    // Additional headers will override existing headers if overlapping
    for (const auto& pair : additional_headers)
    {
        m_headers.insert(pair);
    }
}