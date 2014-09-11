#ifndef H_PUSHHANDLER
#define H_PUSHHANDLER

#include <string>
#include <vector>


#define API_TOKEN "1234" // change this line

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
		int id;
		std::string model;
	} Device;


	std::string login(std::string password);
	std::vector<Device> getDevices();
	void sendToDevice(int deviceID, std::string message);
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

