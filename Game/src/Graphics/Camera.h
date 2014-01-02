/*
 * Camera - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/freeglut.h>

enum CameraTypes {
	FreeMode, FirstPerson, ThirdPerson
};

class Camera {
	public:
		Camera();
		
		void setUp();
		
		CameraTypes getType();
		void setType(CameraTypes type);
		
		void tick(int delta, int absolute);
		
		void translate(GLfloat x, GLfloat y, GLfloat z);
		void moveTo(GLfloat x, GLfloat y, GLfloat z);
		void lookAt(GLfloat x, GLfloat y, GLfloat z);
		
		GLfloat getY();
		
		~Camera();

	private:
		CameraTypes currentType = ThirdPerson;
		
		// target values
		GLfloat tex, tey, tez,
				tcx, tcy, tcz,
				tux, tuy, tuz;
		
		// current values (which will gradually change to equal the target ones)
		GLfloat cex = 0, cey = 0, cez = 0,
				ccx = 0, ccy = 0, ccz = 0,
				cux = 0, cuy = 1, cuz = 0;
		
		void animate(GLfloat target, GLfloat &value);
};

#endif // CAMERA_H
