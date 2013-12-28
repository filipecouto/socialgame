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
#include "GUI/LinearContainer.h"

#include "GameController.h"
#include "Mods/TestMod/TestMod.h"
#include "Bridge.h"

#pragma comment (lib, "glaux.lib")
#pragma comment (lib, "True_GUI.lib")

//
Gui gui;
GameController controller;
Bridge bridge(&gui, &controller);

//
GLint windowWidth, windowHeight;
long lastTime;

void setCamera();

void onDraw() {
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	setCamera();
	
	controller.draw();

	gui.drawGui();

	glutSwapBuffers();
}

void onVisibilityChange(int state) {
	if (state == GLUT_VISIBLE) {
		
	} else {
		
	}
}

void onSpecialKeyDown(int key, int x, int y) {
	if(gui.onKeyDown(key)) return; // if the GUI consumed the event it should mean it was not meant for the GameController
	controller.onKeyDown(0, key);
}

void onKeyDown(unsigned char c, int x, int y) {
	if(gui.onKeyDown(c)) return; // if the GUI consumed the event it should mean it was not meant for the GameController
	controller.onKeyDown(c, 0);
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
	
	int curr = glutGet ( GLUT_ELAPSED_TIME );
    int deltaT = curr - lastTime;
	
	controller.tick(deltaT, curr);
	gui.tick(deltaT, curr);
	
	lastTime = curr;
	
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
	
	GLfloat light_pos[4] =	{-5.0, 20.0, -8.0, 0.0};
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[]=	{ 0.5f, 0.5f, 0.5f, 1.0f };

    // ligar iluminação
    glEnable ( GL_LIGHTING );

    // ligar e definir fonte de luz 0
    glEnable ( GL_LIGHT0 );
    glLightfv ( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv ( GL_LIGHT0, GL_SPECULAR, light_specular );
    glLightfv ( GL_LIGHT0, GL_POSITION, light_pos );
}

void setCamera() {
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective ( 37, ( GLfloat ) 16.f/9.f , 0.1, 100 );
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
	bridge.onMouseButton(button, state, x, windowHeight - y);
}

void onReshape(int width, int height) {
	gui.setDimensions(width, height);
	
	windowWidth = width;
	windowHeight = height;
	
	glViewport ( 0, 0, windowWidth, windowHeight );

	Widget * bar = bridge.getTopBar();
	bar->x = width - bar->getMinimumWidth();
	bar->y = height - bar->getMinimumHeight();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitWindowSize ( 800, 500 );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	if ( glutCreateWindow ( "Social Game" ) == GL_FALSE )
		exit ( 1 );	// TODO feedback needed

	load();

	//gui.addWidget(new ButtonWidget(new TextWidget("ola", 0, 0), 0, 0));
	gui.addWidget(new TextBoxWidget("texto", 0, 25));
	//gui.addWidget(new ButtonWidget(new TextWidget("xau", 0, 0), 40, 0));

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

// 	gui.addWidget(new TextWidget(
// 		"Segundo o modo que estou actualmente a usar, este utilizador chama-se " + controller.getIdentityPerson()->getName() +
// 		" e esta " + controller.getIdentityPerson()->getMood().getDescription() +
// 		" e tem " + std::to_string(controller.getIdentityPerson()->getConnections().size()) + " amigos.", 0, 50));

	gui.addWidget(bridge.getTopBar());
	
	glutMainLoop();

	return 0;
}