#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <string>

#include "Widget.h"

class TextWidget : public Widget {
	public:
		TextWidget ( );
		TextWidget ( std::string text, GLfloat xPos, GLfloat yPos );
		TextWidget ( std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, void* font, GLfloat xPos, GLfloat yPos );
		TextWidget ( std::string text, void * font, GLfloat xPos, GLfloat yPos );
		TextWidget ( std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat xPos, GLfloat yPos );

		virtual ~TextWidget ( );

		void setText ( std::string text );
		std::string getText();

		void setFont ( void * font );
		void * getFont();

		void setTextColor ( GLfloat r, GLfloat g, GLfloat b );
		void setTextColor ( GLfloat r, GLfloat g, GLfloat b, GLfloat a );
		void getTextColor ( float color[] );

		virtual GLfloat getMinimumWidth();
		virtual GLfloat getMinimumHeight();

		virtual void draw();

	private:
		std::string _text;
		void * _font;
		float _textColor[4];
		GLfloat _minWidth, _minHeight;
};

#endif // TEXTWIDGET_H
