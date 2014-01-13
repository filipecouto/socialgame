#include "MazeMinigame.h"
#include "../../GameContext.h"

MazeMinigame::MazeMinigame(GameContext * context) : _context(context) {

}

std::string MazeMinigame::getInternalName() {
	return "crosswebenterprise.maze";
}

std::string MazeMinigame::getName() {
	return "Maze Game";
}

std::string MazeMinigame::getDescription() {
	return "Challenge your friends with 3 different levels of mazes!";
}

IMinigameInstance * MazeMinigame::newGame() {
	return new MazeInstance(_context);
}

void MazeMinigame::MazeInstance::draw() {
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	camera.setUp();

	int * end = maze->getEnd();

	if(textures) {
		glEnable(GL_TEXTURE_2D);
		colors[0] = 1;
		colors[1] = 1;
		colors[2] = 1;
		deleteList();
		createList();
	} else {
		glDisable(GL_TEXTURE_2D);
		colors[0] = 0;
		colors[1] = 0;
		colors[2] = 1;
		deleteList();
		createList();
	}

	glActiveTexture(GL_TEXTURE0);
	glCallList(mazeList);


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
	
	glDisable(GL_TEXTURE_2D);
}

static GLfloat n[6][3] = {
	{ -1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{1.0, 0.0, 0.0},
	{0.0, -1.0, 0.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, -1.0}
};
static GLint faces[6][4] = {
	{0, 1, 2, 3},
	{3, 2, 6, 7},
	{7, 6, 5, 4},
	{4, 5, 1, 0},
	{5, 6, 2, 1},
	{7, 4, 0, 3}
};

void MazeMinigame::MazeInstance::drawCube(double size) {
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for(i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0, 1);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(1, 1);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1, 0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(0, 0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void MazeMinigame::MazeInstance::drawFloor() {
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 1);
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);
	glNormal3f(0, 1, 0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(0.5, -0.5, -0.5);
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

	createList();
}

void MazeMinigame::MazeInstance::deleteList() {
	glDeleteLists(mazeList,1);
}

void MazeMinigame::MazeInstance::createList() {
	mazeList = glGenLists(1);
	glNewList(mazeList, GL_COMPILE);
		int width = maze->getWidth(), height = maze->getHeight();
		glBindTexture(GL_TEXTURE_2D, textureId1);
		for(int i = 0; i < width; i++) {
			for(int j = 0; j < height; j++) {
				if(maze->getValue(i, j)) {
					glPushMatrix();
					glTranslatef(i, 0, j);
					glColor3f(colors[0], colors[1], colors[2]);
					drawCube(1);
					glPopMatrix();
				}
			}
		}

		glBindTexture(GL_TEXTURE_2D, textureId2);
		for(int i = 0; i < width; i++) {
			for(int j = 0; j < height; j++) {
				if(!maze->getValue(i, j)) {
					glPushMatrix();
					glTranslatef(i, 0, j);
					glColor3f(colors[0], colors[1], colors[2]);
					drawFloor();
					glPopMatrix();
				}
			}
		}
	glEndList();
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

	if(keys[0]) {
		rotateZ += d;
		changedZ = true;
	}

	if(keys[1]) {
		rotateX -= d;
		changedX = true;
	}

	if(keys[2]) {
		rotateZ -= d;
		changedZ = true;
	}

	if(keys[3]) {
		rotateX += d;
		changedX = true;
	}

	d *= 1.5f;

	if(!changedX) {
		if(rotateX < -d && rotateX > -45 || rotateX > d && rotateX > 45) rotateX += d;
		else if(rotateX > d && rotateX < 45 || rotateX < -d && rotateX < -45) rotateX -= d;
		else rotateX = 0;
	}

	if(!changedZ) {
		if(rotateZ < -d && rotateZ > -45 || rotateZ > d && rotateZ > 45) rotateZ += d;
		else if(rotateZ > d && rotateZ < 45 || rotateZ < -d && rotateZ < -45) rotateZ -= d;
		else rotateZ = 0;
	}

	int oldX = pos[0];
	int oldY = pos[1];

	while(rotateZ >= 90) {
		rotateZ -= 90;
		pos[1]++;
	}

	while(rotateZ <= -90) {
		rotateZ += 90;
		pos[1]--;
	}

	while(rotateX <= -90) {
		rotateX += 90;
		pos[0]++;
	}

	while(rotateX >= 90) {
		rotateX -= 90;
		pos[0]--;
	}

	tx = - rotateX / 90;
	ty = rotateZ / 90;

	if(maze->getValue(ceil(pos[0] + tx - 0.08f), pos[1]) || maze->getValue(floor(pos[0] + tx + 0.08f), pos[1])) {
		pos[0] = oldX;

		if(tx < -0.05f) tx = -0.05f;
		else if(tx > 0.05f) tx = 0.05f;

		rotateX = -90 * tx;
	}

	if(maze->getValue(pos[0], ceil(pos[1] + ty - 0.08f)) || maze->getValue(pos[0], floor(pos[1] + ty + 0.08f))) {
		pos[1] = oldY;

		if(ty < -0.05f) ty = -0.05f;
		else if(ty > 0.05f) ty = 0.05f;

		rotateZ = 90 * ty;
	}

	if(maze->isEnd(pos[0], pos[1])) finish();
}

MazeMinigame::MazeInstance::MazeInstance(GameContext * context) : _context(context) {
	for(int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
		keys[i] = false;
	}

	textures = false;
	maze = new Maze(31, 21);
	maze->generate();
	cleanRotate();
	cleanKeys();
}

void MazeMinigame::MazeInstance::finish() {
	_context->notifyMinigameFinished(this);
}


void MazeMinigame::MazeInstance::applyRotating(int pos) {
	for(int i = 0; i < 4; i++) {
		rotating[i] = i == pos;
	}
}

void MazeMinigame::MazeInstance::onKeyDown(int key, int special) {
	int * end = maze->getEnd();

	switch(key) {
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
		case 't':
			textures = !textures;
			break;
	}
}

void MazeMinigame::MazeInstance::cleanRotate() {
}

void MazeMinigame::MazeInstance::cleanKeys() {
	for(int i = 0; i < 4; i++) {
		rotating[i] = false;
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
