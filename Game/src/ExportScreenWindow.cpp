/**
 * LoginForm - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#include "ExportScreenWindow.h"
#include "GUI/LinearContainer.h"
#include "GameController.h"

ExportScreenWindow::ExportScreenWindow(GameController * controller, Gui * gui) : controller(controller), _gui(gui) {
	exportScreen = new ExportScreen(); 
	
	setPadding(16);

	LinearContainer * layout = new LinearContainer();
	layout->setSpacing(16);
	layout->setVertical();
	
	layout->addWidget(makeTitle("Export Menu"));

	LinearContainer * line = new LinearContainer();
	line->setSpacing(4);
	line->setVertical();
	line->addWidget(new TextWidget("File Name", 0, 0));
	fileName = new TextBoxWidget("exampleName", 0, 0);
	line->addWidget(fileName);
	layout->addWidget(line);
	
	tMessage = new TextWidget("", 0.8f, 0, 0, 1, 0, 0);
	tMessage->visible = false;
	layout->addWidget(tMessage);

	LinearContainer * buttons = new LinearContainer();
	buttons->setHorizontal();

	exportToJPG = new ButtonWidget(new TextWidget("Export to JPG", 0, 0));
	buttons->addWidget(exportToJPG);
	exportToTGA = new ButtonWidget(new TextWidget("Export to TGA", 0, 0));
	buttons->addWidget(exportToTGA);
	layout->addWidget(buttons);
	
	close = new ButtonWidget(new TextWidget("Close", 0, 0));
	layout->addWidget(close);

	setContent(layout);
}

Widget * ExportScreenWindow::makeTitle(std::string title) {
	return new TextWidget(title, GLUT_BITMAP_HELVETICA_18, 0, 0);
}

void ExportScreenWindow::onWidgetClicked(Widget * clicked) {
	bool state = false;
	if (exportToJPG == clicked) {
		state = exportScreen->takePrint(fileName->getText(), "jpg", _gui->getWidth(), _gui->getHeigth());
		tMessage->visible = true;
		if(state)tMessage->setText("Exported To JPG");
		else tMessage->setText("Failed to Export JPG");
	} else if (exportToTGA == clicked) {
		state = exportScreen->takePrint(fileName->getText(), "tga", _gui->getWidth(), _gui->getHeigth());
		tMessage->visible = true;
		tMessage->setText("Exported To TGA");
		if(state)tMessage->setText("Exported To TGA");
		else tMessage->setText("Failed to Export TGA");
	} else if (close == clicked) {
		tMessage->visible = false;
		tMessage->setText("");
		fileName->setText("exampleName");
		hide();
	} 
}

void ExportScreenWindow::onParentGeometryChange(Widget * widget) {
	Window::onParentGeometryChange(widget);
	if(_parent) centerOnParent();
}

ExportScreenWindow::~ExportScreenWindow() {
	delete fileName;
	delete tMessage;
	delete exportToJPG;
	delete exportToTGA;
	delete close;
}