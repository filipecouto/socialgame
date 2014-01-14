#ifndef PENDINGGAMESNAVIGATOR_H
#define PENDINGGAMESNAVIGATOR_H

#include "GUI/TextWidget.h"
#include "GUI/Dialog.h"
#include "GameController.h"
#include "Models/IPendingGame.h"
#include <map>

class PendingGamesNavigator : public Window {
	public:
		PendingGamesNavigator(GameController * controller);

		virtual void onWidgetClicked(Widget * clicked);

		virtual void show();

	private:
		GameController * controller;

		Widget * bPlay;

		Widget * bPrev, * bNext;
		TextWidget * tNotification, * tType, * tData;

		int index;

		void loadPendingGame(IPendingGame * game);

		class Space : public Widget {
			public:
				Space() {
					w = 160;
				}
		};
};

#endif // PENDINGGAMESNAVIGATOR_H
