<div style="text-align:center">![](http://hackherz.com/wp-content/uploads/2014/09/Pusher-UNIX.png)</div>

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


### Keeping me motivated
If you want to ensure that I'll continue developing just send me a tweet [@hackherz](https://twitter.com/hackherz) why you like or use my software :).


## Libraries
pusher uses a few third party libraries. They are all MIT-Licensed but they are so awesome I have to mention them.

- [json](https://github.com/nlohmann/json) by [Niels Lohmann](http://nlohmann.me/)
- [TCLAP](http://tclap.sourceforge.net/)
- [simpleini](https://github.com/brofield/simpleini) by Brodie Thiesfield
