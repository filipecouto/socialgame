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
	
	int width = maze->getWidth(), height = maze->getHeight();
	int * start = maze->getStart();
	int * end = maze->getEnd();
	
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {	
			if(maze->getValue(i,j)) {
				glPushMatrix();
					glTranslatef(i,j,0);
					glColor3f(0,0,1);
					drawCube();
				glPopMatrix();
			} else {
				if(start[0] == i && start[1] == j) {
					glPushMatrix();
						glTranslatef(i,j,0);
						glColor3f(0,1,0);
						drawCube();
					glPopMatrix();
				} else if(end[0] == i && end[1] == j) {
					glPushMatrix();
						glTranslatef(i,j,0);
						glColor3f(1,0,0);
						drawCube();
					glPopMatrix();
				}
			}
		}
	}
	camera.moveTo(start[0],start[1],1);
	camera.lookAt(0,0,0);
	
}

void MazeMinigame::MazeInstance::drawCube() {
	glBegin(GL_TRIANGLE_STRIP); // bottom
		glVertex3f(1.0,1.0,0.0);
		glVertex3f(1.0,0.0,0.0);
		glVertex3f(0.0,1.0,0.0);
		glVertex3f(0.0,0.0,0.0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(1.0,1.0,1.0);
		glVertex3f(1.0,0.0,1.0);
		glVertex3f(0.0,1.0,1.0);
		glVertex3f(0.0,0.0,1.0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(1.0,0.0,0.0);
		glVertex3f(0.0,0.0,1.0);
		glVertex3f(1.0,0.0,1.0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0,1.0,0.0);
		glVertex3f(1.0,1.0,0.0);
		glVertex3f(0.0,1.0,1.0);
		glVertex3f(1.0,1.0,1.0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(1.0,1.0,1.0);
		glVertex3f(1.0,1.0,0.0);
		glVertex3f(1.0,0.0,1.0);
		glVertex3f(1.0,0.0,0.0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0.0,1.0,1.0);
		glVertex3f(0.0,1.0,0.0);
		glVertex3f(0.0,0.0,1.0);
		glVertex3f(0.0,0.0,0.0);
	glEnd();
	
	
}

void MazeMinigame::MazeInstance::start() {
	camera.moveTo(0,-5,1);
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
	maze = new Maze(30,20);
	maze->generate();
}

void MazeMinigame::MazeInstance::finish() {
	_context->notifyMinigameFinished(this);
}

void MazeMinigame::MazeInstance::onKeyDown(int key, int special) {
	int * pos = maze->getStart();
	int * end = maze->getEnd();
	switch (key) {
		case 'w':
			keys[0] = true;
			if(pos[1]+1 >= maze->getHeight()) {
				break;
			}
			if(!maze->getValue(pos[0],pos[1]+1)) {
				maze->addStart(0,1);
			}
			break;
		case 'a':
			keys[1] = true;
			if(pos[0]+1 >= maze->getWidth()) {
				break;
			}
			if(!maze->getValue(pos[0]+1,pos[1])) {
				maze->addStart(1,0);
			}
			break;
		case 's':
			keys[2] = true;
			if(pos[1]-1 < 0) {
				break;
			}
			if(!maze->getValue(pos[0],pos[1]-1)) {
				maze->addStart(0,-1);
			}
			break;

		case 'd':
			keys[3] = true;
			if(pos[0]-1 < 0) {
				break;
			}
			if(!maze->getValue(pos[0]-1,pos[1])) {
				maze->addStart(-1,0);
			}
			break;
	}
	if(pos[0] == end[0] && pos[1] == end[1]) finish();
	
}

void MazeMinigame::MazeInstance::onKeyUp(int key, int special) {
	int * pos = maze->getStart();
	int * end = maze->getEnd();
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
	if(pos[0] == end[0] && pos[1] == end[1]) finish();
}

void MazeMinigame::MazeInstance::onMouseButton(int state, int button, int x, int y) {
}

void MazeMinigame::MazeInstance::onMouseMove(int x, int y) {
	mx = (GLfloat)x / getViewportWidth() * -40 + 20;
	my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

MazeMinigame::MazeInstance::~MazeInstance() {

}
