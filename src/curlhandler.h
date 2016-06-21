#ifndef H_CURLHANDLER
#define H_CURLHANDLER

#include <curl/curl.h>
#include <string>

#define USER_AGENT "pusher/0.2"


class CurlHandler
{
public:
	static std::string request(std::string data, const char* url);
	static std::string urlDecode(std::string url);
};

#endif
