#ifndef CRESTREQUESTERMOCK_H
#define CRESTREQUESTERMOCK_H

#include "../irestrequester.h"

class CRestRequesterMock :public IRestRequester
{
public:
    CRestRequesterMock(const CRestResponse& getRequest,
                       const CRestResponse& getBinaryRequest);
    virtual ~CRestRequesterMock() override;

    CRestResponse GetRequest(const std::string& getUrl) const override;
    CRestResponse GetBinaryRequest(const std::string& getUrl) const override;

private:
    CRestResponse _getRequest;
    CRestResponse _getBinaryRequest;
};

#endif //CRESTREQUESTERMOCK_H
