#=============================================================================
# Set variables for the build

TARGET = pusher
INSTALL_DIR = /usr/local/bin
CXX = g++
CPPFLAGS = -std=c++11
BUILDCOMMAND = $(CXX) $(CPPFLAGS)
LIBS = `pkg-config libcurl --cflags --libs`


#=============================================================================
# Build
all: pusher

$(TARGET): simpleini curlhandler pushhandler main
	$(BUILDCOMMAND) src/simpleini/ConvertUTF.o src/curlhandler.o src/pushhandler.o src/main.o $(LIBS) -o $(TARGET)


# simpleini
.PHONY: simpleini
simpleini: src/simpleini/ConvertUTF.o

src/simpleini/ConvertUTF.o: src/simpleini/ConvertUTF.c
	$(BUILDCOMMAND) -c src/simpleini/ConvertUTF.c -o src/simpleini/ConvertUTF.o


# curlhandler
.PHONY: curlhandler
curlhandler: src/curlhandler.o

src/curlhandler.o: src/curlhandler.cpp
	$(BUILDCOMMAND) -c src/curlhandler.cpp -o src/curlhandler.o


# pushhandler
.PHONY: pushhandler
pushhandler: src/pushhandler.o

src/pushhandler.o: src/pushhandler.cpp
	$(BUILDCOMMAND) -c src/pushhandler.cpp -o src/pushhandler.o


# main
.PHONY: main
main: src/main.o

src/main.o: src/main.cpp
	$(BUILDCOMMAND) -c src/main.cpp -o src/main.o

#=============================================================================
# Other targets
.PHONY: clean
clean:
	rm -f src/*.o
	rm -f src/simpleini/*.o
	rm -f $(TARGET)


install: pusher
	cp $(TARGET) $(INSTALL_DIR)/


.PHONY: remove
remove:
	rm -f $(INSTALL_DIR)/$(TARGET)
