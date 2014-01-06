GRAPHICS_FILES := $(wildcard Graphics/*.cpp)
MODELS_FILES := $(wildcard Models/*.cpp)
MODS_FILES := $(wildcard Mods/*.cpp) $(wildcard Mods/TestMod/*.cpp)
MINIGAMES_FILES := $(wildcard Minigames/*.cpp) $(wildcard Minigames/Test/*.cpp)

CPP_FILES := $(wildcard *.cpp) $(GRAPHICS_FILES) $(MODELS_FILES) $(MODS_FILES) $(MINIGAMES_FILES)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

all : obj GUI/GUI.a SocialGame ;

SocialGame : $(OBJ_FILES)
	g++ $^ -ggdb -lGL -lGLU -lglut GUI/GUI.a -o $@
	
GUI/GUI.a :
	cd GUI; make

obj :
	-mkdir obj

obj/%.o : %.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Models/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Graphics/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Mods/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Mods/TestMod/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Minigames/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Minigames/Test/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

run : all
	./SocialGame

clean :
	rm obj/*