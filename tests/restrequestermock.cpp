#include "restrequestermock.h"

CRestRequesterMock::CRestRequesterMock(const CRestResponse& getRequest,
                                        const CRestResponse& getBinaryRequest) :
    _getRequest(getRequest),
    _getBinaryRequest(getBinaryRequest)
{

}

CRestRequesterMock::~CRestRequesterMock()
{
}

CRestResponse  CRestRequesterMock::GetRequest(const std::string& getUrl) const
{
    return _getRequest;
}

CRestResponse CRestRequesterMock::GetBinaryRequest(const std::string& getUrl) const
{
    return _getBinaryRequest;
}
