/**
 * GameController - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#if _WIN32
#define GL_GLEXT_PROTOTYPES
#include <GL\glew.h>
#include <GL\glext.h>
#endif

#include "GameController.h"

#include "Dependencies/readjpeg.c"
#include "Graphics/GraphicFactory.h"
#include "Models/IConnectionsList.h"
#include "Models/INotificationsList.h"
#include "Models/IPendingGame.h"
#include "Minigames/MinigameFactory.h"

#include <math.h>
#include <GL/freeglut.h>
#define DEBUG
#ifdef DEBUG
#include <cstdio>
#endif

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#pragma comment (lib, "libjpeg.lib")

#define GameController_isInMinigame _minigame && _minigameState == 1

GameController::GameController() : _graphFactory() {
	for (int i = 0; i < 10; i++) {
		keys[i] = false;
	}

	//std::ifstream

	std::vector<Language> langs = languageLoader.getLanguages();

	if (langs.size() > 0) languageLoader.setLanguage(langs[0]);
}

void GameController::start(GameMod * mod) {
	if (_mod != NULL) {
		personObjects.clear();
		// TODO clean up
	} else {
		// first time loading
		skybox.setTextureIds(loadTexture("Graphics/SkyBox Images/negz.jpg"),
		                     loadTexture("Graphics/SkyBox Images/negx.jpg"),
		                     loadTexture("Graphics/SkyBox Images/posz.jpg"),
		                     loadTexture("Graphics/SkyBox Images/posx.jpg"),
		                     loadTexture("Graphics/SkyBox Images/posy.jpg"),
		                     loadTexture("Graphics/SkyBox Images/negy.jpg"));
	}

	_mod = mod;

	if (_mod != NULL) {
		if (_listener) _mod->setEventListener(_listener);

		_mod->load();

		start();

		_listener->onGameLoaded();
	}
}

void GameController::draw() {
	if(!_mod) return;
	glPushMatrix();

	if (GameController_isInMinigame) {
		glEnable(GL_DEPTH_TEST);
		_minigame->draw();
	} else {
		_camera.setUp();

		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		_camera.translateToCamera();
		skybox.draw();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

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
	}

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

	if (g) {
		if (person == getIdentityPerson()) {
			_camera.lookAt(g->x, g->y + g->getRadius(), g->z - 2);
			_camera.moveTo(g->x, g->y + g->getRadius() * 2.5f, g->z);
		} else {
			_camera.lookAt(g->x, g->y + g->getRadius(), g->z);
			g = ((PersonGraphic *) getGraphic(person));
			_camera.moveTo(g->x, g->y + g->getRadius() * 3, g->z);
		}
	}
}

void GameController::tick(int delta, int current) {
	_camera.tick(delta, current);

	if (_minigame) {
		if (_minigameState == 0) {
			if (_camera.getY() >= 17) {
				_minigameState = 1;
			}
		} else if (_minigameState == 1) {
			_minigame->tick(delta, current);
		} else if (_minigameState == -1) {
			if (_camera.getY() < 17) {
				delete _minigame;
				_minigame = NULL;
			}
		}
	}

	if (keys[0]) _camera.walk(0, 0, +0.01f * delta);

	if (keys[1]) _camera.walk(-0.01f * delta, 0, 0);

	if (keys[2]) _camera.walk(0, 0, -0.01f * delta);

	if (keys[3]) _camera.walk(+0.01f * delta, 0, 0);

	if (keys[4]) _camera.rotate(+0.005f * delta, 0);

	if (keys[5]) _camera.rotate(0, 0.015f * delta);

	if (keys[6]) _camera.rotate(-0.005f * delta, 0);

	if (keys[7]) _camera.rotate(0, -0.015f * delta);

	if (keys[8]) _camera.translate(0, 0.01f * delta, 0);

	if (keys[9]) _camera.translate(0, -0.01f * delta, 0);

}

void GameController::start() {
	if (!sound) {
		sound = new Sound();
		sound->initAudio();
	}

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
	loadPeople(_identity->getPerson(), 6); // FIXME just for testing, depth should be 3
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
		g->y = y + (p->getConnections() ? (p->getConnections()->getFriendsCount() * 2.0f) : 0);
		g->z = z;

		printf("This person (%s) is at (%f, %f, %f)\n", p->getName().c_str(), g->x, g->y, g->z);
	}
}

void GameController::loadPeople(IPerson * p, int depth) {
	createPerson(p, 0, 0, 0);

	loadPeople(p, depth - 1, 0, 0, 0);
}

void GameController::loadPeople(IPerson * p, int depth, GLfloat x, GLfloat y, GLfloat z) {
	if (depth != 0 && p && p->getConnections()) {
		IList<IConnection *> * cons = p->getConnections();
		int len = cons->size();

		for (int i = 0; i < len; i++) {
			// RULES FOR DISTANCE:
			// 1) if this person has too many friends, putting them further will help make the graph easier to understand
			// 2) addding some randomness to slightly displace people will avoid possible overlapping
			GLfloat distance = 5.0f + rand() % 3 - 1 + len * 0.8f;
			GLfloat angle = i * 2 * M_PI / len + ((rand() % 10) / 10.0f - 5.0f);
			createPerson((*cons)[i]->getPerson(), x + distance * cos(angle), y, z + distance * sin(angle));
		}

		for (int i = 0; i < len; i++) {
			PersonGraphic * g = (PersonGraphic *) findGraphic((*cons)[i]->getPerson());
			loadPeople((*cons)[i]->getPerson(), depth - 1, g->x, y, g->z);
		}
	}
}

void GameController::loadConnections() {
	int len = personObjects.size();

	for (int i = 0; i < len; i++) {
		personObjects[i]->load(this);
	}
}

void GameController::invalidatePerson(IPerson * person) {
	int i;
	int len = personObjects.size();

	PersonGraphic * g = (PersonGraphic *) findGraphic(person);

	if (g) g->y = person->getConnections()->getFriendsCount() * 1.0f;

	for (i = 0; i < len; i++) {
		personObjects[i]->invalidate(person);
	}
}

void GameController::startMinigame(IMinigame * minigame) {
	_minigame = minigame->newGame();
	_minigameState = 0;
	_minigame->start(-1);
	_minigame->setViewportDimensions(getViewportWidth(), getViewportHeight());
	_camera.translate(0, 20 - _camera.getY(), 0);

	if (sound) sound->setVolume(0.5f);
}

void GameController::startMinigame(IPendingGame * pendingGame, int index) {
	IMinigame * minigame = pendingGame->getMinigame(index, getMinigameFactory());
	_pendingGame = pendingGame;
	_pendingGameIndex = index;
	_minigame = minigame->newGame();
	_minigameState = 0;
	_minigame->start(pendingGame->getMinigameLevel(index));
	_minigame->setViewportDimensions(getViewportWidth(), getViewportHeight());
	_camera.translate(0, 20 - _camera.getY(), 0);

	if (sound) sound->setVolume(0.5f);
}

bool GameController::isInMinigame() {
	return GameController_isInMinigame;
}

void GameController::notifyMinigameFinished(IMinigameInstance * instance) {
	if (instance == _minigame) {
		printf("The minigame just ended\n");
		flyTo(getIdentityPerson());
		_minigameState = -1;

		if (_pendingGame) {
			_pendingGame->setMinigameScore(_pendingGameIndex, instance->getScore());
			invalidatePerson(_pendingGame->getConnection()->getPerson());
			_listener->onMinigameEnded(instance);
			_pendingGame = NULL;
		}

		invalidatePerson(getIdentityPerson());

		if (sound) sound->setVolume(1);
	}
}

GraphicFactory * GameController::getFactory() {
	return _graphFactory;
}

void GameController::onKeyDown(int key, int special) {
	if (GameController_isInMinigame) _minigame->onKeyDown(key, special);
	else {
		switch (key) {
			case 0 :
				switch (special) {
					case GLUT_KEY_UP:
						keys[4] = true;
						break;

					case GLUT_KEY_LEFT:
						keys[5] = true;
						break;

					case GLUT_KEY_DOWN:
						keys[6] = true;
						break;

					case GLUT_KEY_RIGHT:
						keys[7] = true;
						break;
				}

				break;

			case 'w':
				keys[0] = true;
				break;

			case 'a':
				keys[1] = true;
				break;

			case 's':
				keys[2] = true;
				break;

			case 'd':
				keys[3] = true;
				break;

			case 'z':
				keys[8] = true;
				break;

			case 'x':
				keys[9] = true;
				break;
		}
	}
}

GLuint GameController::loadTexture(std::string texture) {
	printf("Loading texture \"%s\"...\n", texture.c_str());

	char * image;
	int w, h, bpp;

	GLuint textureId;
	glGenTextures(1, &textureId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (read_JPEG_file(texture.c_str(), &image, &w, &h, &bpp)) {
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	} else {
		printf("Texture \"%s\" not found\n", texture.c_str());
	}

	_textures.push_back(textureId);

	return textureId;
}

void GameController::onKeyUp(int key, int special) {
	if (GameController_isInMinigame) {
		_minigame->onKeyUp(key, special);
	} else {
		switch (key) {
			case 0 :
				switch (special) {
					case GLUT_KEY_UP:
						keys[4] = false;
						break;

					case GLUT_KEY_LEFT:
						keys[5] = false;
						break;

					case GLUT_KEY_DOWN:
						keys[6] = false;
						break;

					case GLUT_KEY_RIGHT:
						keys[7] = false;
						break;
				}

				break;

			case 'w':
				keys[0] = false;
				break;

			case 'a':
				keys[1] = false;
				break;

			case 's':
				keys[2] = false;
				break;

			case 'd':
				keys[3] = false;
				break;

			case 'z':
				keys[8] = false;
				break;

			case 'x':
				keys[9] = false;
				break;
		}
	}
}

void GameController::onMouseButton(int state, int button, int x, int y) {
	if (GameController_isInMinigame) _minigame->onMouseButton(state, button, x, y);
}

void GameController::onMouseMove(int x, int y) {
	if (GameController_isInMinigame) _minigame->onMouseMove(x, y);
}

void GameController::setViewportDimensions(int width, int height) {
	GameFragment::setViewportDimensions(width, height);

	if (GameController_isInMinigame) _minigame->setViewportDimensions(width, height);
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

	if (_mod) _mod->setEventListener(listener);
}

GameMod * GameController::getGameMod() {
	return _mod;
}

IMinigameFactory * GameController::getMinigameFactory() {
	if (!_minigameFactory) {
		_minigameFactory = new MinigameFactory(this);
	}

	return _minigameFactory;
}

GameController::~GameController() {
	int len = _textures.size();

	for (int i = 0; i < len; i++)
		glDeleteTextures(1, &_textures[i]);

	delete sound;
}

bool GameController::detectCollisions(int x, int y) {
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
	return onCollisionPick(hits, selectBuf);
}

bool GameController::onCollisionPick(GLint hits, GLuint buffer[]) {
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

				if (n >= 0 && n < personObjects.size()) return true;
			}
		}
	}

	return false;
}

std::string GameController::getString(std::string value) {
	return languageLoader.getValue(value);
}

std::vector< Language > GameController::getLanguages() {
	return languageLoader.getLanguages();
}

void GameController::setLanguage(Language language) {
	languageLoader.setLanguage(language);
}
