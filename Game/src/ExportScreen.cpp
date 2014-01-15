#include "ExportScreen.h"


#include <stdio.h>
#if _WIN32
extern "C"{
#include "jpeglib.h"	
}
#else
#include "jpeglib.h"
#endif
#pragma comment (lib, "libjpeg.lib")
ExportScreen::ExportScreen(){

}

bool ExportScreen::takePrint(string filename, string filetype, int width, int height){
	//Pixel storage mode
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	
	//Buffer, 3 channels per Pixel
	char* dataBuffer = (char*)malloc(width*height*3*sizeof(char));
      
	if (!dataBuffer) return false;
      
	//Read a block of pixels from the frame buffer
	glReadPixels((GLint)0, (GLint)0,
		      (GLint)width, (GLint)height,
		      GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);
      	
	//Create the file
	FILE *filePtr = fopen((filename+"."+filetype).c_str(), "wb");
	if (!filePtr) return false;
	
	//File compression
	if(filetype == "jpg"){
		compressInJPG(filePtr, width, height, dataBuffer);
	}
	else if(filetype == "tga"){
		compressInTGA(filePtr, width, height, dataBuffer);
	}
	else{
		fclose(filePtr);
		return false;
	}
	
	fclose(filePtr);
      
	return true;
}

void ExportScreen::compressInJPG(FILE * filePtr, int width, int height, char* dataBuffer)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, filePtr);
	
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	#if _WIN32
	#else
		cinfo.in_color_space = JCS_EXT_BGR;
	#endif
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 100, true);
	jpeg_start_compress(&cinfo, true);
	
	JSAMPROW row_pointer;
	int row_stride = width * 3;
	
	while (cinfo.next_scanline < cinfo.image_height) {
		row_pointer = (JSAMPROW) &dataBuffer[(cinfo.image_height-1-cinfo.next_scanline)*row_stride];
		jpeg_write_scanlines(&cinfo, &row_pointer, 1);
	}
	
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
}

void ExportScreen::compressInTGA(FILE * filePtr, int width, int height, char* dataBuffer)
{
	unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
	unsigned char header[6] = { width%256,width/256,
				    height%256,height/256,
				    24,0};
	fwrite(TGAheader, sizeof(unsigned char), 12, filePtr);
	fwrite(header, sizeof(unsigned char), 6, filePtr);
	fwrite(dataBuffer, sizeof(GLubyte), (width*height*3), filePtr);
}
