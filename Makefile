MAKEFILE      = Makefile
CC            = gcc
CXX           = g++
LIBS          = `pkg-config --libs-only-l opencv` -ltiff
OBJECTS_DIR   = ./
SOURCES       = main.cpp tiffcapture.cpp 
OBJECTS       = main.o tiffcapture.o
TARGET        = TIFFCapture

all: $(OBJECTS)
	$(CXX) $(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

main.o: main.cpp tiffcapture.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

tiffcapture.o: tiffcapture.cpp tiffcapture.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tiffcapture.o tiffcapture.cpp

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(TARGET)