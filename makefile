#=============================================================================
# Set variables for the build

TARGET = pusher
INSTALL_DIR = /usr/local/bin
CXX = g++
CPPFLAGS = -std=c++11
BUILDCOMMAND = $(CXX) $(CPPFLAGS)
LIBS = -lcurl


#=============================================================================
# Build
all: pusher

pusher: json simpleini pushhandler main
	$(BUILDCOMMAND) src/json/json.o src/simpleini/ConvertUTF.o src/pushhandler.o src/main.o $(LIBS) -o $(TARGET)


# json library
.PHONY: json
json: src/json/json.o

src/json/json.o: src/json/json.cc
	$(BUILDCOMMAND) -c src/json/json.cc -o src/json/json.o


# simpleini
.PHONY: simpleini
simpleini: src/simpleini/ConvertUTF.o

src/simpleini/ConvertUTF.o: src/simpleini/ConvertUTF.c
	$(BUILDCOMMAND) -c src/simpleini/ConvertUTF.c -o src/simpleini/ConvertUTF.o


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
	rm -f src/json/*.o
	rm -f src/simpleini/*.o
	rm -f $(TARGET)


install: pusher
	cp $(TARGET) $(INSTALL_DIR)/


.PHONY: remove
remove:
	rm -f $(INSTALL_DIR)/$(TARGET)
