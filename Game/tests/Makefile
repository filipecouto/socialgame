OBJ = test.o

test.a :	$(OBJ)
	ar rcs $@ $(OBJ)
	
tests : ../src/Mods/AdvancedMode.a test.a $(OBJ_FILES)
	g++ $^ -ggdb -lGL -lGLU -lglut -ljpeg -lcurl ../src/Mods/AdvancedMode.a test.a -o $@
	
%.o : %.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<
	
clean :
	rm *.o