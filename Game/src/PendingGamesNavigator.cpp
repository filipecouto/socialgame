#include "PendingGamesNavigator.h"
#include "GUI/LinearContainer.h"
#include "GUI/ButtonWidget.h"
#include "GUI/TextBoxWidget.h"
#include "Models/IFriendshipRequestNotification.h"
#include "Models/INotificationsList.h"
#include "Models/IConnectionsList.h"
#include "Models/IPendingGamesList.h"
#include "Minigames/MinigameFactory.h"

PendingGamesNavigator::PendingGamesNavigator(GameController * controller) : controller(controller) {
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


	bPlay = new ButtonWidget(new TextWidget("Play", 0, 0));
	buttons->addWidget(bPlay);
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

void PendingGamesNavigator::show() {
	if (!controller->getGameMod()->getPendingGames() || controller->getGameMod()->getPendingGames()->size() == 0) {
		visible = false;
		return;
	}

	Window::show();

	loadPendingGame(controller->getGameMod()->getPendingGames()->operator[](index));
}

void PendingGamesNavigator::loadPendingGame(IPendingGame * game) {
	if (!controller->getGameMod()->getPendingGames()) {
		hide();
		return;
	}

	if (game) {
		tNotification->setText("Pending minigame " + std::to_string(index + 1) +
		                       " of " + std::to_string(controller->getGameMod()->getPendingGames()->size()));
		IMinigame * minigame = game->getMinigame(0, controller->getMinigameFactory());
		tType->setText(minigame->getName());
		tData->setText("From: " + game->getConnection()->getPerson()->getName());
	}
}

void PendingGamesNavigator::onWidgetClicked(Widget * clicked) {
	if (controller->getGameMod()->getNotifications()) {
		if (clicked == bNext) {
			int count = controller->getGameMod()->getPendingGames()->size();

			if (index + 1 < count) {
				index++;
				loadPendingGame(controller->getGameMod()->getPendingGames()->operator[](index));
			}
		} else if (clicked == bPrev) {
			if (index > 0) {
				index--;
				loadPendingGame(controller->getGameMod()->getPendingGames()->operator[](index));
			}
		} else if (clicked == bPlay) {
			controller->startMinigame(controller->getGameMod()->getPendingGames()->operator[](index), 0);
			hide();
		}
	}
}
