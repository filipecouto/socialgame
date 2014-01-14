#include "NotificationsNavigator.h"
#include "GUI/LinearContainer.h"
#include "GUI/ButtonWidget.h"
#include "GUI/TextBoxWidget.h"
#include "Models/IFriendshipRequestNotification.h"
#include "Models/INotificationsList.h"
#include "Models/IConnectionsList.h"
#include "Minigames/MinigameFactory.h"

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
	bChallenge = new ButtonWidget(new TextWidget("Challenge", 0, 0));
	buttons->addWidget(bChallenge);
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

			bool canAccept = n->getConnection() != NULL && !controller->getGameMod()->getIdentity()->getPerson()->getConnections()->isFriendsWith(n->getFrom());

			if (canAccept) {
				tData->setText("From: " + n->getFrom()->getName());

				bAccept->visible = true;
				bRefuse->visible = true;
			} else {
				tData->setText("Already responded");

				bAccept->visible = false;
				bRefuse->visible = false;
			}
		}

		if (!notification->isRead())
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
		} else if (clicked == bAccept || clicked == bRefuse) {
			INotification * notification = controller->getGameMod()->getNotifications()->operator[](index);

			if (notification && notification->getType() == INotification::FriendshipRequest) {
				IFriendshipRequestNotification * n = (IFriendshipRequestNotification *)notification;

				if (clicked == bAccept) n->accept();
				else if (clicked == bRefuse) n->refuse();

				controller->invalidatePerson(controller->getIdentityPerson());
				controller->invalidatePerson(n->getFrom());
			}
		} else if (clicked == bChallenge) {
			if (!minigameSelector) {
				minigameSelector = new MinigameSelector(this);
				((WidgetContainer *) _parent)->addWidget(minigameSelector);
			}

			minigameSelector->show();
		}
	}
}

void NotificationsNavigator::onMinigameSelected(IMinigame * minigame) {
	if (minigame->getLevelSettings()) {
		if (!numberInputDialog) {
			numberInputDialog = new NumberInputDialog(this);
			((WidgetContainer *) _parent)->addWidget(numberInputDialog);
		}

		numberInputDialog->show(minigame);
	} else {
		onMinigameSelected(minigame, 0);
	}
}

void NotificationsNavigator::onMinigameSelected(IMinigame * minigame, int level) {
	//printf("Selected %s\n", minigame->getInternalName().c_str());
	INotification * notification = controller->getGameMod()->getNotifications()->operator[](index);

	if (notification && notification->getType() == INotification::FriendshipRequest) {
		IFriendshipRequestNotification * n = (IFriendshipRequestNotification *)notification;
		n->challenge(minigame, level);
	}
}

NotificationsNavigator::MinigameSelector::MinigameSelector(NotificationsNavigator * parent) : parent(parent) {
	setPadding(8);

	LinearContainer * layout = new LinearContainer();
	layout->setSpacing(8);
	layout->setVertical();

	layout->addWidget(new TextWidget("Minigames", GLUT_BITMAP_HELVETICA_18, 0, 0));
	layout->addWidget(new TextWidget("Pick a minigame to chalenge your friend", 0, 0));

	std::vector<IMinigame *> minigames = MinigameFactory().getMinigames(parent->controller);
	const int len = minigames.size();

	for (int i = 0; i < len; i++) {
		IMinigame * minigame = minigames[i];
		LinearContainer * button = new LinearContainer();
		button->setSpacing(6);
		button->setVertical();
		button->addWidget(new TextWidget(minigame->getName(), GLUT_BITMAP_HELVETICA_18, 0, 0));
		button->addWidget(new TextWidget(minigame->getDescription(), 0, 0));
		ButtonWidget * b = new ButtonWidget(button);
		layout->addWidget(b);
		this->minigames.insert(std::pair<Widget *, IMinigame *>(b, minigame));
	}

	bClose = new ButtonWidget(new TextWidget("Cancel", 0, 0));
	layout->addWidget(bClose);

	setContent(layout);
}

void NotificationsNavigator::MinigameSelector::onWidgetClicked(Widget * clicked) {
	if (clicked == bClose) {
		hide();
	} else {
		if (minigames.find(clicked) != minigames.end()) {
			parent->onMinigameSelected(minigames[clicked]);
			hide();
		}
	}
}

void NotificationsNavigator::MinigameSelector::show() {
	Window::show();

	if (_parent) centerOnParent();
}

NotificationsNavigator::NumberInputDialog::NumberInputDialog(NotificationsNavigator * parent) : parent(parent) {
	setPadding(8);

	LinearContainer * layout = new LinearContainer();
	layout->setSpacing(8);
	layout->setVertical();

	name = new TextWidget("", GLUT_BITMAP_HELVETICA_18, 0, 0);
	layout->addWidget(name);

	description = new TextWidget("", 0, 0);
	layout->addWidget(description);

	response = new TextBoxWidget();
	layout->addWidget(response);

	LinearContainer * buttons = new LinearContainer();
	buttons->setSpacing(8);
	buttons->setHorizontal();

	ok = new ButtonWidget(new TextWidget("OK", 0, 0));
	buttons->addWidget(ok);

	cancel = new ButtonWidget(new TextWidget("Cancel", 0, 0));
	buttons->addWidget(cancel);

	layout->addWidget(buttons);

	setContent(layout);
}

void NotificationsNavigator::NumberInputDialog::show(IMinigame * minigame) {
	Window::show();

	if (_parent) centerOnParent();

	this->minigame = minigame;

	IMinigame::Level * levelSettings = minigame->getLevelSettings();
	name->setText(levelSettings->getName());
	description->setText("Enter a number from " + std::to_string(levelSettings->getMinValue()) + " to " + std::to_string(levelSettings->getMaxValue()) + ":");
	response->setText(std::to_string((levelSettings->getMaxValue() + levelSettings->getMinValue()) / 2));
}
