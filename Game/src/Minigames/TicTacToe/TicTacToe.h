#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "../IMinigame.h"
#include "../IMinigameInstance.h"
#include "../../Graphics/Camera.h"
#include "../../Mods/AdvancedMode/dependencies/CurlHelper/CurlHelper.h"
#include "../../Mods/AdvancedMode/dependencies/rapidjson/document.h"
#include <math.h>
#include "../../GUI/IWidgetEventsListener.h"
#include "../../GUI/Gui.h"
#include "../../GUI/WidgetContainer.h"
#include "../../GUI/ButtonWidget.h"

#include <GL/glut.h>

class TicTacToeMinigame : public IMinigame {
	public:
		TicTacToeMinigame(GameContext * context);

		virtual std::string getName();

		virtual IMinigameInstance * newGame();

	private:
		GameContext * _context;

		class TicTacToeInstance : public IMinigameInstance, public IWidgetEventsListener{
			public:
				TicTacToeInstance(GameContext * context);

				virtual void start();

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
				void endGame(string label, string action);
				char matriz[3][3] = {{'z', 'z', 'z'},
						    {'z', 'z', 'z'},
						    {'z', 'z', 'z'}};
				
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
				string server = "uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/InterfaceToBLL";
				
				TextWidget * labelText;
				ButtonWidget * finishButton;
				
				Gui * _gui;
		};
};

#endif // TESTMINIGAME_H
