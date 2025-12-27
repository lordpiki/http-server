#include "HTTPMessage.h"
#include "HTTPParser.h"

std::string HTTPMessage::to_string()
{

    std::string message;
    
    message += m_start_line + '\n';

    for (const auto& header : m_headers)
    {
        message += header.first + ": " + header.second + '\n';
    }

    // Empty line to indicate finish of metadata
    message += '\n';

    message += m_body;

    return message;
}

