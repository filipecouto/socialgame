CPP_FILES := $(wildcard *.cpp) dependencies/CurlHelper/CurlHelper.cpp
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

all : AdvancedMode.a

AdvancedMode.a : $(OBJ_FILES)
	ar rcs ../$@ $^

CurlHelper.o : dependencies/CurlHelper/CurlHelper.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<
	
%.o : %.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

clean :
	rm *.o; rm ../AdvancedMode.a