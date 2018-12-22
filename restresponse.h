#ifndef RESTRESPONSE_H
#define RESTRESPONSE_H

#include <string>

class CRestResponse
{
public:
    CRestResponse();
    CRestResponse(bool success, int code, std::string body);

    void        SetError(const char* errorMsg);

    bool        RequestSuccess() const;
    bool        Success() const;
    int         GetCode() const;
    std::string GetBody() const;
    std::string GetErrorMessage() const;

private:
    bool        _success;
    int         _code;
    std::string _body;
    std::string _errorMessage;
};

#endif // RESTRESPONSE_H
