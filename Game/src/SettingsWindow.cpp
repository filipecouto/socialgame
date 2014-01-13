#include "SettingsWindow.h"
#include "GUI/LinearContainer.h"
#include "Models/IMoodsList.h"
#include "Models/ITagsList.h"

SettingsWindow::SettingsWindow(GameController * controller) : controller(controller) {
	setPadding(8);

	LinearContainer * layout = new LinearContainer();
	layout->setSpacing(8);
	layout->setVertical();

	layout->addWidget(makeTitle("Mood"));
	IMood * mood = controller->getIdentityPerson()->getMood();
	tMood = new TextWidget(mood ? "You are: " + mood->getDescription() : "Couldn't understand mood", 0, 0);
	layout->addWidget(tMood);
	layout->addWidget(getMoods());

	layout->addWidget(makeTitle("Tags"));
	layout->addWidget(new TextWidget("Write your tags, separating them with a comma", 0, 0));

	LinearContainer * lTags = new LinearContainer();
	lTags->setSpacing(4);
	lTags->setHorizontal();

	tTags = new TextBoxWidget();
	std::string tagsText = "";
	for(int i = 0; i < controller->getIdentityPerson()->getTags()->size(); i++) {
		tagsText += controller->getIdentityPerson()->getTags()->operator[](i)->getName() + ";";
	}
	lTags->addWidget(tTags);
	bSaveTags = new ButtonWidget(new TextWidget("Save", 0, 0));
	lTags->addWidget(bSaveTags);

	layout->addWidget(lTags);

	bClose = new ButtonWidget(new TextWidget("Close", 0, 0));
	layout->addWidget(bClose);

	setContent(layout);
}

WidgetContainer * SettingsWindow::getMoods() {
	LinearContainer * lines = new LinearContainer();
	lines->setVertical();

	LinearContainer * line = NULL;
	IMoodsList * list = controller->getGameMod()->getMoods();
	int len = list->size();
	int i = 0;

	while (i < len) {
		if (!line) {
			line = new LinearContainer();
			line->setHorizontal();
		}

		IMood * mood = list->operator[](i++);
		ButtonWidget * button = new ButtonWidget(new TextWidget(mood->getDescription(), 0, 0));
		line->addWidget(button);
		moodButtons.insert(std::pair<Widget *, IMood *>(button, mood));

		if (line->getMinimumWidth() > 120) {
			lines->addWidget(line);
			line = NULL;
		}
	}

	return lines;
}

Widget * SettingsWindow::makeTitle(std::string title) {
	return new TextWidget(title, GLUT_BITMAP_HELVETICA_18, 0, 0);
}

void SettingsWindow::onWidgetClicked(Widget * clicked) {
	if (clicked == bClose) {
		hide();
	} else if (clicked == bSaveTags) {
		std::string sTags = tTags->getText();
		std::vector<std::string> tags;
		size_t index = 0;

		while ((index = sTags.find(',')) != std::string::npos) {
			tags.push_back(sTags.substr(0, index));
			sTags.erase(0, index + 1);
		}

		controller->getIdentity()->setTags(tags);
	} else {
		if (moodButtons.find(clicked) != moodButtons.end()) {
			IMood * mood = moodButtons[clicked];
			controller->getIdentity()->setMood(mood);
			tMood->setText(mood ? "You are: " + mood->getDescription() : "Couldn't understand mood");
		}
	}
}

void SettingsWindow::onParentGeometryChange(Widget * widget) {
	Window::onParentGeometryChange(widget);

	if (_parent) centerOnParent();
}
