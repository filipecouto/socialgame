/**
 * GameController - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <GL/freeglut.h>

#include "Mods/GameMod.h"
#include "Models/IUser.h"
#include "Graphics/IGraphic.h"
#include "Graphics/GraphicFactory.h"
#include "Graphics/Camera.h"
#include "GameContext.h"
#include "IGameControllerListener.h"

class GameController : public GameContext {
	public:
		GameController();
		
		void start(GameMod * mod);
		
		void draw();
		void tick(int delta, int absolute);
		
		virtual GraphicFactory * getFactory();
		virtual IGraphic * getGraphic(IPerson * p);
		
		Camera * getCamera();
		
		IPerson * getIdentityPerson() { return _identity->getPerson(); }
		
		void onKeyDown(int key, int special);
		
		void pick(int x, int y);
		
		void setListener(IGameControllerListener * listener);

	private:
		GraphicFactory * _graphFactory = NULL;
		
		GameMod * _mod = NULL;
		
		IUser * _identity = NULL;
		
		IGraphic * _firstNode = NULL;
		IGraphic * _currentNode = NULL;
		
		Camera _camera;
		
		std::vector<PersonGraphic *> personObjects;
		PersonGraphic* findGraphic(IPerson * p);

		IGameControllerListener * _listener = NULL;
		
		void load();
		void loadPeople(IPerson * p, int depth, GLfloat x, GLfloat y, GLfloat z);
		void loadConnections();
		
		void start();
		
		void onOpenGlPick(GLint hits, GLuint buffer[]);
};

#endif