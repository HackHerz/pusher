#ifndef H_PUSHHANDLER
#define H_PUSHHANDLER

#include <string>
#include <vector>

// Change this line if you are using your own API-Token
const char API_TOKEN[] = {
	0x38, 0x45, 0x37, 0x44, 0x38, 0x42, 0x32, 
	0x44, 0x44, 0x45, 0x37, 0x44, 0x44, 0x45,
	0x37, 0x44, 0x36, 0x43, 0x33, 0x56, 0x35,
	0x32, 0x56, 0x42, 0x35, 0x32, 0x56, 0x42,
	0x44, 0x34, 0x44, 0x44, 0x45, 0x54, 0x42,
	0x54, 0x54, 0x54, 0x4b, 0x46, 0x46, 0x42 };

#define APP_PACKAGE "com.hackherz.pusher"
#define USER_AGENT "pusher/0.2"

#define URL_PN_LOGIN "http://a.pushnotifier.de/1/login/"
#define URL_PN_CHECK_TOKEN "http://a.pushnotifier.de/1/checkToken/"
#define URL_PN_GET_DEVICES "http://a.pushnotifier.de/1/getDevices/"
#define URL_PN_SEND_TO_DEVICE "http://a.pushnotifier.de/1/sendToDevice/"



class PushHandler
{
public:
	PushHandler(std::string username);
	PushHandler(std::string username, std::string appToken);


	typedef struct
	{
		std::string title;
		std::string id;
		std::string model;
	} Device;


	std::string login(std::string password);
	std::vector<Device> getDevices();
	void sendToDevice(std::string deviceID, std::string message);
	bool verifyToken();


private:
	std::string username;
	std::string appToken;
};


// class for exceptions
class PusherError
{
public:
	PusherError(std::string content) { this->content = content; }
	std::string what() { return this->content; }
private:
	std::string content;
};


#endif

