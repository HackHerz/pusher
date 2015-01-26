![Logo](http://hackherz.com/wp-content/uploads/2014/09/Pusher-UNIX.png)

# pusher
Send push-notifications to your phone from the command line. Uses [PushNotifier](http://pushnotifier.de/) to receive notifications.

## Features
- Written in C++
- Easy to [install](https://github.com/hackherz/pusher#installation)
- Even easier to [use](https://github.com/hackherz/pusher#usage)
- Should work on all Unix-based systems


## Installation

### Option 1: Debian package
You can download debian packages from [my website](http://hackherz.com/pusher#download).

### Option 2: From source
```bash
$ git clone https://github.com/HackHerz/pusher.git
$ cd pusher/
$ make
$ make install
```


## Usage

### Basic usage
```bash
$ pusher -i 1 "Hello World"    # Send Hello World to device-id 1 
```

### Pipe output into pusher
```bash
$ echo "Hello World" | pusher -i 1 -p
```

### List all your devices
```bash
$ pusher --list
```

### Login
```bash
$ pusher --token    # Only necessary the first time using pusher 
```

### Display Help
```bash
$ pusher -h    # Outputs all available options
```


## Contributing

#### Bug Reports & Feature Requests
Please use the [issue tracker](https://github.com/HackHerz/pusher/issues) to report any bugs or file feature requests.

#### Developing
Just file a pull request and start coding.
If you want to develop your own software with code from pusher, make sure that you are using your own [API-Token](http://a.gidix.de/). You have to change it in pushhandler.h

### Keep me motivated
If you want to make sure that I'll continue developing just send me a tweet [@hackherz](https://twitter.com/hackherz) why you like or use my software :).


## Libraries
pusher uses a few third party libraries.

- [json](https://github.com/nlohmann/json) by [Niels Lohmann](http://nlohmann.me/)
- [TCLAP](http://tclap.sourceforge.net/)
- [simpleini](https://github.com/brofield/simpleini) by Brodie Thiesfield
