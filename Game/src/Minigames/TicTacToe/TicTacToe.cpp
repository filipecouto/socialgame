#include "TicTacToe.h"
#include "../../GameContext.h"

TicTacToeMinigame::TicTacToeMinigame(GameContext * context) : _context(context) {

}

std::string TicTacToeMinigame::getName() {
	return "Tic Tac Toe";
}

IMinigameInstance * TicTacToeMinigame::newGame() {
	return new TicTacToeInstance(_context);
}

void TicTacToeMinigame::TicTacToeInstance::draw() {
	camera.setUp();

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	glVertex3i(-20, 0, 20);
	glVertex3i(20, 0, 20);
	glVertex3i(20, 0, -20);
	glVertex3i(-20, 0, -20);
	glEnd();

	/*glPushMatrix();
	glColor3f(0.2, 0.6, 0.9);
	glTranslatef(mx - 0.5f, 1, my - 0.5f);
	glutSolidTeapot(1);
	glPopMatrix();*/

	/*glColor3f(1.0, 0.6, 0.0);
	glTranslatef(thing.x, 2, thing.y);
	glutSolidSphere(2, 32, 32);*/

	glPushMatrix();
		glPushMatrix();
			//glTranslatef(12, 0, 0);
			drawX();
		glPopMatrix();

		glPushMatrix();
			//Right External Line
			drawLine();
		glPopMatrix();
		glPushMatrix();
			//Left External Line
			glTranslatef(9.8, 0, 0);
			drawLine();
		glPopMatrix();
		glPushMatrix();
			//Right Internal Line
			glTranslatef(3.3, 0, 0);
			drawLine();
		glPopMatrix();
		glPushMatrix();
			//Left Internal Line
			glTranslatef(6.7, 0, 0);
			drawLine();
		glPopMatrix();

		glPushMatrix();
			//Upper External Line
			glTranslatef(5, 14.8, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();
		glPushMatrix();
			//Lower External Line
			glTranslatef(5, 5, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();
		glPushMatrix();
			//Lower Internal Line
			glTranslatef(5, 5 + 3.3, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();
		glPushMatrix();
			//Upper Internal Line
			glTranslatef(5, 5 + 6.7, 0);
			glRotatef(90, 0.0, 0.0, 1.0);
			drawLine(0.1);
		glPopMatrix();

		/*glPushMatrix();
			//Base
			glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_QUADS);
			glVertex3i(-5, 0, -15);
			glVertex3i(-5, 10, -15);
			glVertex3i(5, 10, -15);
			glVertex3i(5, 0, -15);
			glEnd();
		glPopMatrix();*/
	glPopMatrix();
}

void TicTacToeMinigame::TicTacToeInstance::drawLine(GLfloat addZ){
	glColor3f(0.5, 0.1, 0.8);
	glBegin(GL_QUADS);
		glVertex3f(-5, 0, -15 - addZ);
		glVertex3f(-5, 10, -15 - addZ);
		glVertex3f(-4.8, 10, -15 - addZ);
		glVertex3f(-4.8, 0, -15 - addZ);
	glEnd();
}

void TicTacToeMinigame::TicTacToeInstance::drawX(){
	glColor3f(0.2, 0.6, 0.3);
	glRotatef(45, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(-5, 0, -18);
		glVertex3f(-5, 2, -18);
		glVertex3f(-4, 2, -18);
		glVertex3f(-4, 0, -18);
	glEnd();
}

void TicTacToeMinigame::TicTacToeInstance::drawO(){

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

	if (keys[1]) camera.rotate(0.0, 1.0, 0.0);
	if (keys[3]) camera.rotate(0.0, -1.0, 0.0);
	

	/*if (keys[1]) thing.vx += 0.005;

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
		my - 1.0f <= thing.y && my + 1.0f >= thing.y) finish();*/
}

TicTacToeMinigame::TicTacToeInstance::TicTacToeInstance(GameContext * context) : _context(context) {
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++){
		keys[i] = false;
	}
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
	if (state == 1){
		if (mx >= 2.6 && mx <= 6.75 &&
			my >= 6 && my <= 13.3){
			printf("<-----------1---------->");
		}

		if (mx >= -2.0 && mx <= 2.3 &&
			my >= 6 && my <= 13.3){
			printf("<-----------2---------->");
		}

		if (mx >= -6.75 && mx <= -2.3 &&
			my >= 6 && my <= 13.3){
			printf("<-----------3---------->");
		}

		if (mx >= 2.4 && mx <= 6.0 &&
			my >= -1.6 && my <= 5.4){
			printf("<-----------4---------->");
		}

		if (mx >= -1.8 && mx <= 2.1 &&
			my >= -1.6 && my <= 5.4){
			printf("<-----------5---------->");
		}

		if (mx >= -6.0 && mx <= -2.1 &&
			my >= -1.6 && my <= 5.4){
			printf("<-----------6---------->");
		}

		if (mx >= 2.2 && mx <= 6.0 &&
			my >= -8.0 && my <= -2.1){
			printf("<-----------7---------->");
		}

		if (mx >= -1.7 && mx <= 2.0 &&
			my >= -8.0 && my <= -2.1){
			printf("<-----------8---------->");
		}

		if (mx >= -5.6 && mx <= -2.0 &&
			my >= -8.0 && my <= -2.1){
			printf("<-----------9---------->");
		}

		printf("%f %f\n", mx, my);
	}
	
}

void TicTacToeMinigame::TicTacToeInstance::onMouseMove(int x, int y) {
	mx = (GLfloat)x / getViewportWidth() * -40 + 20;
	my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

TicTacToeMinigame::TicTacToeInstance::~TicTacToeInstance() {

}
