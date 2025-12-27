#pragma once

#include <stdint.h>

#include "HTTPMessage.h"

class HTTPResponse : HTTPMessage
{

protected:
	uint16_t status;
};

