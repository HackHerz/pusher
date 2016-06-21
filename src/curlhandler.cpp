#include "curlhandler.h"

using namespace std;


// urlDecode matches
string matches[][2] = {
	{"$", "%24"},
	{"&", "%26"},
	{"+", "%2B"},
	{",", "%2C"},
	{"/", "%2F"},
	{":", "%3A"},
	{";", "%3B"},
	{"=", "%3D"},
	{"?", "%3F"},
	{"@", "%40"}
};



// needed for handling curl output
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


string CurlHandler::request(string data, const char* url)
{
	CURL *curl;
	CURLcode res;
	string readBuffer;
	curl = curl_easy_init();

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if(res != CURLE_OK)
		{
			//throw PusherError("Network Error");
		}
	}

	return readBuffer;
}


string CurlHandler::urlDecode(string url)
{

	for(unsigned int i = 0; i < (sizeof(matches)/sizeof(matches[0])); i++)
	{
		size_t start_pos = 0;
		while((start_pos = url.find(matches[i][0], start_pos)) != string::npos)
		{
			url.replace(start_pos, matches[i][0].length(), matches[i][1]);
			start_pos += matches[i][1].length();
		}
	}

	return url;
}
