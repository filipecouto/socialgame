#ifndef IWIDGETCONTAINER_H
#define IWIDGETCONTAINER_H

class Dialog;
class Widget;

class IWidgetContainer {
	public:
		virtual void requestFocus(Widget * from) { }
		virtual void onParentGeometryChange(Widget * widget) { }
		
		virtual void onWidgetClicked(Widget * clicked) { }
		virtual void onDialogResult(Dialog * dialog, int buttonId) { }
		
		virtual int getWidth() = 0;
		virtual int getHeigth() = 0;
};

#endif
