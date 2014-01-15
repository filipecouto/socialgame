OBJ = test.o

all : test;

run : all clean
	./test
	
test : ../src/Mods/AdvancedMode.a test.o $(OBJ_FILES)
	g++ $^ -ggdb -lcurl ../src/Mods/AdvancedMode.a -o $@
	
%.o : %.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<
	
clean :
	rm *.o