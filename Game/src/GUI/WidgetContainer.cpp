#include "WidgetContainer.h"

WidgetContainer::WidgetContainer ( ) {
}

WidgetContainer::~WidgetContainer ( ) { }

void WidgetContainer::draw() {
	int size = m_widgetVector.size();
	for ( int i = 0; i < size; ++i ) {
		Widget * w = m_widgetVector[i];
		glPushMatrix();
		glTranslatef ( w->x, w->y, 0 );
		w->draw();
		glPopMatrix();
	}
}

Widget* WidgetContainer::getWidget ( int x, int y ) {
	int size = m_widgetVector.size();
	for ( int i = 0; i < size; ++i ) {
		Widget * w = m_widgetVector[i];
		if (	w->visible &&
		        x >= w->x && x < w->x+w->w &&
		        y >= w->y && y < w->y+w->h ) {
			return w;
		}
	}
	return NULL;
}

void WidgetContainer::onMouseMove ( int x, int y ) {
	Widget * w = getWidget ( x, y );
	if ( w != NULL ) {
		if ( w == _widgetHover ) {
			w->onMouseMove ( x - w->x, y - w->y );
			return;
		} else {
			if ( _widgetHover != NULL ) _widgetHover->onMouseExit();
			w->onMouseEnter ( x - w->x, y - w->y );
			_widgetHover = w;
			return;
		}
	}
	if ( _widgetHover != NULL ) {
		_widgetHover->onMouseExit();
		_widgetHover = NULL;
	}
}

GLboolean WidgetContainer::onMouseButtonDown ( int button, int x, int y ) {
	Widget * w = getWidget ( x, y );
	if ( w != NULL ) {
		w->onMouseButtonDown ( button, x - w->x, y - w->y );
		return true;
	}
	return false;
}

GLboolean WidgetContainer::onMouseButtonUp ( int button, int x, int y ) {
	Widget * w = getWidget ( x, y );
	if ( w != NULL ) {
		w->onMouseButtonUp ( button, x - w->x, y - w->y );
		return true;
	}
	return false;
}

void WidgetContainer::requestFocus ( Widget * from ) {
	if ( _focused != NULL ) _focused->onBlur();
	_focused = from;
	Widget::requestFocus();
}

void WidgetContainer::onBlur() {
	if ( _focused != NULL ) _focused->onBlur();
}

void WidgetContainer::onFocus() {
	if ( _focused != NULL ) _focused->onFocus();
}

GLboolean WidgetContainer::onKeyDown ( int key ) {
	if ( _focused == NULL ) return false;
	return _focused->onKeyDown ( key );
}

GLboolean WidgetContainer::onKeyUp ( int key ) {
	if ( _focused == NULL ) return false;
	return _focused->onKeyUp ( key );
}

void WidgetContainer::addWidget ( Widget * add_object ) {
	m_widgetVector.push_back ( add_object );
	add_object->setParent ( this );
}

void WidgetContainer::removeWidget ( Widget * remove_object ) {
	int i, size = m_widgetVector.size();
	for ( i = 0; i < size; ++i ) {
		Widget * item = m_widgetVector.at ( i );
		if ( item == remove_object ) {
			std::vector<Widget *>::iterator it = m_widgetVector.begin() + i;
			m_widgetVector.erase ( it );
			return;
		}
	}
}
