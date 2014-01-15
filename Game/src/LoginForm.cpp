/**
 * LoginForm - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#include "LoginForm.h"
#include "GUI/LinearContainer.h"
#include "Mods/AdvancedMode/AdvancedMode.h"
#include "Mods/SimpleMode/SimpleMode.h"
#include "GameController.h"
#include "Models/IMoodsList.h"

LoginForm::LoginForm(GameController * controller) : controller(controller) {
	setPadding(16);

	LinearContainer * layout = new LinearContainer();
	layout->setSpacing(16);
	layout->setVertical();

	layout->addWidget(new TextWidget("SOCIAL GAME", 0.2f, 0.7f, 0.9f, 1.0f, GLUT_BITMAP_HELVETICA_18, 0, 0));
	layout->addWidget(new TextWidget("Login", 0, 0));

	LinearContainer * line = new LinearContainer();
	line->setSpacing(4);
	line->setVertical();
	line->addWidget(new TextWidget("E-mail", 0, 0));
	tEmail = new TextBoxWidget("teste@teste.teste", 0, 0);
	line->addWidget(tEmail);
	layout->addWidget(line);

	line = new LinearContainer();
	line->setSpacing(4);
	line->setVertical();
	line->addWidget(new TextWidget("Password", 0, 0));
	tPassword = new TextBoxWidget("123456", 0, 0);
	tPassword->setPassword(true);
	line->addWidget(tPassword);
	layout->addWidget(line);
	
	tError = new TextWidget("", 0.8f, 0, 0, 1, 0, 0);
	tError->visible = false;
	layout->addWidget(tError);

	LinearContainer * buttons = new LinearContainer();
	buttons->setHorizontal();

	bNormalMode = new ButtonWidget(new TextWidget(controller->getString("mode_normal"), 0, 0));
	buttons->addWidget(bNormalMode);
	bAdvancedMode = new ButtonWidget(new TextWidget(controller->getString("mode_advanced"), 0, 0));
	buttons->addWidget(bAdvancedMode);

	layout->addWidget(buttons);

	setContent(layout);
}

void LoginForm::onWidgetClicked(Widget * clicked) {
	if (bNormalMode == clicked) {
		SimpleMode::SimpleMode * mode = new SimpleMode::SimpleMode();
		controller->start(mode);
		hide();
	} else if (bAdvancedMode == clicked) {
		AdvancedMode::AdvancedMode * mode = new AdvancedMode::AdvancedMode();
		int result = mode->login(tEmail->getText(), tPassword->getText());
		if(result == -1) {
			tError->visible = true;
			tError->setText("Wrong e-mail or password");
		} else {
			//printf("Welcome %s!\n", mode->getIdentity()->getPerson()->getName().c_str());
			//printf("There are %d moods.\n", mode->getMoods()->size());
			controller->start(mode);
			hide();
		}
	}
}

void LoginForm::onParentGeometryChange(Widget * widget) {
	Window::onParentGeometryChange(widget);
	if(_parent) centerOnParent();
}

LoginForm::~LoginForm() {
	delete tEmail;
	delete tError;
	delete tPassword;
	delete bAdvancedMode;
	delete bNormalMode;
}
