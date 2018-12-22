#ifndef RESTRESPONSE_H
#define RESTRESPONSE_H

#include <string>

class CRestResponse
{
public:
    CRestResponse();
    CRestResponse(int error, int code, std::string body);

    bool        Success() const;
    int         GetError() const;
    int         GetCode() const;
    std::string GetBody() const;

private:
    int         _error;
    int         _code;
    std::string _body;
};

#endif // RESTRESPONSE_H
