#include "TicTacToe.h"
#include "../../GameContext.h"

TicTacToeMinigame::TicTacToeMinigame(GameContext * context) : _context(context) {

}

std::string TicTacToeMinigame::getName() {
	return "Test minigame";
}

IMinigameInstance * TicTacToeMinigame::newGame() {
	return new TestInstance(_context);
}

void TicTacToeMinigame::TicTacToeInstance::draw() {
	camera.setUp();

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	glVertex3i(-20, 0,  20);
	glVertex3i(20, 0,  20);
	glVertex3i(20, 0, -20);
	glVertex3i(-20, 0, -20);
	glEnd();
	
	glPushMatrix();
	glColor3f(0.2, 0.6, 0.9);
	glTranslatef(mx - 0.5f, 1, my - 0.5f);
	glutSolidTeapot(1);
	glPopMatrix();

	glColor3f(1.0, 0.6, 0.0);
	glTranslatef(thing.x, 2, thing.y);
	glutSolidSphere(2, 32, 32);
}

void TicTacToeMinigame::TicTacToeInstance::start() {
	mx = -17;
	my = 19;
	thing.x = thing.y = thing.vx = thing.vy = 0;
	camera.moveTo(0, 8, -28);
	camera.lookAt(0, 0, 0);
}

void TicTacToeMinigame::TicTacToeInstance::tick(int delta, int current) {
	camera.tick(delta, current);

	if (keys[1]) thing.vx += 0.005;

	if (keys[3]) thing.vx -= 0.005;

	if (keys[0]) thing.vy += 0.005;

	if (keys[2]) thing.vy -= 0.005;

	thing.x += thing.vx * delta;
	thing.y += thing.vy * delta;

	thing.vx *= 0.75;
	thing.vy *= 0.75;

	if (thing.x < -20) thing.x = -20;
	else if (thing.x > 20) thing.x = 20;

	if (thing.y < -20) thing.y = -20;
	else if (thing.y > 20) thing.y = 20;
	
	if(mx - 1.0f <= thing.x && mx + 1.0f >= thing.x &&
		my - 1.0f <= thing.y && my + 1.0f >= thing.y) finish();
}

TicTacToeMinigame::TicTacToeInstance::TicTacToeInstance(GameContext * context) : _context(context) {

}

void TicTacToeMinigame::TicTacToeInstance::finish() {
	_context->notifyMinigameFinished(this);
}

void TicTacToeMinigame::TicTacToeInstance::onKeyDown(int key, int special) {
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

void TicTacToeMinigame::TicTacToeInstance::onKeyUp(int key, int special) {
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
}

void TicTacToeMinigame::TicTacToeInstance::onMouseButton(int state, int button, int x, int y) {
}

void TicTacToeMinigame::TicTacToeInstance::onMouseMove(int x, int y) {
	mx = (GLfloat)x / getViewportWidth() * -40 + 20;
	my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

TicTacToeMinigame::TicTacToeInstance::~TicTacToeInstance() {

}
