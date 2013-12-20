#include "Widget.h"

Widget::Widget() : Widget(0, 0) {}

Widget::Widget(GLfloat xPos, GLfloat yPos) : x(xPos), y(yPos), visible(true), hover(false) {}

void Widget::draw() {
	drawBackground();
}

void Widget::drawBackground() {

}

void Widget::requestFocus() {
	if (_parent != NULL) _parent->requestFocus(this);
}

void Widget::notifyGeometryChange() {
	if (_parent != NULL) _parent->onParentGeometryChange(this);
}

void Widget::performClick() {
	if (_parent != NULL) _parent->onWidgetClicked(this);
}

Widget::~Widget() { }
