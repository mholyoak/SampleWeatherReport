#ifndef RESTRESPONSE_H
#define RESTRESPONSE_H

#include <string>
#include <vector>

class CRestResponse
{
public:
    typedef std::vector<uint8_t> BinaryData;

    CRestResponse();
    CRestResponse(bool success, int code, std::string stringBody);
    CRestResponse(bool success, int code, BinaryData binaryBody);

    void        SetError(const char* errorMsg);

    bool        RequestSuccess() const;
    bool        Success() const;
    int         GetCode() const;
    std::string GetStringBody() const;
    BinaryData  GetBinaryBody() const;
    std::string GetErrorMessage() const;

private:
    bool        _success;
    int         _code;
    std::string _stringBody;
    BinaryData  _binaryBody;
    std::string _errorMessage;
};

#endif // RESTRESPONSE_H
