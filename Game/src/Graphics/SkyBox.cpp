#include "SkyBox.h"

SkyBox::SkyBox() : skyboxTextId1(0), skyboxTextId2(0), skyboxTextId3(0), skyboxTextId4(0), skyboxTextId5(0), skyboxTextId6(0) {

}

SkyBox::~SkyBox() {

}

void SkyBox::setTextureIds(GLuint Skybox1, GLuint Skybox2, GLuint Skybox3, GLuint Skybox4, GLuint Skybox5, GLuint Skybox6) {
	this->skyboxTextId1 = Skybox1;
	this->skyboxTextId2 = Skybox2;
	this->skyboxTextId3 = Skybox3;
	this->skyboxTextId4 = Skybox4;
	this->skyboxTextId5 = Skybox5;
	this->skyboxTextId6 = Skybox6;
}

void SkyBox::drawSides(GLuint skyboxTextId, GLfloat side1, GLfloat side2, GLfloat side3, GLfloat side4, GLfloat side5, GLfloat side6, GLfloat side7, GLfloat side8, GLfloat side9, GLfloat side10, GLfloat side11, GLfloat side12) {
	glBindTexture(GL_TEXTURE_2D, skyboxTextId);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(side1, side2, side3);
	glTexCoord2f(0, 1);
	glVertex3f(side4, side5, side6);
	glTexCoord2f(0, 0);
	glVertex3f(side7, side8, side9);
	glTexCoord2f(1, 0);
	glVertex3f(side10, side11, side12);
	glEnd();
}

void SkyBox::drawGround(GLuint skyboxTextId, GLfloat side1, GLfloat side2, GLfloat side3, GLfloat side4, GLfloat side5, GLfloat side6, GLfloat side7, GLfloat side8, GLfloat side9, GLfloat side10, GLfloat side11, GLfloat side12) {
	glBindTexture(GL_TEXTURE_2D, skyboxTextId);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(side1, side2, side3);
	glTexCoord2f(1, 0);
	glVertex3f(side4, side5, side6);
	glTexCoord2f(1, 1);
	glVertex3f(side7, side8, side9);
	glTexCoord2f(0, 1);
	glVertex3f(side10, side11, side12);
	glEnd();
}

void SkyBox::draw() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 1.0f, 1.0f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	drawSides(skyboxTextId1, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f);
	drawSides(skyboxTextId2, 0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,  0.5f,  0.5f);
	drawSides(skyboxTextId3, -0.5f, -0.5f,  0.5f , 0.5f, -0.5f,  0.5f, 0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f);
	drawSides(skyboxTextId4, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f , -0.5f,  0.5f, -0.5f);
	drawSides(skyboxTextId5, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, 0.5f,  0.5f,  0.5f , 0.5f,  0.5f, -0.5f);
	drawGround(skyboxTextId6, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}
