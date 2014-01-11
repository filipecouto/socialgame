#include "MazeMinigame.h"
#include "../../GameContext.h"

MazeMinigame::MazeMinigame(GameContext * context) : _context(context) {

}

std::string MazeMinigame::getName() {
	return "Maze Game";
}

IMinigameInstance * MazeMinigame::newGame() {
	return new MazeInstance(_context);
}

void MazeMinigame::MazeInstance::draw() {
	camera.setUp();
	//TODO design
	
	int width = maze->getWidth(), heigth = maze->getHeight();
	
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < heigth; j++) {	
			if(maze->getValue(i,j)) {
				glPushMatrix();
					glTranslatef(i,j,0);
					glColor3f(0,0,1);
					drawCube();
				glPopMatrix();
			}
		}
	}
	
}

void MazeMinigame::MazeInstance::drawCube() {
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(1.0,1.0,0.0);
		glVertex3f(1.0,0.0,0.0);
		glVertex3f(0.0,1.0,0.0);
		glVertex3f(0.0,0.0,0.0);
	glEnd();
}

void MazeMinigame::MazeInstance::start() {
	camera.moveTo(0,0,-28);
	camera.lookAt(0,0,0);
}

bool MazeMinigame::MazeInstance::detectCollision() {
	return true;
}

void MazeMinigame::MazeInstance::tick(int delta, int current) {
	camera.tick(delta, current);
	// TODO Player movements
}

MazeMinigame::MazeInstance::MazeInstance(GameContext * context) : _context(context) {
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++){
		keys[i] = false;
	}
	maze = new Maze(10,10);
	maze->generate();
}

void MazeMinigame::MazeInstance::finish() {
	_context->notifyMinigameFinished(this);
}

void MazeMinigame::MazeInstance::onKeyDown(int key, int special) {
	switch (key) {
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
	}
}

void MazeMinigame::MazeInstance::onKeyUp(int key, int special) {
	switch(key) {
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
	}
}

void MazeMinigame::MazeInstance::onMouseButton(int state, int button, int x, int y) {
}

void MazeMinigame::MazeInstance::onMouseMove(int x, int y) {
	mx = (GLfloat)x / getViewportWidth() * -40 + 20;
	my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

MazeMinigame::MazeInstance::~MazeInstance() {

}
