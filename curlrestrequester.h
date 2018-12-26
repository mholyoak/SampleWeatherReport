#ifndef CURLRESTREQUESTER_H
#define CURLRESTREQUESTER_H

#include "irestrequester.h"

class CCurlRestRequester :public IRestRequester
{
public:
    CCurlRestRequester();
    virtual ~CCurlRestRequester() override;

    CRestResponse GetRequest(const std::string& getUrl) const override;
    CRestResponse GetBinaryRequest(const std::string& getUrl) const override;
};

#endif // CURLRESTREQUESTER_H
