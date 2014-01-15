#ifndef EXPORTSCREEN_H
#define EXPORTSCREEN_H

#if _WIN32
#define GL_GLEXT_PROTOTYPES
#include <GL\glew.h>
#include <GL\glext.h>
#endif

#include <GL/freeglut.h>

#include <setjmp.h>

#include <string>
#include <string.h>


using namespace std;

class ExportScreen {
	public:
		ExportScreen();

		bool takePrint(string filename, string filetype, int width, int height);

	private:
		void compressInJPG(FILE * filePtr, int width, int height, char * dataBuffer);
		void compressInTGA(FILE * filePtr, int width, int height, char * dataBuffer);

};
#endif
