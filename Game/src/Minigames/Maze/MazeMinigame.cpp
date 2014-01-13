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
	glEnable(GL_COLOR_MATERIAL);

	camera.setUp();

	int width = maze->getWidth(), height = maze->getHeight();
	int * end = maze->getEnd();
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (maze->getValue(i, j)) {
				glPushMatrix();
					glTranslatef(i, 0, j);
					glColor3f(1, 1, 1);
					glEnable(GL_TEXTURE_2D);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, textureId1);
					drawCube(1);
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			} else {
				glPushMatrix();
					glTranslatef(i, 0, j);
					glColor3f(1, 1, 1);
					glEnable(GL_TEXTURE_2D);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, textureId2);
					drawFloor();
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}

	glPushMatrix();
	glTranslatef(pos[0] + tx, 0, pos[1] + ty);
	glRotatef(rotateX, 0, 0, 1);
	glRotatef(rotateZ, 1, 0, 0);
	glColor3f(0, 1, 0);
	drawCube(0.9);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(end[0], 0, end[1]);
	glColor3f(1, 0, 0);
	drawCube(0.9);
	glPopMatrix();
}

void MazeMinigame::MazeInstance::drawCube(double size) {
	double halfSize = size / 2;
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,1);
		glVertex3f(-halfSize,size,halfSize);
		glTexCoord2f(1,1);
		glVertex3f(halfSize,size,halfSize);
		glTexCoord2f(0,0);
		glVertex3f(-halfSize,size,-halfSize);
		glTexCoord2f(1,0);
		glVertex3f(halfSize,size,-halfSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,1);
		glVertex3f(-halfSize,0,-halfSize);
		glTexCoord2f(1,1);
		glVertex3f(halfSize,0,-halfSize);
		glTexCoord2f(0,0);
		glVertex3f(-halfSize,0,halfSize);
		glTexCoord2f(1,0);
		glVertex3f(halfSize,0,halfSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,1);
		glVertex3f(-halfSize,size,halfSize);
		glTexCoord2f(1,1);
		glVertex3f(-halfSize,size,-halfSize);
		glTexCoord2f(0,0);
		glVertex3f(-halfSize,0,halfSize);
		glTexCoord2f(1,0);
		glVertex3f(-halfSize,0,-halfSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,1);
		glVertex3f(halfSize,size,-halfSize);
		glTexCoord2f(1,1);
		glVertex3f(halfSize,size,halfSize);
		glTexCoord2f(0,0);
		glVertex3f(halfSize,0,halfSize);
		glTexCoord2f(1,0);
		glVertex3f(halfSize,0,-halfSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,1);
		glVertex3f(-halfSize,size,-halfSize);
		glTexCoord2f(1,1);
		glVertex3f(halfSize,size,-halfSize);
		glTexCoord2f(0,0);
		glVertex3f(-halfSize,0,-halfSize);
		glTexCoord2f(1,0);
		glVertex3f(halfSize,0,-halfSize);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,1);
		glVertex3f(halfSize,size,halfSize);
		glTexCoord2f(1,1);
		glVertex3f(-halfSize,size,halfSize);
		glTexCoord2f(0,0);
		glVertex3f(halfSize,0,halfSize);
		glTexCoord2f(1,0);
		glVertex3f(-halfSize,0,halfSize);
	glEnd();
}

void MazeMinigame::MazeInstance::drawFloor() {
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0,1);
		glVertex3f(-0.5,0,0.5);
		glTexCoord2f(1,1);
		glVertex3f(0.5,0,0.5);
		glTexCoord2f(0,0);
		glVertex3f(-0.5,0,-0.5);
		glTexCoord2f(1,0);
		glVertex3f(0.5,0,-0.5);
	glEnd();
}

void MazeMinigame::MazeInstance::start() {
	camera.lookAt(0, 0.5f, 0);
	camera.moveTo(0, 8, 4);

	int * start = maze->getStart();
	pos[0] = start[0];
	pos[1] = start[1];

	tx = 0;
	ty = 0;
	
	textureId1 = _context->loadTexture("maze_walls.jpg");
	textureId2 = _context->loadTexture("maze_floor.jpg");
}

bool MazeMinigame::MazeInstance::detectCollision() {
	return true;
}

