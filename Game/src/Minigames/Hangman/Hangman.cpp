#include "Hangman.h"
#include "../../GameContext.h"
#include <string.h>

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

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId1);
    drawSquare(-20, 0,  20,20, 0,  20,20, 0, -20,-20, 0, -20);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(0.46, 0.32, 0.1);
    glTranslatef(-2,0,-10);

    glutSolidCube(5);
    glTranslatef(0,12,0);
    glRotated(90,1,0,0);
    gluCylinder(quad,1,1,12,20,2);
    glTranslatef(0,6,0);
    glRotated(-90,0,1,0);

    gluCylinder(quad,1,1,12,20,2);
    glTranslatef(0,-1,10);
    glRotated(90,0,1,0);
    gluCylinder(quad,1,1,3,20,2);
    glRotated(-360,0,1,0);
    glColor3f(1, 1, 1);
    glTranslatef(0,0,3.4);
    
    glPushMatrix();
      glPushMatrix();
      glutSolidSphere(2, 32, 32);
      glPopMatrix();
      
      glPushMatrix();
      gluCylinder(quad,0.5,0.5,10,20,1);
      glPopMatrix();
      glPushMatrix();
	glPushMatrix();
	glRotated(45,0,1,0);
	glTranslatef(0,-3,1);
	gluCylinder(quad,0.1,0.1,5,20,1);
	glPopMatrix();
	glPushMatrix();
	 glColor3f(0, 1, 0);
	glRotated(135,0,1,0);
	glTranslatef(0,0,0);
	gluCylinder(quad,0.1,0.1,7,20,1);
	glPopMatrix();
	glPushMatrix();
	glRotated(-90,0,1,0);
	glTranslatef(0,7,1);
	gluCylinder(quad,0.1,0.1,5,20,1);
	glPopMatrix();
      glPopMatrix();
    glPopMatrix();
    drawHangman();

    glColor3f(0,0,1);
    drawLetterSpaces(word.length());
    glColor3f(0,0,0);
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
    int x = 43;
    for(int i=0; i<wordLength; i++) {
        letters.push_back(new LetterWidget(" ",x,380));
        x+=22;
    }


}

void HangmanMinigame::HangmanInstance::drawHangman()
{
    glColor3f(1, 1, 1);
    switch(attempts) {
    case 6:
        drawCircle(8.0, 69.0,-25.0);
        break;
    case 5:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        break;
    case 4:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        break;
    case 3:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 79.0, -80.0,-15.0 );
        break;
    case 2:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 79.0, -80.0,-15.0 );
        drawLines(5.0,  69.0, -80.0,5.0, 59.0, -80.0, 15.0 );
        break;
    case 1:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 79.0, -80.0,-15.0 );
        drawLines(5.0,  69.0, -80.0,5.0, 59.0, -80.0, 15.0 );
        drawLines(5.0,  69.0, -80.0,5.0, 79.0, -80.0, 15.0 );
        break;
    }

}

void HangmanMinigame::HangmanInstance::start(int level) {
    mx = -17;
    my = 19;
    thing.x = thing.y = thing.vx = thing.vy = 0;
    camera.moveTo(0, 8, -28);
    camera.lookAt(0, 0, 0);
// 	camera.moveTo(0, 8, -28);
// 	camera.lookAt(0, 0, 0);
}

void HangmanMinigame::HangmanInstance::tick(int delta, int current) {
    camera.tick(delta, current);
    gui->tick(delta,current);
    gui->setDimensions(getViewportWidth(),getViewportHeight());
    for(int i=0; i<wordLength; i++) {
        gui->addWidget(letters.at(i));
    }
    if(attempts ==0 ||numberOfLettersRightPlayed == wordLength) finish();
}

HangmanMinigame::HangmanInstance::HangmanInstance(GameContext * context) : _context(context) {

    centralServer = CentralServerHangman();
    for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
        keys[i] = false;
    }
    getWord();
    attempts = 7;
    wordLength= word.length();
    numberOfLettersRightPlayed =0;
    xWrong = 43;
    right = false;
    wrong = false;
    gui = new Gui();
    quad = gluNewQuadric();
    textureId1 = _context->loadTexture("hangman_floor_texture.jpeg");
    gui->addWidget(new LetterWidget("CATEGORY: " + category, 0, 0));

}

void HangmanMinigame::HangmanInstance::getWord()
{
    string s =   centralServer.getWordAndCategory();
    unsigned pos = s.find(",");
    category = s.substr(2,pos-2);
    word= s.substr(pos+1,((s.length()-2) - pos));
}

void HangmanMinigame::HangmanInstance::finish() {
    _context->notifyMinigameFinished(this);
}

