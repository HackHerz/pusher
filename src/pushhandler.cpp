#include "pushhandler.h"
#include "json/json.hpp"
#include "curlhandler.h"

#include <sstream>
#include <algorithm>


using namespace std;
using json = nlohmann::json;


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
	requestData << "apiToken=" << API_TOKEN;
	requestData << "&username=" << this->username;
	requestData << "&password=" << password;

	// network request
	string readBuffer;
	readBuffer = CurlHandler::request(requestData.str(), URL_PN_LOGIN);

	// json parsing
	stringstream jsonData;
	jsonData << readBuffer;

	json j;
	j << jsonData;

	if(j["status"].get<string>() != "ok")
	{
		throw PusherError("wrong credentials");
	}

	this->appToken = j["appToken"].get<string>();
	return this->appToken;
}


// get list of devices
vector<PushHandler::Device> PushHandler::getDevices()
{
	// build request data
	stringstream requestData;
	requestData << "apiToken=" << API_TOKEN;
	requestData << "&appToken=" << this->appToken;

	// network request
	string readBuffer;
	readBuffer =CurlHandler::request(requestData.str(), URL_PN_GET_DEVICES);

	// json parsing
	stringstream jsonData;
	jsonData << readBuffer;

	json j;
	j << jsonData;

	// handle the codes
	switch(j["code"].get<int>())
	{
	case 1: throw PusherError("Invalid API Token");
	break;
	case 2: throw PusherError("App Token missing");
	break;
	case 3: throw PusherError("App Token invalid");
	}

	vector<Device> buffer;

	for(auto element : j["devices"])
	{
		Device buf;

		buf.title = element["title"].get<string>();
		buf.id = to_string(element["id"].get<int>());
		buf.model = element["model"].get<string>();

		buffer.push_back(buf);
	}

	return buffer;
}


// verify token
bool PushHandler::verifyToken()
{
	// build request data
	stringstream requestData;
	requestData << "apiToken=" << API_TOKEN;
	requestData << "&username=" << this->username;
	requestData << "&appToken=" << this->appToken;

	// network request
	string readBuffer;
	readBuffer = CurlHandler::request(requestData.str(), URL_PN_CHECK_TOKEN);

	// json parser
	stringstream jsonData;
	jsonData << readBuffer;

	json j;
	j << jsonData;

	switch(j["code"].get<int>())
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
void PushHandler::sendToDevice(string id, string message)
{
	// analyze content-type
	// ......


	// actual sending
	// build request data
	stringstream requestData;
	requestData << "apiToken=" << API_TOKEN;
	requestData << "&appToken=" << this->appToken;
	requestData << "&app=" << APP_PACKAGE;
	requestData << "&deviceID=" << id;
	requestData << "&type=" << "MESSAGE";
	requestData << "&content=" << CurlHandler::urlDecode(message);

	// network request
	string readBuffer;
	readBuffer = CurlHandler::request(requestData.str(), URL_PN_SEND_TO_DEVICE);

	// json parsing
	stringstream jsonData;
	jsonData << readBuffer;

	json j;
	j << jsonData;

	switch(j["code"].get<int>())
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
