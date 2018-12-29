#include "curlrestrequester.h"

#include <curl/curl.h>
#include <string>

CCurlRestRequester::CCurlRestRequester()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CCurlRestRequester::~CCurlRestRequester()
{
    curl_global_cleanup();
}


size_t SaveToString(void* buffer, size_t itemSize, size_t numItems, void* context)
{
    const char* data = reinterpret_cast<const char*>(buffer);
    size_t dataSize = itemSize * numItems;

    std::string& dest = *(reinterpret_cast<std::string*>(context));

    dest.append(data, dataSize);

    return dataSize;
}

CRestResponse CCurlRestRequester::GetRequest(const std::string& getUrl) const
{
    CRestResponse restResponse;
    std::string response;
    CURL *curl;

    curl = curl_easy_init();
    if (curl)
    {
        // TODO - The GetRequest and GetBinaryRequest are very similar and should be refactored to share code
        auto res = curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &SaveToString);
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        curl_easy_cleanup(curl);
    }

    // BUGBUG need to get response code from request
    return CRestResponse(true, 200, response);
}


size_t SaveToVector(void* buffer, size_t itemSize, size_t numItems, void* context)
{
    const char* data = reinterpret_cast<const char*>(buffer);
    size_t dataSize = itemSize * numItems;

    CRestResponse::BinaryData* dest = (reinterpret_cast<CRestResponse::BinaryData*>(context));

    size_t initialSize = dest->size();
    size_t copyDataSize = itemSize * numItems;
    dest->resize(initialSize + copyDataSize);

    memcpy(dest->data() + initialSize, data, copyDataSize);

    return dataSize;
}


CRestResponse CCurlRestRequester::GetBinaryRequest(const std::string& getUrl) const
{
    CRestResponse restResponse;
    CRestResponse::BinaryData response;
    CURL *curl;

    curl = curl_easy_init();
    if (curl)
    {
        // TODO - The GetRequest and GetBinaryRequest are very similar and should be refactored to share code
        auto res = curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &SaveToVector);
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            restResponse.SetError(curl_easy_strerror(res));
            return restResponse;
        }

        curl_easy_cleanup(curl);
    }

    // BUGBUG need to get response code from request
    return CRestResponse(true, 200, response);
}
