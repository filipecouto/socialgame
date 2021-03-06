GRAPHICS_FILES := $(wildcard Graphics/*.cpp)
MODELS_FILES := $(wildcard Models/*.cpp)
MODS_FILES := $(wildcard Mods/*.cpp) $(wildcard Mods/TestMod/*.cpp)
MINIGAMES_FILES := $(wildcard Minigames/*.cpp) $(wildcard Minigames/Test/*.cpp) $(wildcard Minigames/TicTacToe/*.cpp) $(wildcard Minigames/Hangman/*.cpp) $(wildcard Minigames/Maze/*.cpp)

CPP_FILES := $(wildcard *.cpp) $(GRAPHICS_FILES) $(MODELS_FILES) $(MODS_FILES) $(MINIGAMES_FILES)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

all : obj SocialGame ;

SocialGame : Mods/AdvancedMode.a Mods/SimpleMode.a GUI/GUI.a $(OBJ_FILES)
	g++ $^ -ggdb -lGL -lGLU -lglut -ljpeg -lopenal -lalut -lcurl Mods/AdvancedMode.a Mods/SimpleMode.a GUI/GUI.a -o $@

GUI/GUI.a :
	cd GUI; make

Mods/AdvancedMode.a :
	cd Mods/AdvancedMode; make
Mods/SimpleMode.a :
	cd Mods/SimpleMode; make
	
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
	
obj/%.o : Minigames/TicTacToe/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

obj/%.o : Minigames/Hangman/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<
	
obj/%.o : Minigames/Maze/%.cpp
	g++ -std=c++11 -ggdb -c -o $@ $<

run : all
	./SocialGame

clean :
	rm obj/*

install : all
	mkdir -p /usr/share/SocialGame; cp SocialGame /usr/share/SocialGame/SocialGame; cp BG001.wav /usr/share/SocialGame/BG001.wav; cp hangman_floor_texture.jpeg /usr/share/SocialGame/hangman_floor_texture.jpeg; cp maze_floor.jpg /usr/share/SocialGame/maze_floor.jpg; cp maze_walls.jpg /usr/share/SocialGame/maze_walls.jpg; cp tictactoe_texture.jpg /usr/share/SocialGame/tictactoe_texture.jpg; cp ../deployment/Linux/SocialGame.desktop /usr/share/applications/SocialGame.desktop