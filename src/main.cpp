/*
 * pusher
 * (c) 2014 Daniel Stein
 * github link..
 *
 * TODO
 * syslog
 * content type detection
 * gitignore of lines
 * secret input of password
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Boost
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

// own header files
#include "pushhandler.h"


#define CONFIG_FILE "/etc/pusher.conf"

// namespaces
using namespace std;
namespace po = boost::program_options;


// number of digit
unsigned int numDigits(int number)
{
	unsigned int digits = 0;
	while(number != 0) 
	{
		number /= 10;
		digits++;
	}
	return digits;
}


// main
int main(int argc, char **argv)
{

	po::options_description desc("Allowed options");
	
	desc.add_options()
		("help,h", "Print help message")
		("token,t", "Request your token")
		("list,l", "List of all your devices")
		("pipe,p", "Input via pipe")
	//	("quiet,q", "Outputs are redirected to syslog") // TODO
		("verify,v", "Checks if token is still valid")
		("id,i", po::value<int>(), "Specify device ID");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);

	try
	{
		string message;
		int id;


		// help
		if(vm.count("help"))
		{
			cout << desc << endl;
			return 0;
		}


		// request token
		if(vm.count("token"))
		{
			//request token
			string username, password, token;
			
			cout << "Username: ";
			cin >> username;

			cout << "Password: ";
			cin >> password;

			PushHandler buf(username);
			token = buf.login(password);

			// generate config file
			stringstream conffile;
			conffile << boost::format("[pusher]\nusername=%1%\nappToken=%2%")
				% username
				% token;

			// attempt to save token
			ofstream dat_aus;
			dat_aus.open(CONFIG_FILE, ios_base::out);

			if(!dat_aus.is_open())
			{
				cout << "Try running pusher as root or save the following in " << CONFIG_FILE << "\n" << endl;
				cout << conffile.str() << endl;
				return 1;
			}

			// save
			dat_aus << conffile.str();
			dat_aus.close();

			return 0;
		}


		// load conf and check if token is specified
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini(CONFIG_FILE, pt);
		string username = pt.get<std::string>("pusher.username");
		string appToken = pt.get<std::string>("pusher.appToken");


		// loading values
		PushHandler pusherInstance(username, appToken);


		// verify token
		if(vm.count("verify"))
		{
			if(pusherInstance.verifyToken())
			{
				cout << "appToken is valid" << endl;
				return 0;
			}
			else
			{
				cout << "appToken is invalid" << endl;
				return 1;
			}
		}


		// list devices
		if(vm.count("list"))
		{
			vector<PushHandler::Device> devices;
			devices = pusherInstance.getDevices();

			unsigned int titleLength = 5;
			unsigned int modelLength = 5;
			unsigned int idLength = 2;

			for(unsigned int i = 0; i < devices.size(); i++)
			{
				if(devices[i].title.length() > titleLength) { titleLength = devices[i].title.length(); }
				if(devices[i].model.length() > modelLength) { modelLength = devices[i].model.length(); }
				if(numDigits(devices[i].id) > idLength) { idLength = numDigits(devices[i].id); }
			}

			cout 
				<< "ID\033[" << (idLength - 2 + 2) << "C"
				<< "Title\033[" << (titleLength - 5 + 2) << "C"
				<< "Model" << endl;

			for(unsigned int x = 0; x < (titleLength + modelLength + idLength + 4); x++) { cout << "-"; }
			cout << endl;

			for(unsigned int i = 0; i < devices.size(); i++)
			{
				cout 
					<< devices[i].id << "\033[" << (idLength - numDigits(devices[i].id) + 2) << "C"
					<< devices[i].title << "\033[" << (titleLength - devices[i].title.length() + 2) << "C" 
					<< devices[i].model << endl;
			}

			return 0;
		}


		// device id
		if(vm.count("id"))
		{
			id = vm["id"].as<int>();
		}
		else
		{
			cout << desc << endl;
			return 1;
		}


		// load message
		if(vm.count("pipe"))
		{
			while(cin >> message) {};
		}
		else
		{
			stringstream lastArgument;
			lastArgument << argv[argc-1];

			message = lastArgument.str();
		}


		// send the message
		pusherInstance.sendToDevice(id, message);
	}


	/* ERROR HANDLING */


	// errors thrown by pushhandler
	catch(PusherError& e)
	{
		cout << "Error: " << e.what() << endl;
	}


	// boos ptree 
	catch(const boost::property_tree::ptree_error &e)
	{
		cout << "Maybe you need to request your appToken first?\n" << endl;
		cout << e.what() << "\n" << desc << endl;
	}


	// other errors
	catch(exception& e)
	{
		cout << "Some kind of error occured: " << e.what() << endl;
	}

	return 0;
}
