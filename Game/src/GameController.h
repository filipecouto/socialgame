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

class GameController {
	public:
		GameController();
		
		void start(GameMod * mod);
		
		void draw();
		void tick(GLfloat delta, GLfloat absolute);
		
		Camera * getCamera();
		
		IPerson * getIdentityPerson() { return _identity->getPerson(); }

	private:
		GraphicFactory * _graphFactory;
		
		GameMod * _mod;
		
		IUser * _identity;
		
		IGraphic * _firstNode;
		IGraphic * _currentNode;
		
		Camera _camera;
		
		void start();
};

#endif