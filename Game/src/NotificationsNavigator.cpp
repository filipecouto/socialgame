#include "NotificationsNavigator.h"
#include "GUI/LinearContainer.h"
#include "GUI/ButtonWidget.h"
#include "Models/IFriendshipRequestNotification.h"
#include "Models/INotificationsList.h"

NotificationsNavigator::NotificationsNavigator(GameController * controller) : controller(controller) {
	index = 0;

	setPadding(8);

	LinearContainer * layout = new LinearContainer();
	layout->setSpacing(8);
	layout->setVertical();

	LinearContainer * buttons = new LinearContainer();
	buttons->setHorizontal();

	tNotification = new TextWidget("", 0.8, 0.8, 0.8, 1, 0, 0);
	layout->addWidget(tNotification);
	tType = new TextWidget("", 0, 0);
	layout->addWidget(tType);
	tData = new TextWidget("", 0, 0);
	layout->addWidget(tData);


	bAccept = new ButtonWidget(new TextWidget("Accept", 0, 0));
	buttons->addWidget(bAccept);
	bRefuse = new ButtonWidget(new TextWidget("Refuse", 0, 0));
	buttons->addWidget(bRefuse);
	layout->addWidget(buttons);

	buttons = new LinearContainer();
	buttons->setHorizontal();

	bPrev = new ButtonWidget(new TextWidget(" < ", 0, 0));
	buttons->addWidget(bPrev);
	buttons->addWidget(new Space());
	bNext = new ButtonWidget(new TextWidget(" > ", 0, 0));
	buttons->addWidget(bNext);

	layout->addWidget(buttons);

	setContent(layout);
}

void NotificationsNavigator::show() {
	if (!controller->getGameMod()->getNotifications()) {
		visible = false;
		return;
	}

	Window::show();

	loadNotification(controller->getGameMod()->getNotifications()->operator[](index));
}

void NotificationsNavigator::loadNotification(INotification * notification) {
	if (!controller->getGameMod()->getNotifications()) {
		hide();
		return;
	}

	if (notification) {
		if (notification->getType() == INotification::FriendshipRequest) {
			IFriendshipRequestNotification * n = (IFriendshipRequestNotification *)notification;
			tNotification->setText("Notification " + std::to_string(index + 1) +
			                       " of " + std::to_string(controller->getGameMod()->getNotifications()->size()));
			tType->setText("Friendship request");
			tData->setText("From: " + n->getFrom()->getName());
		}

		notification->setRead(true);
	}
}

void NotificationsNavigator::onWidgetClicked(Widget * clicked) {
	if (controller->getGameMod()->getNotifications()) {
		if (clicked == bNext) {
			int count = controller->getGameMod()->getNotifications()->size();

			if (index + 1 < count) {
				index++;
				loadNotification(controller->getGameMod()->getNotifications()->operator[](index));
			}
		} else if (clicked == bPrev) {
			if (index > 0) {
				index--;
				loadNotification(controller->getGameMod()->getNotifications()->operator[](index));
			}
		}
	}
}
