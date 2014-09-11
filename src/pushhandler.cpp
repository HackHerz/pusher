#include "pushhandler.h"

#include <sstream>
#include <curl/curl.h>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

using namespace std;

// needed for handling curl output
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


// curl wrapper
string curlHandler(string data, const char* url)
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
			throw PusherError("Network Error");
		}
	}


	return readBuffer;
}


// constructor only username
PushHandler::PushHandler(string username)
{
	this->username = username;
}


// constructor with appToken
PushHandler::PushHandler(string username, string appToken)
{
	this->username = username;
	this->appToken = appToken;
}


// login
string PushHandler::login(string password)
{
	// build request data
	stringstream requestData;
	requestData << boost::format("apiToken=%1%&username=%2%&password=%3%") 
		% API_TOKEN 
		% this->username 
		% password;

	// network request
	string readBuffer;
	readBuffer = curlHandler(requestData.str(), URL_PN_LOGIN);

	// json parsing
	stringstream jsonData;
	jsonData << readBuffer;

	boost::property_tree::ptree pt;
	boost::property_tree::read_json(jsonData, pt);

	if(pt.get<string>("status") != "ok")
	{
		throw PusherError("wrong credentials");
	}

	this->appToken = pt.get<string>("appToken");
	return this->appToken;
}


// get list of devices
vector<PushHandler::Device> PushHandler::getDevices()
{
	// build request data
	stringstream requestData;
	requestData << boost::format("apiToken=%1%&appToken=%2%")
		% API_TOKEN
		% this->appToken;

	// network request
	string readBuffer;
	readBuffer = curlHandler(requestData.str(), URL_PN_GET_DEVICES);

	// json parsing
	stringstream jsonData;
	jsonData << readBuffer;

	boost::property_tree::ptree pt;
	boost::property_tree::read_json(jsonData, pt);

	// handle the codes
	switch(pt.get<int>("code"))
	{
	case 1: throw PusherError("Invalid API Token");
	break;
	case 2: throw PusherError("App Token missing");
	break;
	case 3: throw PusherError("App Token invalid");
	}

	vector<Device> buffer;

	 BOOST_FOREACH(boost::property_tree::ptree::value_type& v, pt.get_child("devices"))
	 {
	 	Device buf;

		buf.title = v.second.get<string>("title");
		buf.id = v.second.get<int>("id");
		buf.model = v.second.get<string>("model");
	
		buffer.push_back(buf);
	}

	return buffer;
}


// verify token
bool PushHandler::verifyToken()
{
	// build request data
	stringstream requestData;
	requestData << boost::format("apiToken=%1%&username=%2%&appToken=%3%")
		% API_TOKEN
		% this->username
		% this->appToken;

	// network request
	string readBuffer;
	readBuffer = curlHandler(requestData.str(), URL_PN_CHECK_TOKEN);

	// json parser
	stringstream jsonData;
	jsonData << readBuffer;

	boost::property_tree::ptree pt;
	boost::property_tree::read_json(jsonData, pt);


	switch(pt.get<int>("code"))
	{
	case 0: return true;
	break;
	case 1: throw PusherError("Invalid API-Token");
	break;
	case 2: return false;
	default: throw PusherError("Invalid server response");
	}
}


// send to device
void PushHandler::sendToDevice(int id, string message)
{
	// analyze content-type
	// ......


	// actual sending
	// build request data
	stringstream requestData;
	requestData << boost::format("apiToken=%1%&appToken=%2%&app=%3%&deviceID=%4%&type=%5%&content=%6%")
		% API_TOKEN
		% this->appToken
		% APP_PACKAGE
		% id
		% "MESSAGE"
		% message;

	// network request
	string readBuffer;
	readBuffer = curlHandler(requestData.str(), URL_PN_SEND_TO_DEVICE);

	// json parsing
	stringstream jsonData;
	jsonData << readBuffer;

	boost::property_tree::ptree pt;
	boost::property_tree::read_json(jsonData, pt);


	switch(pt.get<int>("id"))
	{
	case 0: //return 0;
	break;
	case 1: throw PusherError("Invalid API Token");
	break;
	case 2: throw PusherError("App Token missing");
	break;
	case 3: throw PusherError("App Token invalid");
	break;
	case 4: throw PusherError("Package Name missing");
	break;
	case 5: throw PusherError("Package Name invalid");
	break;
	case 6: throw PusherError("Package Name is not linked with the provided API Token");
	break;
	case 7: throw PusherError("Device ID missing");
	break;
	case 8: throw PusherError("Device ID invalid");
	break;
	case 9: throw PusherError("Type missing or invalid");
	break;
	default: throw PusherError("Invalid server response");
	}
}
