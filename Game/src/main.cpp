/**
 * Social Game - Application Starting Point
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <vector>
#endif

#ifdef _WIN32
#include <GL/glaux.h>
#endif

#include "GUI/Gui.h"
#include "GUI/TextBoxWidget.h"
#include "GUI/ButtonWidget.h"

#include "GameController.h"
#include "Mods/TestMod/TestMod.h"

Gui gui;
GameController controller;

GLint windowWidth, windowHeight;

void setCamera();

void onDraw() {
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	gui.drawGui();
	setCamera();

	glutSwapBuffers();
}

void onVisibilityChange(int state) {
	if (state == GLUT_VISIBLE) {
		
	} else {
		
	}
}

void onSpecialKeyDown(int key, int x, int y) {
	if(gui.onKeyDown(key)) return; // if the GUI consumed the event it should mean it was not meant for the GameController
}

void onKeyDown(unsigned char c, int x, int y) {
	if(gui.onKeyDown(c)) return; // if the GUI consumed the event it should mean it was not meant for the GameController
	switch (c) {
		case 27:		// ESC
			exit(0);
			break;
	}
}

void onKeyUp(unsigned char c, int x, int y) {
	if(gui.onKeyUp(c)) return; // if the GUI consumed the event it should mean it was not meant for the GameController
}

void onSpecialKeyUp(int key, int x, int y) {
	if(gui.onKeyUp(key)) return; // if the GUI consumed the event it should mean it was not meant for the GameController
}

void timer(int value) {
	glutTimerFunc ( 20, timer, 0 );
	
	glutPostRedisplay();
}

void load() {
	glEnable ( GL_DEPTH_TEST );
	glShadeModel ( GL_SMOOTH );
	glEnable ( GL_POINT_SMOOTH );
	glEnable ( GL_LINE_SMOOTH );
	glEnable ( GL_POLYGON_SMOOTH );
	glEnable ( GL_TEXTURE_2D );
	// evitar glEnable ( GL_NORMALIZE );

	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	// TODO climate changes due to mood should handle this instead:
	GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightModelfv ( GL_LIGHT_MODEL_AMBIENT, amb );
}

void setCamera() {
	glViewport ( 0, 0, windowWidth, windowHeight );
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective ( 37, ( GLfloat ) 19.f/9.f , 0.1, 100 );
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onMouseMove(int x, int y) {
	gui.onMouseMove(x, y);
}

void onMouseButton( int button, int state, int x, int y ) {
	if ( state == 0 ) {
		if ( gui.onMouseButtonDown ( button, x, y ) ) return;
	} else if ( state == 1 ) {
		if ( gui.onMouseButtonUp ( button, x, y ) ) return;
	}
}

void onReshape(int width, int height) {
	gui.setDimensions(width, height);
	
	windowWidth = width;
	windowHeight = height;
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitWindowSize ( 800, 500 );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	if ( glutCreateWindow ( "Social Game" ) == GL_FALSE )
		exit ( 1 );	// TODO feedback needed

	load();

	gui.addWidget(new ButtonWidget(new TextWidget("ola", 0, 0), 0, 0));
	gui.addWidget(new TextBoxWidget("texto", 0, 25));
	gui.addWidget(new ButtonWidget(new TextWidget("xau", 0, 0), 40, 0));

	glutReshapeFunc ( onReshape );
	glutVisibilityFunc( onVisibilityChange );
	glutDisplayFunc ( onDraw );

	glutKeyboardFunc ( onKeyDown );
	glutSpecialFunc ( onSpecialKeyDown );
	glutSpecialUpFunc ( onSpecialKeyUp );
	glutKeyboardUpFunc( onKeyUp );

	glutMouseFunc ( onMouseButton );
	glutPassiveMotionFunc( onMouseMove );
	glutMotionFunc ( onMouseMove );

	glutTimerFunc ( 20, timer, 0 );

	setCamera();
	
	controller.start(new TestMod());

	gui.addWidget(new TextWidget(
		"Segundo o modo que estou actualmente a usar, este utilizador chama-se " + controller.getIdentityPerson()->getName() +
		" e esta " + controller.getIdentityPerson()->getMood().getDescription() +
		" e tem " + std::to_string(controller.getIdentityPerson()->getConnections().size()) + " amigos.", 0, 50));
	
	glutMainLoop();

	return 0;
}