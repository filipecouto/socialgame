#include "Dialog.h"
#include "LinearContainer.h"

Dialog::Dialog(std::string id, std::string message) : _id(id) {
	LinearContainer * text = new LinearContainer();
	text->setSpacing(4);
	text->setVertical();
	
	size_t index = 0;

	while ((index = message.find('\n')) != std::string::npos) {
		text->addWidget(new TextWidget(message.substr(0, index), 0, 0));
		message.erase(0, index + 1);
	}
	
	text->addWidget(new TextWidget(message.substr(0, message.length()), 0, 0));

	//TextWidget * _message = new TextWidget(message, 0, 0);

	LinearContainer * buttons = new LinearContainer();
	buttons->setHorizontal();

	buttonOk = new ButtonWidget(new TextWidget("Ok", 0, 0));
	buttons->addWidget(buttonOk);

	setLayout(text, buttons);

	_ct = -getWidth();
}

void Dialog::show() {
	Window::show();
	centerOnParent();
}

void Dialog::centerOnParent() {
	x = getParent()->getWidth() / 2 - getWidth() / 2;
	y = getParent()->getHeigth() / 2 - getHeigth() / 2;
}

void Dialog::setLayout(Widget * contents, Widget * buttons) {
	LinearContainer * container = new LinearContainer();
	container->setVertical();
	container->setSpacing(8);
	container->addWidget(contents);
	container->addWidget(buttons);

	setPadding(8);

	setContent(container);
}

void Dialog::onWidgetClicked(Widget * clicked) {
	if (clicked == buttonOk) {
		hide();
	} else {
		WidgetContainer::onWidgetClicked(clicked);
	}
}
