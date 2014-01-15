CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

all : SimpleMode.a

SimpleMode.a : $(OBJ_FILES)
	ar rcs ../$@ $^

	
%.o : %.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

clean :
	rm *.o; rm ../SimpleMode.a