#include "Dialog.h"
#include "LinearContainer.h"

Dialog::Dialog(std::string id, std::string message) : _id(id) {
	LinearContainer * buttons = new LinearContainer();
	buttons->setHorizontal();

	buttonOk = new ButtonWidget(new TextWidget("Ok", 0, 0));
	buttons->addWidget(buttonOk);

	setLayout(setTextMessage(message), buttons);

	_ct = -getWidth();
}

Dialog::Dialog(std::string id, std::string message, std::string positiveButton, std::string negativeButton, std::string neutralButton) : _id(id) {
	LinearContainer * buttons = new LinearContainer();
	buttons->setHorizontal();

	buttonPositive = new ButtonWidget(new TextWidget(positiveButton, 0, 0));
	buttons->addWidget(buttonPositive);
	buttonNegative = new ButtonWidget(new TextWidget(negativeButton, 0, 0));
	buttons->addWidget(buttonNegative);
	buttonNeutral = new ButtonWidget(new TextWidget(neutralButton, 0, 0));
	buttons->addWidget(buttonNeutral);

	setLayout(setTextMessage(message), buttons);

	_ct = -getWidth();
}

Widget * Dialog::setTextMessage(std::string message) {
	LinearContainer * text = new LinearContainer();
	text->setSpacing(4);
	text->setVertical();

	size_t index = 0;

	while ((index = message.find('\n')) != std::string::npos) {
		text->addWidget(new TextWidget(message.substr(0, index), 0, 0));
		message.erase(0, index + 1);
	}

	text->addWidget(new TextWidget(message.substr(0, message.length()), 0, 0));
	return text;
}

std::string Dialog::getId() {
	return _id;
}

bool Dialog::operator==(std::string id) {
	return _id == id;
}

void * Dialog::getTag() {
	return _tag;
}

void Dialog::setTag(void * tag) {
	_tag = tag;
}

void Dialog::show() {
	Window::show();
	centerOnParent();
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

		if (getParent() != NULL) getParent()->onDialogResult(this, DIALOG_BUTTON_ID_OK);
	} else if (clicked == buttonPositive) {
		if (getParent() != NULL) getParent()->onDialogResult(this, DIALOG_BUTTON_ID_POSITIVE);
	} else if (clicked == buttonNegative) {
		if (getParent() != NULL) getParent()->onDialogResult(this, DIALOG_BUTTON_ID_NEGATIVE);
	} else if (clicked == buttonNeutral) {
		if (getParent() != NULL) getParent()->onDialogResult(this, DIALOG_BUTTON_ID_NEUTRAL);
	} else {
		WidgetContainer::onWidgetClicked(clicked);
	}
}
