#include "Gui.h"

Gui::Gui ( ) {
}

Gui::~Gui ( ) { }

void Gui::drawGui ( ) {
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D ( 0, _width, 0, _height );
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity();
	//glScalef(200.0f/_width, 200.0f/_height, 0);
	//GLdouble w = _width/8, h = _height/8;
	//glScalef(1./w, 1./h, 0);

	glEnable ( GL_BLEND );
	glBlendFunc ( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
	glDisable ( GL_LIGHTING );
	glDisable ( GL_DEPTH_TEST );
	glDisable ( GL_COLOR_MATERIAL );

	WidgetContainer::draw();

	glDisable ( GL_BLEND );
	glEnable ( GL_LIGHTING );
	glEnable ( GL_COLOR_MATERIAL );
	glEnable ( GL_DEPTH_TEST );
}

void Gui::onMouseEnter ( int x, int y ) {
	Widget::onMouseEnter ( x, _height - y );
}

void Gui::onMouseMove ( int x, int y ) {
	WidgetContainer::onMouseMove ( x, _height - y );
}

GLboolean Gui::onMouseButtonDown ( int button, int x, int y ) {
	return WidgetContainer::onMouseButtonDown ( button, x, _height - y );
}

GLboolean Gui::onMouseButtonUp ( int button, int x, int y ) {
	return WidgetContainer::onMouseButtonUp ( button, x, _height - y );
}

void Gui::requestFocus ( Widget* from ) {
	if ( _focused != NULL ) _focused->onBlur();
	_focused = from;
	_focused->onFocus();
}

void Gui::setDimensions ( int width, int height ) {
	_width = width;
	_height = height;
}
