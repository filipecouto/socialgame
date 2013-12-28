#include "TextWidget.h"

TextWidget::TextWidget ( ) :
	TextWidget ( "", 0, 0 ) {}

TextWidget::TextWidget ( std::string text, GLfloat xPos, GLfloat yPos ) :
	TextWidget ( text, 1,1,1,1, GLUT_BITMAP_HELVETICA_12, xPos, yPos ) {}

TextWidget::TextWidget ( std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat xPos, GLfloat yPos ) :
	TextWidget ( text, r, g, b, a, GLUT_BITMAP_HELVETICA_12, xPos, yPos ) {}

TextWidget::TextWidget ( std::string text, void* font, GLfloat xPos, GLfloat yPos ) :
	TextWidget ( text, 1, 1, 1, 1, font, xPos, yPos ) {}

TextWidget::TextWidget ( std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, void* font, GLfloat xPos, GLfloat yPos ) :
	_font ( font ), Widget ( xPos, yPos ) {
	setTextColor(r, g, b, a);
	setText ( text );
}

TextWidget::~TextWidget ( ) { }

void TextWidget::setText ( std::string text ) {
	_text = text;

	updateDimensions();
}
std::string TextWidget::getText() {
	return _text;
}

void* TextWidget::getFont() {
	return _font;
}

void TextWidget::setFont ( void* font ) {
	_font = font;

	updateDimensions();
}

void TextWidget::updateDimensions() {
	_minWidth = glutBitmapLength ( _font, ( const unsigned char* ) _text.c_str() );
	_minHeight = glutBitmapHeight ( _font ) - 7;

	w = _minWidth;
	h = _minHeight;

	notifyGeometryChange();
}

void TextWidget::getTextColor ( float color[] ) {
	color = _textColor;
}
void TextWidget::setTextColor ( GLfloat r, GLfloat g, GLfloat b ) {
	_textColor[0] = r;
	_textColor[1] = g;
	_textColor[2] = b;
}
void TextWidget::setTextColor ( GLfloat r, GLfloat g, GLfloat b, GLfloat a ) {
	setTextColor ( r,g,b );
	_textColor[3] = a;
}

GLfloat TextWidget::getMinimumWidth() {
	return _minWidth;
}

GLfloat TextWidget::getMinimumHeight() {
	return _minHeight;
}

void TextWidget::draw ( ) {
	drawBackground();

	glColor4fv ( _textColor );

	glRasterPos2d ( 0, 0 );
	GLfloat n = _text.length();
	glutBitmapString(_font, (const unsigned char*) _text.c_str());
}
