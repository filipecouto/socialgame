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
#include "GUI/Window.h"
#include "GUI/TextWidget.h"
#include "GUI/ButtonWidget.h"
#include "GameController.h"
#include "IGameControllerListener.h"

class PersonInfoWindow;

/**
 * This class connects the GameController to the GUI, this class will add
 * the GUI components to the screen and assign actions to them in order
 * to interact with the GameController.
 */
class Bridge : public IWidgetEventsListener, public IGameControllerListener {
	public:
		Bridge(Gui * gui, GameController * controller);

		Widget * getTopBar();

		// events from GUI
		virtual bool onWidgetClicked(Widget * widget);

		// events from GameController
		virtual void onPersonClicked(IPerson * person);
		
		// events from GameMod
		virtual void onNewNotification(INotification * notification);
		
		// other events
		void onMouseButton( int button, int state, int x, int y );

		~Bridge();

	private:
		Gui * _gui;
		GameController * _controller;
		PersonInfoWindow * windowPersonInfo = NULL;
		WidgetContainer * bar = NULL;
		Widget * barCamera, * barNotifications, * barPendingGames, * barSettings, * barTest1, * barTest2, * barTest3;
		
		int _mouseX, _mouseY;
		int timeFriendAdded = -1;
};

class PersonInfoWindow : public Window {
	public:
		PersonInfoWindow(IPerson * me, IPerson * person);

		void display(IPerson * me, IPerson * person);
		
		Widget * getAddFriendButton();
		Widget * getGoToButton();
		Widget * getCloseButton();

		virtual ~PersonInfoWindow();

	private:
		TextWidget * textName, * textMood, * textFriends;
		ButtonWidget * buttonAddFriend, * buttonGoTo, * buttonClose;
};

#endif // BRIDGE_H
