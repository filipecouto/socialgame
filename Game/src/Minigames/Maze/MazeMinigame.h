#ifndef MAZEMINIGAME_H
#define MAZEMINIGAME_H

#include "../IMinigame.h"
#include "../IMinigameInstance.h"
#include "../../Graphics/Camera.h"

#include <GL/glut.h>

class MazeMinigame : public IMinigame {
	public:
		Maze(GameContext * context);

		virtual std::string getName();

		virtual IMinigameInstance * newGame();

	private:
		GameContext * _context;

		class MazeInstance : public IMinigameInstance {
			public:
				MazeInstance(GameContext * context);

				virtual void start();

				virtual void draw();
				virtual void tick(int delta, int current);

				virtual void onKeyDown(int key, int special);
				virtual void onKeyUp(int key, int special);

				virtual void onMouseButton(int state, int button, int x, int y);
				virtual void onMouseMove(int x, int y);

				virtual void finish();
				
				virtual ~MazeInstance();

			private:
				GameContext * _context;

				Camera camera;

				bool keys[4];
				
				typedef struct Player {
					GLfloat x, y;
					GLfloat vx, vy;
				} Player;

				Player player;
				GLfloat mx, my;
				
				bool detectCollision();
				
		};
};

#endif
