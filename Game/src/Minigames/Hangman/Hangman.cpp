#include "Hangman.h"
#include "../../GameContext.h"

HangmanMinigame::HangmanMinigame(GameContext* context): _context(context)
{

}

std::string HangmanMinigame::getName()
{
    return "Hangman";
}

IMinigameInstance* HangmanMinigame::newGame()
{
    return new HangmanInstance(_context);
}

void HangmanMinigame::HangmanInstance::draw() {
	camera.setUp();

	glColor3f(0, 0.25, 0);
	glBegin(GL_QUADS);
	glVertex3i(-20, 0,  20);
	glVertex3i(20, 0,  20);
	glVertex3i(20, 0, -20);
	glVertex3i(-20, 0, -20);
	glEnd();
	
	glPushMatrix();
	glColor3f(0.46, 0.32, 0.1);/*
	glTranslatef(thing.x, 2, thing.y);*/
	glBegin(GL_LINE);
	glPopMatrix();

	glColor3f(1.0, 0.6, 0.0);
// 	
// 	glutSolidSphere(2, 32, 32);
}

void HangmanMinigame::HangmanInstance::start() {
	mx = -17;
	my = 19;
	thing.x = thing.y = thing.vx = thing.vy = 0;
	camera.moveTo(0,10, 1);
	camera.lookAt(0, 0, 0);
// 	camera.moveTo(0, 8, -28);
// 	camera.lookAt(0, 0, 0);
}

void HangmanMinigame::HangmanInstance::tick(int delta, int current) {
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

HangmanMinigame::HangmanInstance::HangmanInstance(GameContext * context) : _context(context) {
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++){
		keys[i] = false;
	}
}

void HangmanMinigame::HangmanInstance::finish() {
	_context->notifyMinigameFinished(this);
}

void HangmanMinigame::HangmanInstance::onKeyDown(int key, int special) {
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

void HangmanMinigame::HangmanInstance::onKeyUp(int key, int special) {
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

void HangmanMinigame::HangmanInstance::onMouseButton(int state, int button, int x, int y) {
}

void HangmanMinigame::HangmanInstance::onMouseMove(int x, int y) {
	mx = (GLfloat)x / getViewportWidth() * -40 + 20;
	my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

HangmanMinigame::HangmanInstance::~HangmanInstance() {

}
