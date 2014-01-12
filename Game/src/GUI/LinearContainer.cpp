#include "LinearContainer.h"

LinearContainer::LinearContainer() {

}

LinearContainer::~LinearContainer() {

}

void LinearContainer::addWidget(Widget * newWidget) {
	WidgetContainer::addWidget(newWidget);
	revalidate();
}

void LinearContainer::removeWidget(Widget * oldWidget) {
	WidgetContainer::removeWidget(oldWidget);
	revalidate();
}

void LinearContainer::onParentGeometryChange(Widget * widget) {
	revalidate();
	WidgetContainer::onParentGeometryChange(widget);
}

void LinearContainer::revalidate() {
	GLfloat newX = 0;
	GLfloat newY = 0;

	int len = m_widgetVector.size();

	if (orientation) {
		for (int i = len - 1; i >= 0; i--) {
			Widget * widget = m_widgetVector.at(i);
			widget->x = newX;
			widget->y = newY;

			newY += i == 0 ? widget->h : widget->h + _spacing;
		}
	} else {
		for (int i = 0; i < len; i ++) {
			Widget * widget = m_widgetVector.at(i);
			widget->x = newX;
			widget->y = newY;

			newX += i + 1 == len ? widget->w : widget->w + _spacing;
		}
	}

	if (orientation) {
		w = getBiggestMinimumWidth();
		h = newY;
	} else {
		w = newX;
		h = getBiggestMinimumHeight();
	}
}

void LinearContainer::setHorizontal() {
	orientation = false;
}

void LinearContainer::setVertical() {
	orientation = true;
}

GLfloat LinearContainer::getSpacing() {
	return _spacing;
}

void LinearContainer::setSpacing(GLfloat spacing) {
	_spacing = spacing;
}
