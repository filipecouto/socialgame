#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "../IMinigame.h"
#include "../IMinigameInstance.h"
#include "../../Graphics/Camera.h"
#include <math.h>
#include "../../GUI/IWidgetEventsListener.h"
#include "../../GUI/Gui.h"
#include "CentralServerTicTacToe.h"

#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class TicTacToeMinigame : public IMinigame {
	public:
		TicTacToeMinigame(GameContext * context);

		virtual std::string getName();
		virtual std::string getDescription();
		virtual std::string getInternalName();

		virtual IMinigameInstance * newGame();

	private:
		GameContext * _context;

		class TicTacToeInstance : public IMinigameInstance, public IWidgetEventsListener{
			public:
				TicTacToeInstance(GameContext * context);

				virtual void start(int level);

				virtual void draw();
				virtual void tick(int delta, int current);

				virtual void onKeyDown(int key, int special);
				virtual void onKeyUp(int key, int special);

				virtual void onMouseButton(int state, int button, int x, int y);
				virtual void onMouseMove(int x, int y);

				virtual void finish();

				virtual ~TicTacToeInstance();

				void drawLine(GLfloat addZ = 0);
				void drawX(int x, int y);
				void drawXLine(GLfloat ang);
				void drawO(int x, int y);
				void drawCircle(GLfloat radius);
				bool checkMatriz(int x, int y);
				string convertMatrizToPrologList();
				void Game(string list);
				void endGame(string message, bool win);
				void startNewGame();
				char matriz[3][3];
				
				// events from GUI
				virtual bool onDialogResult(Dialog * dialog, int buttonId);
				virtual bool onWidgetClicked(Widget* widget);
				

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
				
				Gui * _gui;
				bool ableToPlay = true;
				GLuint textureId1;
				CentralServerTicTacToe * centralServer;
		};
};

#endif // TESTMINIGAME_H
