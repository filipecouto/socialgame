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

    glColor3f(0, 0.25, 0);
    drawSquare(-400,-81,400,400,-81,400,200,-81,-200,-200, -81,-200);
    glPushMatrix();
    glColor3f(0.46, 0.32, 0.1);
    drawLines(20.0,10.0, -80.0, 20.0,50.0, -80.0,20.0);
    drawLines(10.0,30.0, -80.0, 20.0,30.0, -80.0,-40.0);
    drawLines(10.0,30.0, -80.0,-40.0,70.0, -80.0,-40.0);
    drawLines(10.0,69.0, -80.0,-40.0,69.0, -80.0,-30.0);

    drawHangman();

    glColor3f(0,0,1);
    drawLetterSpaces(word.length());
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

void HangmanMinigame::HangmanInstance::drawHangman()
{
    glColor3f(1, 1, 1);
    switch(attempts) {
    case 5:
        drawCircle(8.0, 69.0,-25.0);
        break;
    case 4:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        break;
    case 3:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        break;
    case 2:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 79.0, -80.0,-15.0 );
        break;
    case 1:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 79.0, -80.0,-15.0 );
        drawLines(5.0,  69.0, -80.0,5.0, 59.0, -80.0, 15.0 );
        break;
    case 0:
        drawCircle(8.0, 69.0,-25.0);
        drawLines(5.0, 69.0, -80.0,-30.0, 69.0, -80.0,5.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 59.0, -80.0,-15.0 );
        drawLines(5.0, 69.0, -80.0,-10.0, 79.0, -80.0,-15.0 );
        drawLines(5.0,  69.0, -80.0,5.0, 59.0, -80.0, 15.0 );
        drawLines(5.0,  69.0, -80.0,5.0, 79.0, -80.0, 15.0 );
        break;
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
    gui->tick(delta,current);
    gui->setDimensions(getViewportWidth(),getViewportHeight());
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

    centralServer = CentralServerHangman();
    for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
        keys[i] = false;
    }
    getWord();
    attempts = 6;
    wordLength= word.length();

    gui = new Gui();
    gui->addWidget(new TextWidget(category, 80, 450));

}

void HangmanMinigame::HangmanInstance::getWord()
{
    string s =   centralServer.getWordAndCategory();
    unsigned pos = s.find(",");
    category = s.substr(2,pos-2);
    word= s.substr(pos+1,((s.length()-2) - pos));
}

void HangmanMinigame::HangmanInstance::finish() {
    //  _context->notifyMinigameFinished(this);
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
            cout << "word["<<i<<"] = "<< word[i]<<"; letterPlayed= "<<letterPlayed<<"\n";
            if(word[i] == letterPlayed) {
                string letter;
                cout<<"i = "<<i<<"\n";
                letter = word.substr(i,1);
                cout<<letter<<"\n";
                gui->addWidget(new TextWidget(letter, x, 380));
            }
            x+=22;
        }

    }
}

void HangmanMinigame::HangmanInstance::determinateLetter(string chosenLetter, string word)
{
    bool answer=centralServer.findLetterInWord((string)chosenLetter, word);
    if(answer)
    {
        attempts--;
        transform(chosenLetter.begin(), chosenLetter.end(), chosenLetter.begin(),(int (*)(int))toupper);

    } else {
        transform(chosenLetter.begin(), chosenLetter.end(), chosenLetter.begin(),(int (*)(int))toupper);
        letterPlayed  =  chosenLetter[0];
        drawLetters();
    }
}

