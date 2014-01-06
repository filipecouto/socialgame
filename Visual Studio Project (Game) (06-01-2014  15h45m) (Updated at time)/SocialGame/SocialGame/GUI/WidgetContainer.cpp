#include "WidgetContainer.h"

WidgetContainer::WidgetContainer() {
}

WidgetContainer::~WidgetContainer() { }

void WidgetContainer::draw() {
	Widget::draw();

	int size = m_widgetVector.size();

	for (int i = 0; i < size; ++i) {
		Widget * w = m_widgetVector[i];

		if (w->visible) {
			glPushMatrix();
			glTranslatef(w->x, w->y, 0);
// 		glColor4f(1, 1, 1, 0.4f);
// 		glBegin(GL_QUADS);
// 		glVertex2f(0, 0);
// 		glVertex2f(w->w, 0);
// 		glVertex2f(w->w, w->h);
// 		glVertex2f(0, w->h);
// 		glEnd();
			w->draw();
			glPopMatrix();
		}
	}
}

Widget * WidgetContainer::getWidget(int x, int y) {
	for (int i = m_widgetVector.size() - 1; i >= 0; i--) {
		Widget * w = m_widgetVector[i];

		if (w->visible &&
		    x >= w->x && x < w->x + w->w &&
		    y >= w->y && y < w->y + w->h) {
			return w;
		}
	}

	return NULL;
}

void WidgetContainer::onWidgetClicked(Widget * clicked) {
	if (_parent != NULL) _parent->onWidgetClicked(clicked);
}

void WidgetContainer::onMouseMove(int x, int y) {
	Widget * w = getWidget(x, y);

	if (w != NULL) {
		if (w == _widgetHover) {
			w->onMouseMove(x - w->x, y - w->y);
			return;
		} else {
			if (_widgetHover != NULL) _widgetHover->onMouseExit();

			w->onMouseEnter(x - w->x, y - w->y);
			_widgetHover = w;
			return;
		}
	}

	if (_widgetHover != NULL) {
		_widgetHover->onMouseExit();
		_widgetHover = NULL;
	}

	//printf("<- %x->onMouseMove(%d, %d)\n", this, x, y);
}

GLboolean WidgetContainer::onMouseButtonDown(int button, int x, int y) {
	Widget * w = getWidget(x, y);

	if (w != NULL) {
		return w->onMouseButtonDown(button, x - w->x, y - w->y);
	}

	return false;
}

GLboolean WidgetContainer::onMouseButtonUp(int button, int x, int y) {
	Widget * w = getWidget(x, y);

	if (w != NULL) {
		return w->onMouseButtonUp(button, x - w->x, y - w->y);
	}

	return false;
}

void WidgetContainer::requestFocus(Widget * from) {
	if (_focused != NULL) _focused->onBlur();

	_focused = from;
	Widget::requestFocus();
}

void WidgetContainer::onBlur() {
	if (_focused != NULL) _focused->onBlur();
}

void WidgetContainer::onFocus() {
	if (_focused != NULL) _focused->onFocus();
}

GLboolean WidgetContainer::onKeyDown(int key) {
	if (_focused == NULL) return false;

	return _focused->onKeyDown(key);
}

GLboolean WidgetContainer::onKeyUp(int key) {
	if (_focused == NULL) return false;

	return _focused->onKeyUp(key);
}

void WidgetContainer::addWidget(Widget * add_object) {
	m_widgetVector.push_back(add_object);
	add_object->setParent(this);

	w = getBiggestMinimumWidth();
	h = getBiggestMinimumHeight();
}

void WidgetContainer::removeWidget(Widget * remove_object) {
	int i, size = m_widgetVector.size();

	for (i = 0; i < size; ++i) {
		Widget * item = m_widgetVector.at(i);

		if (item == remove_object) {
			std::vector<Widget *>::iterator it = m_widgetVector.begin() + i;
			m_widgetVector.erase(it);
			return;
		}
	}

	w = getBiggestMinimumWidth();
	h = getBiggestMinimumHeight();
}

GLfloat WidgetContainer::getBiggestMinimumWidth() {
	int len = m_widgetVector.size();

	if (len == 0) return 0;

	GLfloat biggest = m_widgetVector[0]->getMinimumWidth();

	for (int i = 0; i < len; i++) {
		if (m_widgetVector[i]->getMinimumWidth() > biggest) biggest = m_widgetVector[i]->getMinimumWidth();
	}

	return biggest;
}

GLfloat WidgetContainer::getBiggestMinimumHeight() {
	int len = m_widgetVector.size();

	if (len == 0) return 0;

	GLfloat biggest = m_widgetVector[0]->getMinimumHeight();

	for (int i = 0; i < len; i++) {
		if (m_widgetVector[i]->getMinimumHeight() > biggest) biggest = m_widgetVector[i]->getMinimumHeight();
	}

	return biggest;
}

void WidgetContainer::tick(int delta, int absolute) {
	int len = m_widgetVector.size();

	for (int i = 0; i < len; i++) {
		Widget * w = m_widgetVector[i];

		if (w->visible && w->isAnimating()) m_widgetVector[i]->tick(delta, absolute);
	}
}

GLboolean WidgetContainer::isAnimating() {
	int len = m_widgetVector.size();

	for (int i = 0; i < len; i++) {
		Widget * w = m_widgetVector[i];

		if (w->visible && w->isAnimating()) return true;
	}

	return false;
}

int WidgetContainer::getWidth() {
	return w;
}

int WidgetContainer::getHeigth() {
	return h;
}

void WidgetContainer::onParentGeometryChange(Widget * widget) {
	if (getParent()) getParent()->onParentGeometryChange(widget);
}
