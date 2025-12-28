#include "HTTPGetRequest.h"
#include "HTTPException.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> // C++17/C++20 feature

HTTPResponse HTTPGetRequest::handle()
{
    

    std::string target;
    std::string optional_query;


    std::stringstream ss(m_request_target);

    std::getline(ss, target, '?');
    std::getline(ss, optional_query);

    target = target.substr(1);

    // Open in binary mode
    std::ifstream file(target, std::ios::binary);

    // Strip the '/'

    if (!file.is_open()) {
        throw HTTPException(
            404,
            "File not found"
        );
    }

    // Get file size
    size_t size = std::filesystem::file_size(target);
    std::string content(size, '\0'); // Resize string and pre-allocate memory

    // Read the entire file into the pre-allocated buffer
    file.read(content.data(), size);


    return HTTPResponse(content);
}
