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
	glEnable(GL_LIGHTING);
	
	camera.setUp();
	
	int width = maze->getWidth(), height = maze->getHeight();
	double * start = maze->getStart();
	int * end = maze->getEnd();
	
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {	
			if(maze->getValue(i,j)) {
				glPushMatrix();
					glTranslatef(i,0,j);
					glColor3f(0,0,1);
					drawCube();
				glPopMatrix();
			}
		}
	}
	glPushMatrix();
		glTranslatef(start[0],0,start[1]);
		glRotatef(-rotateAngle , rotateX, 0 , rotateZ);
		glColor3f(0,1,0);
		drawCube();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(end[0],0,end[1]);
		glColor3f(1,0,0);
		drawCube();
	glPopMatrix();
}

void MazeMinigame::MazeInstance::drawCube() {
		glutSolidCube(1);
}

void MazeMinigame::MazeInstance::start() {
	camera.lookAt(5,0.5f,5);
	camera.moveTo(1,10,1);
}

bool MazeMinigame::MazeInstance::detectCollision() {
	return true;
}

void MazeMinigame::MazeInstance::tick(int delta, int current) {
	camera.tick(delta, current);
	double * actual = maze->getStart();
	camera.moveTo(actual[0],10,actual[1]-2);
	camera.lookAt(actual[0],0.5,actual[1]);
	GLfloat light_pos[4] =	{actual[0],10,actual[1]-2, 0.0};
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[] =	{ 0.5f, 0.5f, 0.5f, 1.0f };
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	
	bool pressed = false;
	for(int i = 0; i < 4; i++) {
		pressed = rotating[i];
		if(pressed) break;
	}
	double rotateValueX = 0;
	double rotateValueZ = 0;
	
	if(!pressed && rotateAngle != 0) {
		if(rotateAngle >= 90 || rotateAngle <= -90) {
			cleanRotate();
		} else {
			if(rotateAngle > 45) {
				rotateAngle+=9;
				if(rotateX == 1) {
					rotateValueX = -0.1;
				} else if(rotateZ == 1) {
					rotateValueZ = 0.1;
				}
			} else if(rotateAngle < -45) {
				rotateAngle-=9;
				if(rotateX == 1) {
					rotateValueX = 0.1;
				} else if(rotateZ == 1) {
					rotateValueZ = -0.1;
				}
			} else if(rotateAngle > 0) {
				rotateAngle-=9;
				if(rotateX == 1) {
					rotateValueX = 0.1;
				} else if(rotateZ == 1) {
					rotateValueZ = -0.1;
				}
			} else if(rotateAngle < 0) {
				rotateAngle+=9;
				if(rotateX == 1) {
					rotateValueX = -0.1;
				} else if(rotateZ == 1) {
					rotateValueZ = 0.1;
				}
			}
		}
	}
	maze->addStart(rotateValueZ, rotateValueX);
}

MazeMinigame::MazeInstance::MazeInstance(GameContext * context) : _context(context) {
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++){
		keys[i] = false;
	}
	
	maze = new Maze(30,20);
	maze->generate();
	cleanRotate();
	cleanKeys();
}

void MazeMinigame::MazeInstance::finish() {
	_context->notifyMinigameFinished(this);
}

bool MazeMinigame::MazeInstance::isRotating(int pos) {
	if(pos == 0 && rotating[2]) return false;
	if(pos == 1 && rotating[3]) return false;
	if(pos == 2 && rotating[0]) return false;
	if(pos == 3 && rotating[1]) return false;
	for(int i = 0; i < 4; i++) {
		if(i!=pos && rotating[i]) return true;
	}
	return false;
}

void MazeMinigame::MazeInstance::applyRotating(int pos) {
	for(int i = 0; i < 4; i++) {
		rotating[i] = i == pos;
	}
}

void MazeMinigame::MazeInstance::onKeyDown(int key, int special) {
	double * pos = maze->getStart();
	int * end = maze->getEnd();
	switch (key) {
		case 'w':
			keys[0] = true;
			if(floor(pos[1]+1) >= maze->getHeight() || isRotating(0)) {
				break;
			}
			if(!maze->getValue(pos[0],floor(pos[1]+1))) {
				maze->addStart(0,0.1);
				rotateX = 1;
				rotateZ = 0;
				rotateAngle-=9;
				applyRotating(0);
			}
			break;
		case 'a':
			keys[1] = true;
			if(floor(pos[0]+1) >= maze->getWidth() || isRotating(1)) {
				break;
			}
			if(!maze->getValue(floor(pos[0]+1),pos[1])) {
				maze->addStart(0.1,0);
				rotateZ = 1;
				rotateX = 0;
				rotateAngle+=9;
				applyRotating(1);
			}
			break;
		case 's':
			keys[2] = true;
			if(ceil(pos[1]-1) < 0 || isRotating(2)) {
				break;
			}
			if(!maze->getValue(pos[0],ceil(pos[1]-1))) {
				maze->addStart(0,-0.1);
				rotateX = 1;
				rotateZ = 0;
				rotateAngle+=9;
				applyRotating(2);
			}
			break;

		case 'd':
			keys[3] = true;
			if(ceil(pos[0]-1) < 0 || isRotating(3)) {
				break;
			}
			if(!maze->getValue(ceil(pos[0]-1),pos[1])) {
				maze->addStart(-0.1,0);
				rotateZ = 1;
				rotateX = 0;
				rotateAngle-=9;
				applyRotating(3);
			}
			break;
	}
	
	if(rotateAngle>=90 || rotateAngle<=-90) cleanRotate();
	
	if(pos[0] == end[0] && pos[1] == end[1]) finish();
	
}

void MazeMinigame::MazeInstance::cleanRotate() {
	rotateAngle = 0;
	double * start = maze->getStart();
	start[0] = round(start[0]);
	start[1] = round(start[1]);
	maze->setStart(start[0], start[1]);
}

void MazeMinigame::MazeInstance::cleanKeys() {
	for(int i = 0; i < 4; i++) {
		rotating[i] = false;
	}
}

void MazeMinigame::MazeInstance::onKeyUp(int key, int special) {
	double * pos = maze->getStart();
	int * end = maze->getEnd();
	switch(key) {
		case 'w':
			keys[0] = false;
			cleanKeys();
			break;
		case 'a':
			keys[1] = false;
			cleanKeys();
			break;
		case 's':
			keys[2] = false;
			cleanKeys();
			break;

		case 'd':
			keys[3] = false;
			cleanKeys();
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
