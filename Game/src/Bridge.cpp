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

Bridge::Bridge(Gui * gui, GameController * controller) : _gui(gui), _controller(controller) {
	gui->setEventsListener(this);
	controller->setListener(this);
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
	} else if (windowPersonInfo && windowPersonInfo->visible) {
		if (widget == windowPersonInfo->getCloseButton()) {
			windowPersonInfo->hide();
		}
	}
}

void Bridge::onMouseButton(int button, int state, int x, int y) {
	if (state == 0 && button == 0) {
		_mouseX = x;
		_mouseY = y;

		if (windowPersonInfo) windowPersonInfo->hide();

		_controller->pick(x, y);
	}
}

void Bridge::onPersonClicked(IPerson * person) {
	if (windowPersonInfo) windowPersonInfo->display(person);
	else {
		windowPersonInfo = new PersonInfoWindow(person);
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
		barNotifications = new ButtonWidget(new TextWidget("Notifications", 0, 0));
		barPendingGames = new ButtonWidget(new TextWidget("Pending Games", 0, 0));
		barSettings = new ButtonWidget(new TextWidget("Settings", 0, 0));
		bar->addWidget(barCamera);
		bar->addWidget(barNotifications);
		bar->addWidget(barPendingGames);
		bar->addWidget(barSettings);
	}

	return bar;
}

Bridge::~Bridge() {

}

PersonInfoWindow::PersonInfoWindow(IPerson * person): Window() {
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
	buttonGoTo = new ButtonWidget(new TextWidget("Go To", 0, 0));
	buttons->addWidget(buttonGoTo);
	buttonClose = new ButtonWidget(new TextWidget("Close", 0, 0));
	buttons->addWidget(buttonClose);
	layout->addWidget(buttons);

	setContent(layout);

	display(person);
}

void PersonInfoWindow::display(IPerson * person) {
	textName->setText(person->getName());
	textMood->setText(person->getMood().getDescription());
	textFriends->setText(std::to_string(person->getConnections().size()) + " friend(s)");
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
