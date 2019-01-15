#ifndef CORE_CLIENT_RESTREQUESTERMOCK_H
#define CORE_CLIENT_RESTREQUESTERMOCK_H

#include <gmock/gmock.h>
#include "../irestrequester.h"

class CRestRequesterMock : public IRestRequester
{
public:
    CRestRequesterMock(){};

    MOCK_CONST_METHOD1(GetRequest, CRestResponse(const std::string& getUrl));
    MOCK_CONST_METHOD1(GetBinaryRequest, CRestResponse(const std::string& getUrl));
};

#endif //CORE_CLIENT_RESTREQUESTERMOCK_H
