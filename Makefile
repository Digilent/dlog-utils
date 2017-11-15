# Debug printing is turned off by default.  Turn on debug prints by passing 'DEBUGPRINT=1'.
CXX ?=g++
CXXFLAGS = -Wall -O2 -std=c++11
LIBFLAGS = -fPIC -shared
INC = -Isrc
LIBCORE = src/dlog-utils.cpp
APPEXT = .out
SOEXT = .so
DEBUGABLE =

#Set path for libraries based on platform
ifeq ($(OS),Windows_NT)
	APPEXT =.exe
	SOEXT =.dll
endif

#Enable debuggable builds by passing DEBUGPRINT=1
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CXXFLAGS += -g
endif

#Enable debug prints by passing DEBUGPRINT=1
DEBUGPRINT ?= 0
ifeq ($(DEBUGPRINT), 1)
    CXXFLAGS += -DDEBUGPRINT
endif

dlogLib:
	$(CXX) $(INC) $(LIBCORE) $(CXXFLAGS) $(LIBFLAGS) -o build/libdlogutils$(SOEXT)

dlogStaticLib:
	$(CXX) $(INC) $(LIBCORE) $(CXXFLAGS) -c -o build/dlogutils.o
	ar rcs build/libdlogutils.a build/dlogutils.o
	rm build/dlogutils.o

dlogExamples:
	$(CXX) $(INC) $(CXXFLAGS) examples/main.cpp -o examples/build/main$(APPEXT) build/libdlogutils.a

all: dlogLib dlogStaticLib dlogExamples docs

#Setup Environment
setupEnv:
	@mkdir -p build
	@mkdir -p examples/build
	@mkdir -p test
	@mkdir -p doc

#Documentation
docs:
	@doxygen Doxyfile

#Remove all built and temporary files
clean:
	rm -rf build/*
	rm -rf doc/*
	rm -rf examples/build/*
