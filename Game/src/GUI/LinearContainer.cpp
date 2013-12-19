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
	IWidgetContainer::onParentGeometryChange(widget);
	revalidate();
}

void LinearContainer::revalidate() {
	GLfloat newX = 0;
	GLfloat newY = 0;

	for (int i = 0; i < m_widgetVector.size(); i++) {
		Widget * widget = m_widgetVector.at(i);
		widget->x = newX;
		widget->y = newY;

		if (orientation) {
			newY += widget->h + spacing;
		} else {
			newX += widget->w + spacing;
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

GLfloat LinearContainer::getBiggestMinimumWidth() {
	int len = m_widgetVector.size();

	if (len == 0) return 0;

	GLfloat biggest = m_widgetVector[0]->getMinimumWidth();

	for (int i = 0; i < len; i++) {
		if (m_widgetVector[i]->getMinimumWidth() > biggest) biggest = m_widgetVector[i]->getMinimumWidth();
	}

	return biggest;
}

GLfloat LinearContainer::getBiggestMinimumHeight() {
	int len = m_widgetVector.size();

	if (len == 0) return 0;

	GLfloat biggest = m_widgetVector[0]->getMinimumHeight();

	for (int i = 0; i < len; i++) {
		if (m_widgetVector[i]->getMinimumHeight() > biggest) biggest = m_widgetVector[i]->getMinimumHeight();
	}

	return biggest;
}
