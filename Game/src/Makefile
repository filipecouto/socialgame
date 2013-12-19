GRAPHICS_FILES := $(wildcard Graphics/*.cpp)
MODELS_FILES := $(wildcard Models/*.cpp)
MODS_FILES := $(wildcard Mods/*.cpp) $(wildcard Mods/TestMod/*.cpp)

CPP_FILES := $(wildcard *.cpp) $(GRAPHICS_FILES) $(MODELS_FILES) $(MODS_FILES)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

all : SocialGame ;

SocialGame : $(OBJ_FILES)
	g++ $^ -ggdb -lGL -lGLU -lglut GUI/GUI.a -o $@
	
obj/%.o : %.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Models/%.cpp
	g++ -std=c++11 -c -o $@ $<
	
obj/%.o : Graphics/%.cpp
	g++ -std=c++11 -c -o $@ $<
	
obj/%.o : Mods/%.cpp
	g++ -std=c++11 -c -o $@ $<
	
obj/%.o : Mods/TestMod/%.cpp
	g++ -std=c++11 -c -o $@ $<
	
run : all
	./SocialGame
	
clean :
	rm obj/*