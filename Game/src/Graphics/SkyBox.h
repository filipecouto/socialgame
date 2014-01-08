#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/freeglut.h>


class SkyBox {
	public:
		SkyBox();

		void setTextureIds(GLuint Skybox1, GLuint Skybox2, GLuint Skybox3, GLuint Skybox4, GLuint Skybox5, GLuint Skybox6);
		void draw();

		~SkyBox();
	private:
		GLuint skyboxTextId1;
		GLuint skyboxTextId2;
		GLuint skyboxTextId3;
		GLuint skyboxTextId4;
		GLuint skyboxTextId5;
		GLuint skyboxTextId6;

		void drawSide(GLuint textId, GLfloat v1x, GLfloat v1y, GLfloat v1z, GLfloat v2x, GLfloat v2y, GLfloat v2z, GLfloat side7, GLfloat side8, GLfloat side9, GLfloat side10, GLfloat side11, GLfloat side12);
		void drawSides(GLuint skyboxTextId, GLfloat side1, GLfloat side2, GLfloat side3, GLfloat side4, GLfloat side5, GLfloat side6, GLfloat side7, GLfloat side8, GLfloat side9, GLfloat side10, GLfloat side11, GLfloat side12);
		void drawGround(GLuint skyboxTextId, GLfloat side1, GLfloat side2, GLfloat side3, GLfloat side4, GLfloat side5, GLfloat side6, GLfloat side7, GLfloat side8, GLfloat side9, GLfloat side10, GLfloat side11, GLfloat side12);
};

#endif //SKYBOX_H
