/**
 * GameController - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "GameController.h"

#include "Graphics/GraphicFactory.h"

#include <math.h>
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
	glEnable(GL_LIGHTING);

	_camera.setUp();

	glPushMatrix();

	int len = personObjects.size();

	for (int i = 0; i < len; i++) {
		PersonGraphic * g = personObjects[i];
		g->draw();
	}
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glLineWidth(2);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void GameController::tick(int delta, int absolute) {
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

	//_firstNode = _graphFactory->build(_identity->getPerson());

	load();
	//_firstNode->load(3, this);

	//_currentNode = _firstNode;
}

void GameController::load() {
	loadPeople(_identity->getPerson(), 3, 0, 0, 0);
	loadConnections();
}

IGraphic * GameController::getGraphic(IPerson * p) {
	IGraphic * graphic = findGraphic(p);

	if (graphic == NULL) {
		graphic = _graphFactory->build(p);
		personObjects.push_back((PersonGraphic *)graphic);
		graphic->load(this);
	} else {
	}

	return graphic;
}

PersonGraphic * GameController::findGraphic(IPerson * p) {
	int len = personObjects.size();

	for (int i = 0; i < len; i++) {
		//memoryPeople[i]->draw();
		if ((*personObjects[i]) == p) return personObjects[i];
	}

	return NULL;
}

void GameController::loadPeople(IPerson * p, int depth, GLfloat x, GLfloat y, GLfloat z) {
	if (depth != 0 && p && !findGraphic(p)) {
		PersonGraphic * g = (PersonGraphic *)_graphFactory->build(p);
		personObjects.push_back(g);

		std::vector<IConnection *> cons = p->getConnections();
		int len = cons.size();
		g->x = x;
		g->y = y + len * 0.5f;
		g->z = z;

		for (int i = 0; i < len; i++) {
			GLfloat distance = 10.0f;
			loadPeople(cons[i]->getPerson(), depth - 1, x + distance * cos(i * 360.0f / len), y, z + distance * sin(i * 360.0f / len));
		}

		printf("This person (%s) is at (%f, %f, %f)\n", p->getName().c_str(), g->x, g->y, g->z);
	}
}

void GameController::loadConnections() {
	int len = personObjects.size();

	for (int i = 0; i < len; i++) {
		personObjects[i]->load(this);
	}
}

GraphicFactory * GameController::getFactory() {
	return _graphFactory;
}

void GameController::onKeyDown(int key, int special) {
	switch (key) {
			// TODO this is ONLY FOR TESTING
		case 'w':
			_camera.translate(1, 0, 0);
			break;

		case 's':
			_camera.translate(-1, 0, 0);
			break;

		case 'a':
			_camera.translate(0, 0, -1);
			break;

		case 'd':
			_camera.translate(0, 0, 1);
			break;
			
		case 'z':
			_camera.translate(0, 1, 0);
			break;
			
		case 'x':
			_camera.translate(0, -1, 0);
			break;
	}
}

Camera * GameController::getCamera() {
	return &_camera;
}
