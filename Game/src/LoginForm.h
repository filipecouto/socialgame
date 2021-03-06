/**
 * LoginForm - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "GUI/Window.h"
#include "GUI/TextBoxWidget.h"
#include "GUI/ButtonWidget.h"

class GameController;

class LoginForm : public Window {
	public:
		LoginForm(GameController * controller);

		virtual void onWidgetClicked(Widget * clicked);
		virtual void onParentGeometryChange(Widget * widget);

		~LoginForm();

	private:
		GameController * controller;

		TextBoxWidget * tEmail;
		TextBoxWidget * tPassword;

		TextWidget * tError;

		ButtonWidget * bNormalMode;
		ButtonWidget * bAdvancedMode;
};

#endif // LOGINFORM_H
