#ifndef MAZEMINIGAME_H
#define MAZEMINIGAME_H

#include "../IMinigame.h"
#include "../IMinigameInstance.h"
#include "Maze.h"
#include "../../Graphics/Camera.h"

#include <GL/glut.h>
#include <tgmath.h> 

class MazeMinigame : public IMinigame {
	public:
		MazeMinigame(GameContext * context);

		virtual std::string getInternalName();
		virtual std::string getName();
		virtual std::string getDescription();
		
		virtual Level * getLevelSettings();

		virtual IMinigameInstance * newGame();

	private:
		GameContext * _context;

		class MazeInstance : public IMinigameInstance {
			public:
				MazeInstance(GameContext * context);

				virtual void start();

				virtual void draw();
				virtual void drawCube(double size);
				virtual void drawFloor();
				virtual void tick(int delta, int current);

				virtual void onKeyDown(int key, int special);
				virtual void onKeyUp(int key, int special);

				virtual void onMouseButton(int state, int button, int x, int y);
				virtual void onMouseMove(int x, int y);

				virtual void finish();
				
				virtual ~MazeInstance();

			private:
				GameContext * _context;
				Maze * maze;

				Camera camera;

				bool keys[4];
				
				typedef struct Player {
					GLfloat x, y;
					GLfloat vx, vy;
				} Player;

				Player player;
				GLfloat mx, my;
				GLfloat rotateX = 0, rotateZ = 0;
				GLfloat rotateAngle = 0;
				GLfloat tx, ty;
				GLuint textureId1, textureId2;
				GLuint mazeList;
				int pos[2];
				bool rotating[4];
				bool textures, oldTextures;
				int colors[3];
				int cubeStopped;
				vector<int*> solution;
				
				bool detectCollision();
				void applyRotating(int);
				void cleanRotate();
				void cleanKeys();
				void createList();
				void deleteList();
				void activateSuggestion();
		};
};

#endif
