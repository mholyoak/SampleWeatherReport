#ifndef IRESTREQUESTER_H
#define IRESTREQUESTER_H

#include "restresponse.h"

// Interface for REST Requester
class IRestRequester
{
public:
    virtual ~IRestRequester() = default;

    // Json Get Request
    virtual CRestResponse GetRequest(const std::string& getUrl) const = 0;
    // Binary Get Request
    virtual CRestResponse GetBinaryRequest(const std::string& getUrl) const = 0;

};

#endif // IRESTREQUESTER_H
