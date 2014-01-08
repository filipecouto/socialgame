#ifndef DIALOG_H
#define DIALOG_H

#include <string>

#include "Window.h"
#include "ButtonWidget.h"

class Dialog : public Window {
	public:
		Dialog(std::string id, std::string message);
		Dialog(std::string id, std::string message, std::string positiveButton, std::string negativeButton, std::string neutralButton);

		virtual void centerOnParent();
		
		virtual void show();

		virtual void onWidgetClicked(Widget * clicked);
		
		std::string getId();
		bool operator==(std::string id);
		
		void setTag(void * tag);
		void * getTag();
		
		const static int DIALOG_BUTTON_ID_OK = 1;
		const static int DIALOG_BUTTON_ID_POSITIVE = 2;
		const static int DIALOG_BUTTON_ID_NEGATIVE = 4;
		const static int DIALOG_BUTTON_ID_NEUTRAL = 8;

	private:
		std::string _id;
		void * _tag;

		Widget * setTextMessage(std::string message);
		void setLayout(Widget * contents, Widget * buttons);

		ButtonWidget * buttonOk, * buttonPositive, * buttonNegative, * buttonNeutral;
};

#endif // DIALOG_H
