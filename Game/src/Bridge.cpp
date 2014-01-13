/**
 * Bridge - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "Bridge.h"
#include "GUI/LinearContainer.h"
#include "GUI/ButtonWidget.h"
#include "GUI/TextBoxWidget.h"

#include "Mods/TestMod/TestMod.h"
#include "Models/IMessageNotification.h"
#include "Models/IFriendshipRequestNotification.h"
#include "Models/INotificationsList.h"
#include "Minigames/Test/TestMinigame.h"
#include "Minigames/TicTacToe/TicTacToe.h"
#include "Minigames/Maze/MazeMinigame.h"
#include "Minigames/Hangman/Hangman.h"

Bridge::Bridge(Gui * gui, GameController * controller) : _gui(gui), _controller(controller) {
	gui->setEventsListener(this);
	controller->setListener(this);

	controller->start(new TestMod());

	loginForm = new LoginForm(controller);
	_gui->addWidget(loginForm);
}
#include <cstdio>
bool Bridge::onWidgetClicked(Widget * widget) {
	if (widget == barCamera) {
		if (_controller->getCamera()->getType() == ThirdPerson) {
			_controller->getCamera()->setType(FreeMode);
			printf("Switching camera to free mode...\n");
		} else if (_controller->getCamera()->getType() == FreeMode) {
			_controller->getCamera()->setType(FirstPerson);
			printf("Switching camera to first person...\n");
		} else {
			_controller->getCamera()->setType(ThirdPerson);
			printf("Switching camera to third person...\n");
		}
	} else if (widget == barNotifications) {
		if (!notifications) {
			notifications = new NotificationsNavigator(_controller);
			notifications->visible = false;
			_gui->addWidget(notifications);
		}

		notifications->x = _gui->getWidth() - notifications->w;
		notifications->y = _gui->getHeigth() - bar->getHeigth() - notifications->h;

		if (notifications->visible) {
			notifications->hide();
			updateNotificationsButton();
		} else {
			notifications->show();
		}
	} else if (widget == barSettings) {
		if (!settingsWindow) {
			settingsWindow = new SettingsWindow(_controller);
			_gui->addWidget(settingsWindow);
		}

		if (windowPersonInfo && windowPersonInfo->visible) windowPersonInfo->hide();
		
		settingsWindow->centerOnParent();
		settingsWindow->show();
	} else if (widget == barTest1) {
		_controller->startMinigame(new TicTacToeMinigame(_controller));
	} else if (widget == barTest2) {
		_controller->startMinigame(new MazeMinigame(_controller));
	} else if (widget == barTest3) {
		_controller->startMinigame(new HangmanMinigame(_controller));
	} else if (windowPersonInfo && windowPersonInfo->visible) {
		if (widget == windowPersonInfo->getCloseButton()) {
			windowPersonInfo->hide();
		} else if (widget == windowPersonInfo->getGoToButton()) {
			_controller->flyTo(_controller->getSelectedPerson());
		} else if (widget == windowPersonInfo->getAddFriendButton()) {
			timeFriendAdded = glutGet(GLUT_ELAPSED_TIME);

			IPerson * selected = _controller->getSelectedPerson();

			if (_controller->getIdentity()->getPerson()->getConnections()->getConnectionWith(selected))
				_controller->getIdentity()->removeFriend(selected);
			else
				_controller->getIdentity()->addFriend(selected);

			_controller->invalidatePerson(_controller->getIdentityPerson());
			_controller->invalidatePerson(selected);

			windowPersonInfo->hide();
		}
	}

	return true;
}

bool Bridge::onDialogResult(Dialog * dialog, int buttonId) {
	if (dialog->getId() == "message" && !showFirstMessage) {
		if (buttonId == Dialog::DIALOG_BUTTON_ID_OK) {
			((TestMod *)_controller->getGameMod())->doSomething();
		}

		showFirstMessage = true;
	} else if (dialog->getId() == "friendship request") {
		dialog->hide();

		IFriendshipRequestNotification * n = (IFriendshipRequestNotification *)dialog->getTag();

		switch (buttonId) {
			case Dialog::DIALOG_BUTTON_ID_POSITIVE:
				n->accept();
				_controller->invalidatePerson(_controller->getIdentityPerson());
				_controller->invalidatePerson(n->getConnection()->getPerson());
				break;

			case Dialog::DIALOG_BUTTON_ID_NEGATIVE:
				n->refuse();
				_controller->invalidatePerson(_controller->getIdentityPerson());
				_controller->invalidatePerson(n->getConnection()->getPerson());
				break;

			case Dialog::DIALOG_BUTTON_ID_NEUTRAL:
				break;
		}
	}

	return true;
}

void Bridge::onMouseButton(int button, int state, int x, int y) {
	if (state == 0 && button == 0 && !_controller->isInMinigame()) {
		_mouseX = x;
		_mouseY = y;

		if (windowPersonInfo) windowPersonInfo->hide();

		_controller->pick(x, y);
	} else {
		_controller->onMouseButton(state, button, x, y);
	}
}

void Bridge::onPersonClicked(IPerson * person) {
	if (windowPersonInfo) windowPersonInfo->display(_controller->getIdentityPerson(), person);
	else {
		windowPersonInfo = new PersonInfoWindow(_controller->getIdentityPerson(), person);
		_gui->addWidget(windowPersonInfo);
	}

	windowPersonInfo->show();
	windowPersonInfo->x = _mouseX;
	windowPersonInfo->y = _mouseY;
	windowPersonInfo->avoidOutside();
}

Widget * Bridge::getTopBar() {
	if (bar == NULL) {
		bar = new LinearContainer();
		barCamera = new ButtonWidget(new TextWidget("Camera", 0, 0));
		LinearContainer * buttonNotifications = new LinearContainer();
		buttonNotifications->setHorizontal();
		buttonNotifications->setSpacing(4);
		buttonNotifications->addWidget(new TextWidget("Notifications", 0, 0));

		if (!tNotifications) tNotifications = new TextWidget("", 0, 0);

		buttonNotifications->addWidget(tNotifications);
		barNotifications = new ButtonWidget(buttonNotifications);
		barPendingGames = new ButtonWidget(new TextWidget("Pending Games", 0, 0));
		barSettings = new ButtonWidget(new TextWidget("Settings", 0, 0));
		bar->addWidget(barCamera);
		bar->addWidget(barNotifications);
		bar->addWidget(barPendingGames);
		bar->addWidget(barSettings);

		barTest1 = new ButtonWidget(new TextWidget("Tic Tac Toe", 0, 0));
		barTest2 = new ButtonWidget(new TextWidget("Maze", 0, 0));
		barTest3 = new ButtonWidget(new TextWidget("Hangman", 0, 0));
		bar->addWidget(barTest1);
		bar->addWidget(barTest2);
		bar->addWidget(barTest3);
	}

	if (loginForm->visible) loginForm->centerOnParent();

	return bar;
}

void Bridge::onNewNotification(INotification * notification) {
	Dialog * message = NULL;

	switch (notification->getType()) {
		case INotification::Message: {
			message = _gui->showMessage("message", ((IMessageNotification *)notification)->getMessage());
		}
		break;

		case INotification::FriendshipRequest: {
			IFriendshipRequestNotification * n = (IFriendshipRequestNotification *) notification;

			switch (n->getConnection()->getState()) {
				case -1:
					message = _gui->showMessage(n->getConnection()->getPerson()->getName() + " refused to be friends with you.");
					break;

				case 0: {
					Dialog * d = _gui->showYesNoCancelMessage("friendship request",
					                                          n->getConnection()->getPerson()->getName() + " sent you a friendship request.",
					                                          "Accept", "Refuse", "Later");
					d->setTag(n);
				}
				break;

				case 1:
					message = _gui->showMessage(n->getConnection()->getPerson()->getName() + " accepted to be friends with you.");
					break;
			}

			_controller->invalidatePerson(_controller->getIdentityPerson());
			_controller->invalidatePerson(n->getConnection()->getPerson());
		}
		break;
	}

	if (message && windowPersonInfo && glutGet(GLUT_ELAPSED_TIME) - timeFriendAdded < 5) {
		message->x = windowPersonInfo->x;
		message->y = windowPersonInfo->y;
		message->avoidOutside();
	}
}

void Bridge::onGameLoaded() {
	updateNotificationsButton();
}

void Bridge::updateNotificationsButton() {
	GameMod * mod = _controller->getGameMod();

	if (!tNotifications) tNotifications = new TextWidget("", 0, 0);

	if (mod->getNotifications()) {
		int count = mod->getNotifications()->getUnreadCount();
		tNotifications->setText(std::to_string(count));
		tNotifications->setTextColor(count == 0 ? 0.8 : 0.1, count == 0 ? 0.8 : 0.9, count == 0 ? 0.8 : 0.1);
	} else {
		tNotifications->setText("-");
		tNotifications->setTextColor(0.5, 0.5, 0.5);
	}
}

Bridge::~Bridge() {

}

PersonInfoWindow::PersonInfoWindow(IPerson * me, IPerson * person): Window() {
	LinearContainer * layout = new LinearContainer();
	layout->setSpacing(8);
	layout->setVertical();

	textName = new TextWidget("", GLUT_BITMAP_HELVETICA_18, 0, 0);
	layout->addWidget(textName);

	textMood = new TextWidget("", GLUT_BITMAP_HELVETICA_12, 0, 0);
	layout->addWidget(textMood);

	textFriends = new TextWidget("", GLUT_BITMAP_HELVETICA_12, 0, 0);
	layout->addWidget(textFriends);

	LinearContainer * buttons = new LinearContainer();
	buttonAddFriend = new ButtonWidget(new TextWidget("Add Friend", 0, 0));
	buttons->addWidget(buttonAddFriend);
	buttonGoTo = new ButtonWidget(new TextWidget("Fly to Here", 0, 0));
	buttons->addWidget(buttonGoTo);
	buttonClose = new ButtonWidget(new TextWidget("Close", 0, 0));
	buttons->addWidget(buttonClose);
	layout->addWidget(buttons);

	setContent(layout);

	display(me, person);
}

void PersonInfoWindow::display(IPerson * me, IPerson * person) {
	textName->setText(person->getName());
	textMood->setText(person->getMood() ? person->getMood()->getDescription() : "Couldn't understand mood");
	textFriends->setText(person->getConnections() ? std::to_string(person->getConnections()->getFriendsCount()) + " friend(s)" : "Couldn't count friends");

	if (me == person) {
		buttonAddFriend->visible = false;
	} else {
		buttonAddFriend->visible = true;
		((TextWidget *) buttonAddFriend->getContainingWidget())->setText(me->getConnections()->isFriendsWith(person) ? "Remove friend" : "Add friend");
	}
}

PersonInfoWindow::~PersonInfoWindow() {

}
Widget * PersonInfoWindow::getAddFriendButton() {
	return buttonAddFriend;
}

Widget * PersonInfoWindow::getGoToButton() {
	return buttonGoTo;
}

Widget * PersonInfoWindow::getCloseButton() {
	return buttonClose;
}
