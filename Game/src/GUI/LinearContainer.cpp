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
