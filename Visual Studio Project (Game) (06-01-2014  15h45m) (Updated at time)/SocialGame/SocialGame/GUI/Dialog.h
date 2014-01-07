#ifndef DIALOG_H
#define DIALOG_H

#include <string>

#include "Window.h"
#include "ButtonWidget.h"

class Dialog : public Window {
	public:
		Dialog(std::string id, std::string message);

		virtual void centerOnParent();
		
		virtual void show();

		virtual void onWidgetClicked(Widget * clicked);

	private:
		std::string _id;

		void setLayout(Widget * contents, Widget * buttons);

		ButtonWidget * buttonOk;
};

#endif // DIALOG_H
