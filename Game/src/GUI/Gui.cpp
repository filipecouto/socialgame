#include "Gui.h"

Gui::Gui() {
}

Gui::~Gui() { }

void Gui::drawGui() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, _width, 0, _height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);

	WidgetContainer::draw();

	glDisable(GL_BLEND);
}

void Gui::onMouseEnter(int x, int y) {
	Widget::onMouseEnter(x, _height - y);
}

void Gui::onMouseMove(int x, int y) {
	WidgetContainer::onMouseMove(x, _height - y);
}

GLboolean Gui::onMouseButtonDown(int button, int x, int y) {
	if (!WidgetContainer::onMouseButtonDown(button, x, _height - y)) {
		if (_focused != NULL) _focused->onBlur();

		_focused = NULL;
		
		return GL_FALSE;
	}

	return GL_TRUE;
}

GLboolean Gui::onMouseButtonUp(int button, int x, int y) {
	return WidgetContainer::onMouseButtonUp(button, x, _height - y);
}

void Gui::requestFocus(Widget * from) {
	if (_focused != NULL) _focused->onBlur();

	_focused = from;
	_focused->onFocus();
}

void Gui::setDimensions(int width, int height) {
	_width = width;
	_height = height;
	
	if(_dialog) _dialog->centerOnParent();
}

void Gui::setEventsListener(IWidgetEventsListener * listener) {
	_listener = listener;
}

void Gui::onWidgetClicked(Widget * clicked) {
	if(_listener != NULL) _listener->onWidgetClicked(clicked);
}

void Gui::onDialogResult(Dialog * dialog, int buttonId) {
	if(_listener != NULL) _listener->onDialogResult(dialog, buttonId);
}

int Gui::getWidth() {
	return _width;
}

int Gui::getHeigth() {
	return _height;
}

Dialog * Gui::showMessage(std::string message) {
	return showMessage("", message);
}

Dialog * Gui::showMessage(std::string id, std::string message) {
	_dialog = new Dialog(id, message);
	addWidget(_dialog);
	_dialog->show();
	return _dialog;
}

Dialog * Gui::showYesNoCancelMessage(std::string id, std::string message) {
	return showYesNoCancelMessage(id, message, "Yes", "No", "Cancel");
}

Dialog * Gui::showYesNoCancelMessage(std::string id, std::string message, std::string yes, std::string no, std::string cancel) {
	_dialog = new Dialog(id, message, yes, no, cancel);
	addWidget(_dialog);
	_dialog->show();
	return _dialog;
}
