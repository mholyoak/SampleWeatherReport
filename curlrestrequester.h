#ifndef CURLRESTREQUESTER_H
#define CURLRESTREQUESTER_H

#include "irestrequester.h"

// Curl implentation of the Rest requester interface
class CCurlRestRequester :public IRestRequester
{
public:
    CCurlRestRequester();
    virtual ~CCurlRestRequester() override;

    // Get request that returns Json
    CRestResponse GetRequest(const std::string& getUrl) const override;
    // Get request that return binary
    CRestResponse GetBinaryRequest(const std::string& getUrl) const override;
};

#endif // CURLRESTREQUESTER_H
