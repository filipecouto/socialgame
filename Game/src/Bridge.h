/**
 * Bridge - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef BRIDGE_H
#define BRIDGE_H

#include "GUI/IWidgetEventsListener.h"
#include "GUI/Gui.h"
#include "GameController.h"

/**
 * This class connects the GameController to the GUI, this class will add
 * the GUI components to the screen and assign actions to them in order
 * to interact with the GameController.
 */
class Bridge : public IWidgetEventsListener {
	public:
		Bridge(GameController * controller);
		
		Widget * getTopBar();
		
		virtual bool onWidgetClicked(Widget * widget);
		
		~Bridge();
		
	private:
		GameController * _controller;
		
		WidgetContainer * bar = NULL;
		Widget * barCamera, * barNotifications, * barPendingGames, * barSettings;
};

#endif // BRIDGE_H
