#ifndef IRESTREQUESTER_H
#define IRESTREQUESTER_H

#include "restresponse.h"

class IRestRequester
{
public:
    virtual ~IRestRequester() {}

    virtual CRestResponse GetRequest(const std::string& getUrl) const = 0;

};

#endif // IRESTREQUESTER_H
