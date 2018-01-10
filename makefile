#=============================================================================
# Set variables for the build

TARGET = pusher
INSTALL_DIR = /usr/local/bin
CXX = g++
CPPFLAGS = -std=c++11
CDEFS = -DAPI_TOKEN=\"8E7D8B2DDE7DDE7D6C3V52VB52VBD4DDETBTTTKFFB11\"
CDEFS += -DAPP_PACKAGE=\"com.hackherz.pusher\"
BUILDCOMMAND = $(CXX) $(CDEFS) $(CPPFLAGS)
LIBS = `pkg-config libcurl --cflags --libs`


#=============================================================================
# Build
all: $(TARGET)

$(TARGET): simpleini pushnotifier main
	$(BUILDCOMMAND) src/simpleini/ConvertUTF.o src/pushnotifier-sdk-cpp/pushnotifier.o src/main.o $(LIBS) -o $(TARGET)


# simpleini
.PHONY: simpleini
simpleini: src/simpleini/ConvertUTF.o

src/simpleini/ConvertUTF.o: src/simpleini/ConvertUTF.c
	$(BUILDCOMMAND) -c src/simpleini/ConvertUTF.c -o src/simpleini/ConvertUTF.o


# pushnotifier
.PHONY: pushnotifier
pushnotifier: src/pushnotifier-sdk-cpp/pushnotifier.o

src/pushnotifier-sdk-cpp/pushnotifier.o: src/pushnotifier-sdk-cpp/PushNotifier.cpp
	$(BUILDCOMMAND) -c src/pushnotifier-sdk-cpp/PushNotifier.cpp -o src/pushnotifier-sdk-cpp/pushnotifier.o


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
	rm -f src/pushnotifier-sdk-cpp/pushnotifier.o
	rm -f $(TARGET)


install: pusher
	cp $(TARGET) $(INSTALL_DIR)/


.PHONY: remove
remove:
	rm -f $(INSTALL_DIR)/$(TARGET)
