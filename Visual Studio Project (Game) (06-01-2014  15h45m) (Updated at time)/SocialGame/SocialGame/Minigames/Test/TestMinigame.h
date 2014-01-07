#ifndef TESTMINIGAME_H
#define TESTMINIGAME_H

#include "../IMinigame.h"
#include "../IMinigameInstance.h"
#include "../../Graphics/Camera.h"

#include <GL/glut.h>

class TestMinigame : public IMinigame {
	public:
		TestMinigame(GameContext * context);

		virtual std::string getName();

		virtual IMinigameInstance * newGame();

	private:
		GameContext * _context;

		class TestInstance : public IMinigameInstance {
			public:
				TestInstance(GameContext * context);

				virtual void start();

				virtual void draw();
				virtual void tick(int delta, int current);

				virtual void onKeyDown(int key, int special);
				virtual void onKeyUp(int key, int special);

				virtual void onMouseButton(int state, int button, int x, int y);
				virtual void onMouseMove(int x, int y);

				virtual void finish();
				
				virtual ~TestInstance();

			private:
				GameContext * _context;

				Camera camera;

				typedef struct Thing {
					GLfloat x, y;
					GLfloat vx, vy;
				} Thing;

				bool keys[4];

				Thing thing;
				GLfloat mx, my;
		};
};

#endif // TESTMINIGAME_H
