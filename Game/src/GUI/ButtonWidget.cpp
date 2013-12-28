#include "ButtonWidget.h"
#include <iostream>
// Constructors/Destructors
//

ButtonWidget::ButtonWidget() {
}

ButtonWidget::ButtonWidget(Widget * containingWidget) : ButtonWidget(containingWidget, 0, 0) {
}

ButtonWidget::ButtonWidget(Widget * containingWidget, GLfloat xPos, GLfloat yPos) : _clicked(false), _hoverAnim(0), _clickAnim(1), _focusAnim(0), _borderWidth(5), Widget(xPos, yPos) {
	setContainingWidget(containingWidget);
}

ButtonWidget::~ButtonWidget() { }

void ButtonWidget::drawBackground() {
	if (hover && _hoverAnim < 1) _hoverAnim += 0.08f;
	else if (!hover && _hoverAnim > 0) _hoverAnim -= 0.04f;

	if (_hoverAnim > 1) _hoverAnim = 1;
	else if (_hoverAnim < 0) _hoverAnim = 0;

	if (_clicked && _clickAnim > 0.9f) _clickAnim -= 0.02f;
	else if (!_clicked && _clickAnim < 1) _clickAnim += 0.1f;

	if (_clickAnim > 1) _clickAnim = 1;
	else if (_clickAnim < 0.9f) _clickAnim = 0.9f;

	if (focused && _focusAnim < 1) _focusAnim += 0.08f;
	else if (!focused && _focusAnim > 0) _focusAnim -= 0.04f;

	if (_focusAnim > 1) _focusAnim = 1;
	else if (_focusAnim < 0) _focusAnim = 0;

	glPushMatrix();
	glTranslatef(w / 2, h / 2, 0);
	glScalef(_clickAnim, _clickAnim, 0);
	glTranslatef(-w / 2, -h / 2, 0);
	glColor4f(0.3, 0.3 + 0.3 * _focusAnim, 0.3 + 0.6 * _focusAnim, 0.4 + 0.6 * _hoverAnim);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(_minW + _borderWidth * 2, 0);
	glVertex2f(0, _minH + _borderWidth * 2);
	glVertex2f(_minW + _borderWidth * 2, _minH + _borderWidth * 2);
	glEnd();
	glPopMatrix();
}

void ButtonWidget::draw() {
	Widget::draw();

	if (_widget != NULL) {
		glTranslatef(_borderWidth, _borderWidth, 0);
		_widget->draw();
		glTranslatef(-_borderWidth, -_borderWidth, 0);
	}
}

GLboolean ButtonWidget::onMouseButtonDown(int button, int x, int y) {
	Widget::onMouseButtonDown(button, x, y);

	if (button == 0) _clicked = true;

	return true;
}

GLboolean ButtonWidget::onMouseButtonUp(int button, int x, int y) {
	if (button == 0) {
		if (_clicked && x >= 0 && x < w && y >= 0 && y < h) performClick();

		_clicked = false;
	}

	return true;
}

void ButtonWidget::onParentGeometryChange(Widget * widget) {
	_minW = _widget->getMinimumWidth();
	_minH = _widget->getMinimumHeight();

	w = _minW + _borderWidth * 2;
	h = _minH + _borderWidth * 2;

	notifyGeometryChange();
}

Widget * ButtonWidget::getContainingWidget() {
	return _widget;
}

void ButtonWidget::setContainingWidget(Widget * widget) {
	_widget = widget;
	_widget->setParent(this);

	onParentGeometryChange(_widget);
}

int ButtonWidget::getWidth() {
	return w;
}

int ButtonWidget::getHeigth() {
	return h;
}