void HangmanMinigame::HangmanInstance::onKeyDown(int key, int special) {
    switch (key) {
    case 'a':
        if(keys[0]==false) {
            keys[0] = true;
            determinateLetter("a", word);
        }
        break;
    case 'b':
        if(keys[1]==false) {
            keys[1] = true;
            determinateLetter("b", word);
        }
        break;
    case 'c':
        if(keys[3]==false) {
            keys[3] = true;
            determinateLetter("c", word);
        }
        break;
    case 'd':
        if(keys[4]==false) {
            keys[4] = true;
            determinateLetter("d", word);
        }
        break;
    case 'e':
        if(keys[5]==false) {
            keys[5] = true;
            determinateLetter("e", word);
        }
        break;
    case 'f':
        if(keys[6]==false) {
            keys[6] = true;
            determinateLetter("f", word);
        }
        break;
    case 'g':
        if(keys[7]==false) {
            keys[7] = true;
            determinateLetter("g", word);
        }
        break;
    case 'h':
        if(keys[8]==false) {
            keys[8] = true;
            determinateLetter("h", word);
        }
        break;
    case 'i':
        if(keys[9]==false) {
            keys[9] = true;
            determinateLetter("i", word);
        }
        break;
    case 'j':
        if(keys[10]==false) {
            keys[10] = true;
            determinateLetter("j", word);
        }
        break;
    case 'k':
        if(keys[11]==false) {
            keys[11] = true;
            determinateLetter("k", word);
        }
        break;
    case 'l':
        if(keys[12]==false) {
            keys[12] = true;
            determinateLetter("l", word);
        }
        break;
    case 'm':
        if(keys[13]==false) {
            keys[13] = true;
            determinateLetter("m", word);
        }
        break;
    case 'n':
        if(keys[14]==false) {
            keys[14] = true;
            determinateLetter("n", word);
        }
        break;
    case 'o':
        if(keys[15]==false) {
            keys[15] = true;
            determinateLetter("o", word);
        }
        break;
    case 'p':
        if(keys[16]==false) {
            keys[16] = true;
            determinateLetter("p", word);
        }
        break;
    case 'q':
        if(keys[17]==false) {
            keys[17] = true;
            determinateLetter("q", word);
        }
        break;
    case 'r':
        if(keys[18]==false) {
            keys[18] = true;
            determinateLetter("r", word);
        }
        break;
    case 's':
        if(keys[19]==false) {
            keys[19] = true;
            determinateLetter("s", word);
        }
        break;
    case 't':
        if(keys[20]==false) {
            keys[20] = true;
            determinateLetter("t", word);
        }
        break;
    case 'u':
        if(keys[21]==false) {
            keys[21] = true;
            determinateLetter("u", word);
        }
        break;
    case 'v':
        if(keys[22]==false) {
            keys[22] = true;
            determinateLetter("v", word);
        }
        break;
    case 'x':
        if(keys[23]==false) {
            keys[23] = true;
            determinateLetter("x", word);
        }
        break;
    case 'w':
        if(keys[24]==false) {
            keys[24] = true;
            determinateLetter("w", word);
        }
        break;
    case 'y':
        if(keys[25]==false) {
            keys[25] = true;
            determinateLetter("y", word);
        }
        break;
    case 'z':
        if(keys[26]==false) {
            keys[26] = true;
            determinateLetter("z", word);
        }
        break;

    }
}

void HangmanMinigame::HangmanInstance::onKeyUp(int key, int special) {

}

void HangmanMinigame::HangmanInstance::onMouseButton(int state, int button, int x, int y) {
}

void HangmanMinigame::HangmanInstance::onMouseMove(int x, int y) {
    mx = (GLfloat)x / getViewportWidth() * -40 + 20;
    my = (GLfloat)y / getViewportHeight() * -40 + 20;
}

HangmanMinigame::HangmanInstance::~HangmanInstance() {

}
void HangmanMinigame::HangmanInstance::drawLetters()
{
    int x = 43;
    if(right) {
        x = 43;
        for(int i=0; i<wordLength; i++) {
            cout << "word["<<i<<"] = "<< word[i]<<"; letterRigthPlayed= "<<letterRigthPlayed<<"\n";
            if(word[i] == letterRigthPlayed) {
                string letter;
                cout<<"i = "<<i<<"\n";
                letter = word.substr(i,1);
                cout<<letter<<"\n";
                numberOfLettersRightPlayed++;
                letters.at(i)->setText(letter);
            }
            x+=22;
        }
        right =false;
    }
    if(wrong) {

        string letter = letterWrongPlayed;
        gui->addWidget(new LetterWidget(letter, xWrong, 200));

        xWrong+=22;
        wrong =false;
    }
}

void HangmanMinigame::HangmanInstance::determinateLetter(string chosenLetter, string word)
{
    bool answer=centralServer.findLetterInWord((string)chosenLetter, word);
    if(answer)
    {
        attempts--;
        transform(chosenLetter.begin(), chosenLetter.end(), chosenLetter.begin(),(int (*)(int))toupper);
        letterWrongPlayed  =  chosenLetter;
        wrong = true;
        drawLetters();
        wrong = false;

    } else {
        transform(chosenLetter.begin(), chosenLetter.end(), chosenLetter.begin(),(int (*)(int))toupper);
        letterRigthPlayed  =  chosenLetter[0];
        right = true;
        drawLetters();
        right = false;
    }
}

void HangmanMinigame::HangmanInstance::LetterWidget::drawBackground() {
    GLfloat w = getMinimumWidth();
    glBegin(GL_QUADS);
    glVertex2f(0, -6);
    glVertex2f(w, -6);
    glVertex2f(w, -2);
    glVertex2f(0, -2);
    glEnd();
}

HangmanMinigame::HangmanInstance::LetterWidget::LetterWidget(string text, GLfloat xPos, GLfloat yPos): TextWidget(" " + text + " ", xPos, yPos) {
    setFont(GLUT_BITMAP_HELVETICA_18);
}

string HangmanMinigame::getDescription()
{
    return "Challenge your friend with hangman, where you must guess the letters in a word";
}
string HangmanMinigame::getInternalName()
{
    return "crosswebenterprise.hangman";
}
int HangmanMinigame::HangmanInstance::getScore()
{
    switch(attempts) {
    case 7:
        return 1000;
    case 6:
        return 500;
    case 5:
        return 250;
    case 4:
        return 125;
    case 3:
        return 63;
    case 2:
        return 32;
    case 1:
        return 16;
    case 0:
        return 0;
    default:
        return 0;
    }
}
