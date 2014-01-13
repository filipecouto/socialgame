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
    drawSquare(-400,-81,400,400,-81,400,200,-81,-200,-200, -81,-200);
    glPushMatrix();
    glColor3f(0.46, 0.32, 0.1);
    drawLines(20.0,10.0, -80.0, 20.0,50.0, -80.0,20.0);
    drawLines(10.0,30.0, -80.0, 20.0,30.0, -80.0,-40.0);
    drawLines(10.0,30.0, -80.0,-40.0,70.0, -80.0,-40.0);
    drawLines(10.0,69.0, -80.0,-40.0,69.0, -80.0,-30.0);

    glColor3f(1, 1, 1);
    drawCircle(8.0, 69.0,-25.0);
    drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
    drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
    drawLines(5.0, 69.0, -80.0,-10.0, 79.0, -80.0,-15.0 );
    drawLines(5.0,  69.0, -80.0,5.0, 59.0, -80.0, 15.0 );
    drawLines(5.0,  69.0, -80.0,5.0, 79.0, -80.0, 15.0 );

    glColor3f(0,0,1);
    drawLetterSpaces(2);
    glColor3f(0,0,0);
   
   drawSquare(-98.0,-80.0,20.0,0,-80.0,20.0,0,-80.0,0,-100.0,-80.0,0);
    glPopMatrix();
    gui->drawGui();
}
void HangmanMinigame::HangmanInstance::drawLines(GLfloat width,
        GLfloat beginX, GLfloat beginY, GLfloat beginZ,
        GLfloat endX, GLfloat endY, GLfloat endZ)
{
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex3f(beginX, beginY,beginZ);
    glVertex3f(endX, endY,endZ);
    glEnd();
}

void HangmanMinigame::HangmanInstance::drawSquare(GLfloat v1x, GLfloat v1y, GLfloat v1z,
        GLfloat v2x, GLfloat v2y, GLfloat v2z,
        GLfloat v3x, GLfloat v3y, GLfloat v3z,
        GLfloat v4x, GLfloat v4y, GLfloat v4z)
{
    glBegin(GL_QUADS);
    glVertex3i(v1x,v1y,v1z);
    glVertex3i(v2x,v2y,v2z);
    glVertex3i(v3x,v3y,v3z);
    glVertex3i(v4x,v4y,v4z);
    glEnd();
}

void HangmanMinigame::HangmanInstance::drawCircle(double distance, double pX, double pZ)
{
    float salto = M_PI*2;
    float grau=0, x,z;
    glBegin(GL_POLYGON);
    int i =0;
    for(; i<100; i++)
    {
        grau+=(salto/100);
        x= -distance*cos(grau) + pX;
        z= distance*sin(grau) + pZ;
        glVertex3f(x, -79.0,z);
    }
    glEnd();
}

void HangmanMinigame::HangmanInstance::drawLetterSpaces(int length)
{
  GLfloat x = -100.0, y = -80.0, z =-40.0;
    for(int i =0; i<length; i++) {
        glLineWidth(3.0);
        glBegin(GL_LINES);
        glVertex3f(x,y,z);
	x+=5.0;
        glVertex3f(x,y,z);
        glEnd();
	x+=1.0;
    }
}

void HangmanMinigame::HangmanInstance::start() {
    mx = -17;
    my = 19;
    thing.x = thing.y = thing.vx = thing.vy = 0;
    camera.moveTo(0,10, 1);
    camera.lookAt(0, 1, 0);
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
    for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
        keys[i] = false;
    }
    gui = new Gui();
    gui->addWidget(new TextWidget("Ritinha!!!", 0, 0));
}

void HangmanMinigame::HangmanInstance::finish() {
    //  _context->notifyMinigameFinished(this);
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

bool HangmanMinigame::HangmanInstance::determinateLetter(char chosenLetter, string word)
{
	return true;
}


