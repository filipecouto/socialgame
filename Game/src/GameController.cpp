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
#define DEBUG
#ifdef DEBUG
#include <cstdio>
#endif

GameController::GameController() : _graphFactory() {
}

void GameController::start(GameMod * mod) {
	if (_mod != NULL) {
		// TODO clean up
	}

	_mod = mod;
	if(_listener) _mod->setEventListener(_listener);
	_mod->load();

	start();
}

void GameController::draw() {
	_camera.setUp();

	glPushMatrix();

	int len = personObjects.size();

	for (int i = 0; i < len; i++) {
		personObjects[i]->draw();
	}

#ifdef DEBUG
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
#endif

	glPopMatrix();
}

void GameController::pick(int x, int y) {
	GLuint selectBuf[256];
	GLint hits;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glSelectBuffer(256, selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix((GLdouble) x, (GLdouble) y, 1.0, 1.0, viewport);
	gluPerspective(67, (GLfloat) 16.f / 9.f , 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	_camera.setUp();

	int len = personObjects.size();

	for (int i = 0; i < len; i++) {
		glPushName(i);
		personObjects[i]->drawPickMode();
		glPopName();
	}

	glPopName();

	glPopMatrix();
	glFlush();

	hits = glRenderMode(GL_RENDER);
	onOpenGlPick(hits, selectBuf);

	//glutPostRedisplay();
}

void GameController::onOpenGlPick(GLint hits, GLuint buffer[]) {
	GLuint names, *ptr;

	GLuint name = -1;
	GLuint minZ = 0xffffffff;

	//printf ("hits = %d\n", hits);
	ptr = (GLuint *) buffer;

	for (int i = 0; i < hits; i++) {
		names = *ptr;
		//printf("%d) name count = %d;\n", i, names);

		if (names >= 2) {
			ptr++;
			//printf(" minZ = %f;", (float) *ptr / 0x7fffffff);

			if (*ptr < minZ) {
				minZ = *ptr;
				ptr += 3;

				int n = *ptr;

				if (n >= 0 && n < personObjects.size()) name = n;
			}
		}
	}

	if (name != -1 && _listener) {
		selectedPerson = personObjects[name]->getPerson();
		_listener->onPersonClicked(selectedPerson);
	}

	//printf("   clicked on %s", personObjects[name]->getPerson()->getName().c_str());

	//printf("n=%d\n", name);
}

void GameController::flyTo(IPerson * person) {
	PersonGraphic * g = ((PersonGraphic *)getGraphic(getIdentityPerson()));

	if (person == getIdentityPerson()) {
		_camera.lookAt(g->x + 1, g->y + g->getRadius() * 2, g->z + 1);
		_camera.moveTo(g->x, g->y + g->getRadius() * 3, g->z);
	} else {
		_camera.lookAt(g->x, g->y + g->getRadius(), g->z);
		g = ((PersonGraphic *) getGraphic(person));
		_camera.moveTo(g->x, g->y + g->getRadius() * 3, g->z);
	}
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

	load();
}

IUser * GameController::getIdentity() {
	return _identity;
}

void GameController::load() {
	loadPeople(_identity->getPerson(), 3);
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
		if ((*personObjects[i]) == p) return personObjects[i];
	}

	return NULL;
}

void GameController::createPerson(IPerson * p, GLfloat x, GLfloat y, GLfloat z) {
	if (!findGraphic(p)) {
		PersonGraphic * g = (PersonGraphic *)_graphFactory->build(p);
		personObjects.push_back(g);

		g->x = x;
		g->y = y + p->getConnections().size() * 0.8f;
		g->z = z;

		printf("This person (%s) is at (%f, %f, %f)\n", p->getName().c_str(), g->x, g->y, g->z);
	}
}

void GameController::loadPeople(IPerson * p, int depth) {
	createPerson(p, 0, 0, 0);

	loadPeople(p, depth - 1, 0, 0, 0);
}

void GameController::loadPeople(IPerson * p, int depth, GLfloat x, GLfloat y, GLfloat z) {
	if (depth != 0 && p/* && !findGraphic(p)*/) {
// 		PersonGraphic * g = (PersonGraphic *)_graphFactory->build(p);
// 		personObjects.push_back(g);

		std::vector<IConnection *> cons = p->getConnections();
		int len = cons.size();
// 		g->x = x;
// 		g->y = y + len * 0.5f;
// 		g->z = z;

		for (int i = 0; i < len; i++) {
			GLfloat distance = 8.0f + rand() % 3 - 1;
			createPerson(cons[i]->getPerson(), x + distance * cos(i * 2 * M_PI / (len)), y, z + distance * sin(i * 2 * M_PI / (len)));
		}

		for (int i = 0; i < len; i++) {
			PersonGraphic * g = (PersonGraphic *) findGraphic(cons[i]->getPerson());
			loadPeople(cons[i]->getPerson(), depth - 1, g->x, y, g->z);
		}
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

IPerson * GameController::getIdentityPerson() {
	return _identity->getPerson();
}

IPerson * GameController::getSelectedPerson() {
	return selectedPerson;
}

void GameController::setListener(IGameControllerListener * listener) {
	_listener = listener;
	if(_mod) _mod->setEventListener(listener);
}
