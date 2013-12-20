/**
 * GameController - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "GameController.h"

#include "Graphics/GraphicFactory.h"

#include <GL/freeglut.h>

GameController::GameController() : _graphFactory() {
}

void GameController::start(GameMod * mod) {
	if (_mod != NULL) {
		// TODO clean up
	}

	_mod = mod;
	_mod->load();

	start();
}

#include <cstdio>
#define DEBUG

void GameController::draw() {
    glEnable ( GL_LIGHTING );
	
	_camera.setUp();
	
	glPushMatrix();
	glTranslatef(1.1f, 0, 0);
	_firstNode->draw();
	glPopMatrix();
}

void GameController::tick(GLfloat delta, GLfloat absolute) {
	_camera.tick(delta, absolute);
}

void GameController::start() {
#ifdef DEBUG
	printf("Starting game...\n");
#endif

	_identity = _mod->getIdentity();

#ifdef DEBUG
	printf("Loaded user's identity (%x): %s\n", _identity, _identity->getPerson()->getName().c_str());
#endif

	_firstNode = _graphFactory->build(_identity->getPerson());
	_currentNode = _firstNode;
}
Camera * GameController::getCamera() {
	return &_camera;
}
