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

Bridge::Bridge(GameController * controller) :  _controller(controller) {

}
#include <cstdio>
bool Bridge::onWidgetClicked(Widget * widget) {
	if(widget == barCamera) {
		printf("Clicked camera button\n");
	} else {
		printf("Clicked something else\n");
	}
}

Widget * Bridge::getTopBar() {
	if (bar == NULL) {
		bar = new LinearContainer();
		barCamera = new ButtonWidget(new TextWidget("Camera", 0, 0));
		barNotifications = new ButtonWidget(new TextWidget("Notifications", 0, 0));
		barPendingGames = new ButtonWidget(new TextWidget("Pending Games", 0, 0));
		barSettings = new ButtonWidget(new TextWidget("Settings", 0, 0));
		//bar->addWidget(new TextBoxWidget("ola", 0, 0));
		bar->addWidget(barCamera);
		bar->addWidget(barNotifications);
		bar->addWidget(barPendingGames);
		bar->addWidget(barSettings);
	}
	
	return bar;
}

Bridge::~Bridge() {

}
