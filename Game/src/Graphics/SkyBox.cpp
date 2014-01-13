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

void SkyBox::drawSide(GLuint textId,
                      GLfloat v1x, GLfloat v1y, GLfloat v1z,
                      GLfloat v2x, GLfloat v2y, GLfloat v2z,
                      GLfloat v3x, GLfloat v3y, GLfloat v3z,
                      GLfloat v4x, GLfloat v4y, GLfloat v4z) {
	glBindTexture(GL_TEXTURE_2D, textId);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(v1x, v1y, v1z);
	glTexCoord2f(0, 0);
	glVertex3f(v2x, v2y, v2z);
	glTexCoord2f(0, 1);
	glVertex3f(v3x, v3y, v3z);
	glTexCoord2f(1, 1);
	glVertex3f(v4x, v4y, v4z);
	glEnd();
}

void SkyBox::draw() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glColor3f(1.0f, 1.0f, 1.0f);

	drawSide(skyboxTextId1,
	         +0.5f, +0.5f, -0.5f,
	         -0.5f, +0.5f, -0.5f,
	         -0.5f, -0.5f, -0.5f,
	         +0.5f, -0.5f, -0.5f);
	drawSide(skyboxTextId2,
	         +0.5f, +0.5f, +0.5f,
	         +0.5f, +0.5f, -0.5f,
	         +0.5f, -0.5f, -0.5f,
	         +0.5f, -0.5f, +0.5f);
	drawSide(skyboxTextId3,
	         -0.5f, +0.5f, +0.5f,
	         +0.5f, +0.5f, +0.5f,
	         +0.5f, -0.5f, +0.5f,
	         -0.5f, -0.5f, +0.5f);
	drawSide(skyboxTextId4,
	         -0.5f, +0.5f, -0.5f,
	         -0.5f, +0.5f, +0.5f,
	         -0.5f, -0.5f, +0.5f,
	         -0.5f, -0.5f, -0.5f);
	drawSide(skyboxTextId5,
	         -0.5f, +0.5f, -0.5f,
	         +0.5f, +0.5f, -0.5f,
	         +0.5f, +0.5f, +0.5f,
	         -0.5f, +0.5f, +0.5f);
	drawSide(skyboxTextId6,
	         -0.5f, -0.5f, +0.5f,
	         +0.5f, -0.5f, +0.5f,
	         +0.5f, -0.5f, -0.5f,
	         -0.5f, -0.5f, -0.5f);
	
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
}
