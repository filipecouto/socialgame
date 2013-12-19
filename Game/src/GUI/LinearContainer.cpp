#include "LinearContainer.h"

LinearContainer::LinearContainer() {

}

LinearContainer::~LinearContainer() {

}

void LinearContainer::addWidget(Widget * newWidget) {
	WidgetContainer::addWidget(newWidget);
}

void LinearContainer::removeWidget(Widget * oldWidget) {
	WidgetContainer::removeWidget(oldWidget);
}

LinearContainer::~WidgetContainer() {

}

void LinearContainer::onParentGeometryChange(Widget * widget) {
	IWidgetContainer::onParentGeometryChange(widget);
}

void LinearContainer::revalidate() {
	GLfloat newX = 0; GLfloat newY = 0;
	for(int i = 0; i < m_widgetVector.size(); i++) {
		Widget widget = (Widget) m_widgetVector.at(i);
		widget.x = newX;
		widget.y = newY;
		if(orientation) {
			newY+= widget.h + spacing;
		} else {
			newX+= widget.w + spacing;
		}
	}
	
}