void MazeMinigame::MazeInstance::tick(int delta, int current) {
	camera.tick(delta, current);
	GLfloat x = pos[0] + tx;
	GLfloat y = pos[1] + ty;
	camera.moveTo(x, 8, y - 4);
	camera.lookAt(x, 0.5, y);
	GLfloat light_pos[4] = {x, 0.5, y, 0};
	GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 1.0f, 0.8f, 1.0f };
	GLfloat light_specular[] = { 0.8f, 1.0f, 0.8f, 1.0f };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat d = delta / 4.0;

	bool changedX = false, changedZ = false;

	if (keys[0]) {
		rotateZ += d;
		changedZ = true;
	}

	if (keys[1]) {
		rotateX -= d;
		changedX = true;
	}

	if (keys[2]) {
		rotateZ -= d;
		changedZ = true;
	}

	if (keys[3]) {
		rotateX += d;
		changedX = true;
	}

	d *= 1.5f;

	if (!changedX) {
		if (rotateX < -d && rotateX > -45 || rotateX > d && rotateX > 45) rotateX += d;
		else if (rotateX > d && rotateX < 45 || rotateX < -d && rotateX < -45) rotateX -= d;
		else rotateX = 0;
	}

	if (!changedZ) {
		if (rotateZ < -d && rotateZ > -45 || rotateZ > d && rotateZ > 45) rotateZ += d;
		else if (rotateZ > d && rotateZ < 45 || rotateZ < -d && rotateZ < -45) rotateZ -= d;
		else rotateZ = 0;
	}

	while (rotateZ >= 90) {
		rotateZ -= 90;
		pos[1]++;
	}

	while (rotateZ <= -90) {
		rotateZ += 90;
		pos[1]--;
	}

	while (rotateX <= -90) {
		rotateX += 90;
		pos[0]++;
	}

	while (rotateX >= 90) {
		rotateX -= 90;
		pos[0]--;
	}
	
	tx = - rotateX / 90;
	ty = rotateZ / 90;
	
	if(maze->getValue(ceil(pos[0]+tx), ceil(pos[1]+ty)) || maze->getValue(floor(pos[0]+tx), floor(pos[1]+ty))) {
		tx = 0;
		ty = 0;
		rotateX = 0;
		rotateZ = 0;
	}
}

MazeMinigame::MazeInstance::MazeInstance(GameContext * context) : _context(context) {
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
		keys[i] = false;
	}

	maze = new Maze(31, 21);
	maze->generate();
	cleanRotate();
	cleanKeys();
}

void MazeMinigame::MazeInstance::finish() {
	_context->notifyMinigameFinished(this);
}

bool MazeMinigame::MazeInstance::isRotating(int pos) {
	if (pos == 0 && keys[2]) return false;

	if (pos == 1 && keys[3]) return false;

	if (pos == 2 && keys[0]) return false;

	if (pos == 3 && keys[1]) return false;

	for (int i = 0; i < 4; i++) {
		if (i != pos && keys[i]) return true;
	}

	return false;
}

void MazeMinigame::MazeInstance::applyRotating(int pos) {
	for (int i = 0; i < 4; i++) {
		rotating[i] = i == pos;
	}
}

void MazeMinigame::MazeInstance::onKeyDown(int key, int special) {
	int * end = maze->getEnd();

	switch (key) {
		case 'w':
			keys[0] = !isRotating(0);
			break;

		case 'a':
			keys[1] = !isRotating(1);
			break;

		case 's':
			keys[2] = !isRotating(2);
			break;

		case 'd':
			keys[3] = !isRotating(3);
			break;
	}
}

void MazeMinigame::MazeInstance::cleanRotate() {
}

void MazeMinigame::MazeInstance::cleanKeys() {
	for (int i = 0; i < 4; i++) {
		rotating[i] = false;
	}
}

void MazeMinigame::MazeInstance::onKeyUp(int key, int special) {
	switch (key) {
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

	if (maze->isEnd(pos[0], pos[1])) finish();
}

void MazeMinigame::MazeInstance::onMouseButton(int state, int button, int x, int y) {
}

void MazeMinigame::MazeInstance::onMouseMove(int x, int y) {
	mx = (GLfloat)x / getViewportWidth() * -40 + 20;
	my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

MazeMinigame::MazeInstance::~MazeInstance() {

}
