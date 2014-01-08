#ifndef IWIDGETEVENTSLISTENER_H
#define IWIDGETEVENTSLISTENER_H

#include <string>
#include "Widget.h"

class IWidgetEventsListener {
	public:
		virtual bool onWidgetClicked(Widget * widget) = 0;
		
		virtual bool onDialogResult(Dialog * dialog, int buttonId) = 0;
};

#endif