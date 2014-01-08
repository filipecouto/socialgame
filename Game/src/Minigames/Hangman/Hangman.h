#ifndef HANGMAN_H
#define HANGMAN_H

#include "../IMinigame.h"
#include "../IMinigameInstance.h"
#include "../../Graphics/Camera.h"
#include<math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
#include <GL/glut.h>

class HangmanMinigame : public IMinigame {
public:
    HangmanMinigame(GameContext * context);

    virtual std::string getName();

    virtual IMinigameInstance * newGame();

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
	virtual void drawCircle(double distance, double pX, double pZ);
	virtual void drawLines (GLfloat width,GLfloat beginX, GLfloat beginY, GLfloat beginZ,GLfloat endX, GLfloat endY, GLfloat endZ);
	virtual void drawGround(GLfloat v1x, GLfloat v1y, GLfloat v1z,GLfloat v2x, GLfloat v2y, GLfloat v2z,GLfloat v3x, GLfloat v3y, GLfloat v3z,GLfloat v4x, GLfloat v4y, GLfloat v4z);

    private:
        GameContext * _context;

        Camera camera;

        typedef struct Thing {
            GLfloat x, y;
            GLfloat vx, vy;
        } Thing;

        bool keys[4];

        Thing thing;
        GLfloat mx, my;
    };
};

#endif //HANGMAN_H