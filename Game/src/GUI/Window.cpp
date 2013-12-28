#include "Window.h"

Window::Window() {
	setPadding(8);
}

Window::Window(Widget * contents) : _contents(contents) {
	addWidget(contents);
	setPadding(8);
}

void Window::draw() {
	if (_ct != 0)
		glTranslatef(_ct, 0, 0);

	WidgetContainer::draw();

	if (_ct != 0)
		glTranslatef(-_ct, 0, 0);
}

void Window::drawBackground() {
	glColor4f(0.6, 0.6, 0.6, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(w, 0);
	glVertex2f(w, h);
	glVertex2f(0, h);
	glEnd();
}

GLfloat Window::getBiggestMinimumHeight() {
	return WidgetContainer::getBiggestMinimumHeight() + _padding * 2;
}

GLfloat Window::getBiggestMinimumWidth() {
	return WidgetContainer::getBiggestMinimumWidth() + _padding * 2;
}

void Window::setPadding(GLfloat padding) {
	_padding = padding;

	if (_contents) {
		_contents->x += padding;
		_contents->y += padding;
	}

	onParentGeometryChange(NULL);
}

GLboolean Window::onMouseButtonDown(int button, int x, int y) {
	WidgetContainer::onMouseButtonDown(button, x, y);
	return true;
}

GLboolean Window::onMouseButtonUp(int button, int x, int y) {
	WidgetContainer::onMouseButtonUp(button, x, y);
	return true;
}

void Window::setContent(Widget * content) {
	addWidget(content);
	_contents = content;
	setPadding(_padding);
}

GLboolean Window::isAnimating() {
	if (_ct != _tt) return true;

	return WidgetContainer::isAnimating();
}

void Window::tick(int delta, int absolute) {
	WidgetContainer::tick(delta, absolute);

	if (_ct != _tt) {
		_ct += (_tt - _ct) * (float)delta / 80.0f;

		if (abs(_ct - _tt) <= 2) {
			_ct = _tt;

			if (_ct <= -w - x) visible = false;
		}
	}
}

void Window::show() {
	//_ct = -w-x;
	_tt = 0;
	visible = true;
}

void Window::hide() {
	//_ct = 0;
	_tt = -w - x;
	visible = true;
}

void Window::onParentGeometryChange(Widget * widget) {
	if (_contents) {
		w = _contents->w + _padding * 2;
		h = _contents->h + _padding * 2;
	}

	if (getParent()) getParent()->onParentGeometryChange(widget);
}

void Window::avoidOutside() {
	if(x + w > getParent()->getWidth()) x = getParent()->getWidth() - w;
	if(y + h > getParent()->getHeigth()) y = getParent()->getHeigth() - h;
}

Window::~Window() {

}
