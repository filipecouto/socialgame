#ifndef NOTIFICATIONSNAVIGATOR_H
#define NOTIFICATIONSNAVIGATOR_H

#include "GUI/Window.h"
#include "GUI/TextWidget.h"
#include "GameController.h"
#include <map>

class NotificationsNavigator : public Window {
	public:
		NotificationsNavigator(GameController * controller);

		virtual void onWidgetClicked(Widget * clicked);

		virtual void show();

	private:
		GameController * controller;

		Widget * bAccept, * bChallenge, * bRefuse;

		Widget * bPrev, * bNext;
		TextWidget * tNotification, * tType, * tData;

		int index;

		void loadNotification(INotification * notification);
		
		void onMinigameSelected(IMinigame * minigame);

		class Space : public Widget {
			public:
				Space() {
					w = 160;
				}
		};

		class MinigameSelector : public Window {
			public:
				MinigameSelector(NotificationsNavigator * parent);

				virtual void show();
				
				virtual void onWidgetClicked(Widget * clicked);

			private:
				NotificationsNavigator * parent;
				
				Widget * bClose;
				std::map<Widget*, IMinigame*> minigames;
		};
		
		MinigameSelector * minigameSelector = NULL;
};

#endif // NOTIFICATIONSNAVIGATOR_H
