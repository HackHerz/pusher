/*
 * pusher
 * (c) 2014-2016 Daniel Stein
 * https://github.com/HackHerz/pusher
 *
 * TODO
 * syslog
 * content type detection
 * secret input of password
 */

#include <iostream>
#include <string>
#include <sstream>
#include <termios.h>
#include <unistd.h>

#include "tclap/CmdLine.h"
#include "simpleini/SimpleIni.h"
#include "pushhandler.h"

#define CONFIG_FILE "/etc/pusher.conf"

// namespaces
using namespace std;


void HideStdinKeystrokes()
{
	termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	tty.c_lflag &= ~ECHO; // Disable echo
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void ShowStdinKeystrokes()
{
	termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	tty.c_lflag |= ECHO; // enable echo
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// Main
int main(int argc, char **argv)
{
	// Check the number of command line arguments
	if(argc < 2)
	{
		cout << "Try " << argv[0] << " -h or --help" << endl;
		return 1;
	}

	try
	{
		TCLAP::CmdLine cmd("Push notifications to your phone easily.", ' ', "0.3");

		// Values
		TCLAP::ValueArg<int> idArg("i","id","ID of the device.",false,0,"number");
		cmd.add(idArg);

		// Switches
		TCLAP::SwitchArg tokenSwitch("t", "token", "Request your token.", cmd, false);
		TCLAP::SwitchArg listSwitch("l", "list", "List all your devices.", cmd, false);
		TCLAP::SwitchArg pipeSwitch("p", "pipe", "Input via pipe.", cmd, false);
		TCLAP::SwitchArg verifySwitch("v","verify","Checks if token is still valid.", cmd, false);


		// add unlabeled argument
		TCLAP::UnlabeledValueArg<string> noLabelMessage("message", "The notification you want to send.", false, "message", "message");
		cmd.add(noLabelMessage);


    	// Parse the argv array.
    	cmd.parse(argc, argv);


		// Variables
		string message;
		int id;
		CSimpleIniA iniReader;
		iniReader.SetUnicode();


		// Request token
		if(tokenSwitch.getValue())
		{
			string username, password, token;

			// Read username
			cout << "Username: ";
			cin >> username;

			cin.clear();
			cin.ignore(1024,'\n');

			// Read password
			cout << "Password: ";

			HideStdinKeystrokes();
			getline(cin, password);
			ShowStdinKeystrokes();
			cout << endl;

			// pusher instance
			PushHandler buf(username);
			token = buf.login(password);


			// Build config
			iniReader.SetValue("pusher", "username", username.c_str());
			iniReader.SetValue("pusher", "appToken", token.c_str());

			// Check if file is writable
			if(iniReader.SaveFile(CONFIG_FILE) < 0)
			{
				cout << "Try running pusher as root or save the following in "
					<< CONFIG_FILE << "\n" << endl;

				// Data
				string strData;
				iniReader.Save(strData);
				cout << strData << endl;

				return 1;
			}


			cout << "Success!" << endl;
			return 0;
		}



		// Check if reading of config is possible
		if(iniReader.LoadFile(CONFIG_FILE) < 0)
		{
			throw PusherError("You need to login first.");
		}

		string username = iniReader.GetValue("pusher", "username", "");
		string appToken = iniReader.GetValue("pusher", "appToken", "");

		if(username.empty() || appToken.empty())
		{
			throw PusherError("You need to login first.");
		}



		// Loading values
		PushHandler pusherInstance(username, appToken);



		// Verify token
		if(verifySwitch.getValue())
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



		// List devices
		if(listSwitch.getValue())
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
				if(devices[i].id.length() > idLength) { idLength = devices[i].id.length(); }
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
					<< devices[i].id << "\033[" << (idLength - devices[i].id.length() + 2) << "C"
					<< devices[i].title << "\033[" << (titleLength - devices[i].title.length() + 2) << "C"
					<< devices[i].model << endl;
			}

			return 0;
		}



		// Device id
		if(idArg.getValue() != 0)
		{
			id = idArg.getValue();
		}
		else
		{
			return 1;
		}



		// Load message
		if(pipeSwitch.getValue())
		{
			string pipeBuffer;

			while(getline(cin, pipeBuffer))
			{
				message += "\n";
				message += pipeBuffer;
			}

			message.erase(0,1);
		}
		else
		{
			message = noLabelMessage.getValue();
		}

		// Send the message
		stringstream stringID;
		stringID << id;

		pusherInstance.sendToDevice(stringID.str(), message);
	}


	/* ERROR HANDLING */


	// Command line parsing exception
	catch (TCLAP::ArgException &e)
	{
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
		return 1;
	}


	// errors thrown by pushhandler
	catch(PusherError& e)
	{
		cout << "Error: " << e.what() << endl;
		return 1;
	}


	// other errors
	catch(exception& e)
	{
		cout << "Some kind of error occured: " << e.what() << endl;
		return 1;
	}

	return 0;
}
