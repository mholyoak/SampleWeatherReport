#include "restresponse.h"

CRestResponse::CRestResponse()
{

}

CRestResponse::CRestResponse(int error, int code, std::string body) :
    _error(error),
    _code(code),
    _body(body)
{

}

bool CRestResponse::Success() const
{
    return _error == 0 && _code == 200;
}

int CRestResponse::GetError() const
{
    return _error;
}

int CRestResponse::GetCode() const
{
    return _code;
}

std::string CRestResponse::GetBody() const
{
    return _body;
}
