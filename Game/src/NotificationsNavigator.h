#ifndef NOTIFICATIONSNAVIGATOR_H
#define NOTIFICATIONSNAVIGATOR_H

#include "GUI/Window.h"
#include "GUI/TextWidget.h"
#include "GameController.h"

class NotificationsNavigator : public Window {
	public:
		NotificationsNavigator(GameController * controller);

		virtual void onWidgetClicked(Widget * clicked);
		
		virtual void show();

	private:
		GameController * controller;

		Widget * bAccept, * bRefuse;

		Widget * bPrev, * bNext;
		TextWidget * tNotification, * tType, * tData;
		
		int index;
		
		void loadNotification(INotification * notification);

		class Space : public Widget {
			public:
				Space() {
					w = 160;
				}
		};
};

#endif // NOTIFICATIONSNAVIGATOR_H
