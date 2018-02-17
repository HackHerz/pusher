![Logo](https://github.com/HackHerz/pusher/blob/master/pusher.png)
[![All Contributors](https://img.shields.io/badge/all_contributors-3-orange.svg?style=flat-square)](#contributors)

# pusher
Send push-notifications to your phone from the command line. Uses [PushNotifier](http://pushnotifier.de/) to receive notifications.

## Features
- Written in C++
- Easy to [install](https://github.com/hackherz/pusher#installation)
- Even easier to [use](https://github.com/hackherz/pusher#usage)
- Should work on all Unix-based systems


## Installation

Make sure you have **libcurl4-openssl-dev** installed.
```bash
$ git clone --recursive https://github.com/HackHerz/pusher.git
$ cd pusher/
$ make
$ make install
```


## Usage

If you want some real life use cases make sure to check out our [example section](https://github.com/HackHerz/pusher/tree/master/examples).

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

## Contributors

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore -->
| [<img src="https://avatars2.githubusercontent.com/u/159488?v=4" width="100px;"/><br /><sub><b>Niels Lohmann</b></sub>](http:/nlohmann.me)<br />[💻](https://github.com/hackherz/pusher/commits?author=nlohmann "Code") | [<img src="https://avatars1.githubusercontent.com/u/1824603?v=4" width="100px;"/><br /><sub><b>James Rose</b></sub>](http://jameserose.co.uk)<br />[📖](https://github.com/hackherz/pusher/commits?author=jamesterjim "Documentation") | [<img src="https://avatars1.githubusercontent.com/u/2885148?v=4" width="100px;"/><br /><sub><b>Daniel Stein</b></sub>](https://hackherz.com/)<br />[💻](https://github.com/hackherz/pusher/commits?author=HackHerz "Code") [📖](https://github.com/hackherz/pusher/commits?author=HackHerz "Documentation") |
| :---: | :---: | :---: |
<!-- ALL-CONTRIBUTORS-LIST:END -->
Thanks goes to these wonderful people ([emoji key](https://github.com/kentcdodds/all-contributors#emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/kentcdodds/all-contributors) specification. Contributions of any kind welcome!