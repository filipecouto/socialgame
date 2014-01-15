#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <map>

#include "GUI/Window.h"
#include "GUI/TextBoxWidget.h"
#include "GUI/ButtonWidget.h"
#include "GameController.h"

class SettingsWindow : public Window {
	public:
		SettingsWindow(GameController * controller);

		virtual void onParentGeometryChange(Widget * widget);
		virtual void onWidgetClicked(Widget * clicked);
		
		virtual void show();

	private:
		GameController * controller;

		TextWidget * tMood;
		TextBoxWidget * tTags;
		ButtonWidget * bSaveTags, * bClose;
		
		WidgetContainer * lMoods;
		
		std::map<Widget*, IMood*> moodButtons;
		
		Widget * makeTitle(std::string title);
		WidgetContainer * getMoods();
		
		void loadTags();
};

#endif // SETTINGSWINDOW_H
