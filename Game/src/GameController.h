/**
 * GameController - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <GL/freeglut.h>


#ifdef _WIN32
extern "C"{
#include "jpeglib.h"
}
#endif

#include "Mods/GameMod.h"
#include "Models/IUser.h"
#include "Graphics/IGraphic.h"
#include "Graphics/GraphicFactory.h"
#include "Graphics/Camera.h"
#include "Graphics/SkyBox.h"
#include "GameContext.h"
#include "IGameControllerListener.h"
#include "GameFragment.h"
#include "Minigames/IMinigame.h"
#include "Minigames/IMinigameInstance.h"

class IPendingGame;

class GameController : public GameContext, GameFragment {
	public:
		GameController();
		
		void start(GameMod * mod);
		
		void draw();
		void tick(int delta, int current);
		
		Camera * getCamera();
		
		GameMod * getGameMod();
		IUser * getIdentity();
		IPerson * getIdentityPerson();
		IPerson * getSelectedPerson();
		
		void onKeyDown(int key, int special);
		void onKeyUp(int key, int special);
		
		void onMouseMove(int x, int y);
		void onMouseButton(int state, int button, int x, int y);
		
		void setViewportDimensions(int width, int height);
		
		void pick(int x, int y);
		void flyTo(IPerson * person);
		
		void setListener(IGameControllerListener * listener);
		
		void startMinigame(IMinigame * minigame);
		void startMinigame(IPendingGame * pendingGame, int index);
		bool isInMinigame();
		void notifyMinigameFinished(IMinigameInstance *);
		
		/**
		 * Notifies the GameController this person (and its connections) are not valid anymore
		 * and it needs to be refreshed.
		 */
		void invalidatePerson(IPerson * person);
		
		// GameContext methods
		virtual GraphicFactory * getFactory();
		virtual IGraphic * getGraphic(IPerson * p);
		
		virtual GLuint loadTexture(std::string texture);
		
		virtual IMinigameFactory * getMinigameFactory();
		
		virtual ~GameController();
		
		bool detectCollisions(int x, int y);
		bool onCollisionPick(GLint hits, GLuint buffer[]);

	private:
		GraphicFactory * _graphFactory = NULL;
		IMinigameFactory * _minigameFactory = NULL;
		
		GameMod * _mod = NULL;
		
		IMinigameInstance * _minigame = NULL;
		IPendingGame * _pendingGame = NULL;
		int _pendingGameIndex = -1;
		int _minigameState = 0;
		
		IUser * _identity = NULL;
		
		IGraphic * _firstNode = NULL;
		IGraphic * _currentNode = NULL;
		
		Camera _camera;
		
		IPerson * selectedPerson = NULL;
		
		std::vector<PersonGraphic *> personObjects;
		PersonGraphic* findGraphic(IPerson * p);
		SkyBox skybox;
		std::vector<GLuint> _textures;

		IGameControllerListener * _listener = NULL;
		
		bool keys[10];
		
		void load();
		void createPerson(IPerson * p, GLfloat x, GLfloat y, GLfloat z);
		//void setPersonPosition(IPerson * p, GLfloat x, GLfloat y, GLfloat z);
		void loadPeople(IPerson * p, int depth);
		void loadPeople(IPerson * p, int depth, GLfloat x, GLfloat y, GLfloat z);
		void loadConnections();
		
		void start();
		
		void onOpenGlPick(GLint hits, GLuint buffer[]);
};

#endif