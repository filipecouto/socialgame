#ifndef HANGMAN_H
#define HANGMAN_H

#include "../IMinigame.h"
#include "../IMinigameInstance.h"
#include "../../Graphics/Camera.h"
#include "../../GUI/Gui.h"
#include "CentralServerHangman.h"
#include<math.h>
#include <GL/glut.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif


class HangmanMinigame : public IMinigame {
public:
    HangmanMinigame(GameContext * context);

    virtual std::string getName();

    virtual IMinigameInstance * newGame();
    virtual string getDescription();
    virtual string getInternalName();

private:
    GameContext * _context;

    class HangmanInstance : public IMinigameInstance {
    public:

        HangmanInstance(GameContext * context);

        virtual void start();

        virtual void draw();
        virtual void tick(int delta, int current);

        virtual void onKeyDown(int key, int special);
        virtual void onKeyUp(int key, int special);

        virtual void onMouseButton(int state, int button, int x, int y);
        virtual void onMouseMove(int x, int y);

        virtual void finish();

        virtual ~HangmanInstance();
        virtual int getScore();

        virtual void drawCircle(double distance, double pX, double pZ);
        virtual void drawLines(GLfloat width, GLfloat beginX, GLfloat beginY, GLfloat beginZ, GLfloat endX, GLfloat endY, GLfloat endZ);
        virtual void drawSquare(GLfloat v1x, GLfloat v1y, GLfloat v1z, GLfloat v2x, GLfloat v2y, GLfloat v2z, GLfloat v3x, GLfloat v3y, GLfloat v3z, GLfloat v4x, GLfloat v4y, GLfloat v4z);
        virtual void drawLetterSpaces(int length);
        virtual void determinateLetter(string chosenLetter, string word);
        virtual void drawHangman();
        virtual void drawLetters();
        void getWord();

    private:
        int attempts;
        int xWrong;
        string word;
        string category;
        char  letterRigthPlayed;
        string  letterWrongPlayed;
        int wordLength;
        bool right;
        bool wrong;
        int numberOfLettersRightPlayed;

        CentralServerHangman centralServer;
        GameContext * _context;
        Gui * gui;

        Camera camera;

        typedef struct Thing {
            GLfloat x, y;
            GLfloat vx, vy;
        } Thing;

        bool keys[26];

        Thing thing;
        GLfloat mx, my;

        class LetterWidget : public TextWidget {
        public:
            LetterWidget(string text, GLfloat xPos, GLfloat yPos);

            virtual void drawBackground();
        };
        vector<LetterWidget*> letters;
    };
};

#endif //HANGMAN_H
