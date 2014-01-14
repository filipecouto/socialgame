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
		void rotate(GLfloat xz, GLfloat y);
		void rotate(GLfloat x, GLfloat y, GLfloat z);
		void walk(GLfloat x, GLfloat y, GLfloat z);
		
		/**
		 * Translates current matrix to the position of the camera,
		 * useful to place the skybox
		 */
		void translateToCamera();
		
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
		
		//void animate(GLfloat tx, GLfloat & vx, GLfloat ty, GLfloat & vy, GLfloat tz, GLfloat & vz);
		void animate(GLfloat target, GLfloat & current);
		
		GLfloat getAngle();
};

#endif // CAMERA_H
