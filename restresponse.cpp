#include "restresponse.h"

CRestResponse::CRestResponse()
{

}

CRestResponse::CRestResponse(bool success, int code, std::string body) :
    _success(success),
    _code(code),
    _body(body)
{

}

void CRestResponse::SetError(const char* errorMsg)
{
    _success = false;
    _errorMessage = errorMsg;
}


bool CRestResponse::RequestSuccess() const
{
    return _success && _code == 200;
}

bool CRestResponse::Success() const
{
    return _success;
}

int CRestResponse::GetCode() const
{
    return _code;
}

std::string CRestResponse::GetBody() const
{
    return _body;
}

std::string CRestResponse::GetErrorMessage() const
{
    return _errorMessage;
}

