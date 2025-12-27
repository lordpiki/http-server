#pragma once

#include <stdexcept>
#include <string>

class HTTPException: public std::runtime_error {
public:
    explicit HTTPException(int status, const std::string& message)
        : std::runtime_error(message), status_code(status) {}

    int status() const noexcept {
        return status_code;
    }

private:
    int status_code;
};
