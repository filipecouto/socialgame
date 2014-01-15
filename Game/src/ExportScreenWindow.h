/**
 * ExportScreenWindow - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#ifndef EXPORTSCREENWINDOW_H
#define EXPORTSCREENWINDOW_H

#if _WIN32
#include <GL\glew.h>
#endif

#include "GUI/Window.h"
#include "GUI/TextBoxWidget.h"
#include "GUI/ButtonWidget.h"
#include "GUI/Gui.h"
#include "ExportScreen.h"

class GameController;

class ExportScreenWindow : public Window {
	public:
		ExportScreenWindow(GameController * controller, Gui * gui);

		virtual void onWidgetClicked(Widget * clicked);
		virtual void onParentGeometryChange(Widget * widget);

		virtual ~ExportScreenWindow();

	private:
		Gui * _gui;
		GameController * controller;

		TextBoxWidget * fileName;

		TextWidget * tMessage;

		ButtonWidget * exportToJPG;
		ButtonWidget * exportToTGA;
		ButtonWidget * close;

		Widget * makeTitle(std::string title);

		ExportScreen * exportScreen = NULL;
};

#endif // EXPORTSCREENWINDOW_H
