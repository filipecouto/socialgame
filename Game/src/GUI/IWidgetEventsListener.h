#ifndef IWIDGETEVENTSLISTENER_H
#define IWIDGETEVENTSLISTENER_H

#include "Widget.h"

class IWidgetEventsListener {
	public:
		virtual bool onWidgetClicked(Widget * widget) = 0;
};

#endif