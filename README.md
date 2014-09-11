# pusher
**pusher** is a simple cli program to connect your server or computer with the app [PushNotifier](http://www.pushnotifier.de/). 


# Building
## Requirements

* boost `libboost-dev`
* boost regex `libboost-regex-dev`
* boost program options `libboost-program-options-dev`
* curl `libcurl4-gnutls-dev`

## Compile
First you do have to change `API_TOKEN` in src/pushhandler.h. You can receive your API-Token at [a.gidix.de](http://www.a.gidix.de/). Don't forget to match the APP-Package as well.

    chmod +x configure
    ./configure
    make
    make install

If you want to uninstall `pusher` try

    make remove


# Usage

The first time using `pusher` you have to log in to your [gidix.de](http://www.gidix.de/) account.

    pusher -t


The next step is to request a list of all your devices available

    pusher -l


You are finally able to send messages from your server to your device. You have two options now.

1) Normal mode.
Declare the message in " and put the message as your last argument.

    pusher -i # "hello world"

Replace the `#` with the id of your device.    


2) Pipe mode.
You can pipe the output of another program, e.g. echo, into `pusher`

    echo "hello world" | pusher -i # -p


To see more available options use the help flag.

    pusher -h
