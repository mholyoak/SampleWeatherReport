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
    std::string response;
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        res = curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());

        res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &SaveToString);
        res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    return CRestResponse(0, res, response);
}
