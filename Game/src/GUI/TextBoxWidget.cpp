#include "TextBoxWidget.h"

TextBoxWidget::TextBoxWidget(): TextBoxWidget("", 0, 0) {

}

TextBoxWidget::TextBoxWidget(std::string text, GLfloat xPos, GLfloat yPos): TextBoxWidget(text, 1, 1, 1, 1, GLUT_BITMAP_HELVETICA_12, xPos, yPos) {

}

TextBoxWidget::TextBoxWidget(std::string text, void * font, GLfloat xPos, GLfloat yPos): TextBoxWidget(text, 1, 1, 1, 1, font, xPos, yPos) {

}

TextBoxWidget::TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat xPos, GLfloat yPos): TextBoxWidget(text, r, g, b, a, GLUT_BITMAP_HELVETICA_12, xPos, yPos) {

}

TextBoxWidget::TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, void * font, GLfloat xPos, GLfloat yPos): TextWidget(text, r, g, b, a, font, xPos, yPos), _borderWidth(3) {
	cursorPosition = text.size();
	updateTextSize();
	updateDimensions();
}

void TextBoxWidget::updateTextSize() {
	std::string tmptext = "";
	std::string text = getText();
	if(isPassword()) {
		for(int i=0;i<text.size();i++) {
			tmptext.append("*");
		}
	} else {
		tmptext = text;
	}
	textSize = glutBitmapLength(getFont(), (const unsigned char *) tmptext.substr(0, cursorPosition).c_str());
}

TextBoxWidget::~TextBoxWidget() {

}

GLfloat TextBoxWidget::getMinimumWidth() {
	return TextWidget::getMinimumWidth() + _borderWidth * 2;
}

GLfloat TextBoxWidget::getMinimumHeight() {
	return TextWidget::getMinimumHeight() + _borderWidth * 2;
}

void TextBoxWidget::draw() {
	glTranslatef(_borderWidth, _borderWidth, 0);
	TextWidget::draw();

	if (focused && showCursor) {
		glBegin(GL_QUADS);
		glVertex2f(textSize + 1, -2);
		glVertex2f(textSize + 1, TextWidget::getMinimumHeight() + 2);
		glVertex2f(textSize, TextWidget::getMinimumHeight() + 2);
		glVertex2f(textSize, -2);
		glEnd();
	}

	glTranslatef(-_borderWidth, -_borderWidth, 0);
}

void TextBoxWidget::drawBackground() {
	glTranslatef(-_borderWidth, -_borderWidth, 0);
	//TextWidget::drawBackground();
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(w, 0);
	glVertex2f(w, h);
	glVertex2f(0, h);
	glEnd();
	glColor4f(1, 1, 1, 1.0f);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(w, 0);
	glVertex2f(w, h);
	glVertex2f(0, h);
	glEnd();
	glTranslatef(_borderWidth, _borderWidth, 0);
}

void TextBoxWidget::onMouseEnter(int x, int y) {
	TextWidget::onMouseEnter(x, y);
}

void TextBoxWidget::onMouseExit() {
	TextWidget::onMouseExit();
}

GLboolean TextBoxWidget::onMouseButtonDown(int button, int x, int y) {
	return TextWidget::onMouseButtonDown(button, x, y);
}

GLboolean TextBoxWidget::onMouseButtonUp(int button, int x, int y) {
	return TextWidget::onMouseButtonUp(button, x, y);
}

GLboolean TextBoxWidget::onKeyDown(int key, int special) {
	std::string text = getText();
	int currentPosition = cursorPosition;

	if (key == 0) {
		switch (special) {
			case GLUT_KEY_LEFT:
				currentPosition--;

				if (currentPosition < 0) {
					currentPosition = 0;
				}

				cursorPosition = currentPosition;
				break;

			case GLUT_KEY_RIGHT:
				currentPosition++;

				if (currentPosition > text.length()) {
					currentPosition = text.length();
				}

				cursorPosition = currentPosition;
				break;
		}
	} else {
		if (key == 8) {
			if (currentPosition > 0) {
				text.erase(currentPosition - 1, 1);
				currentPosition--;
			}

			cursorPosition = currentPosition;
		} else if (key == 127) {
			if (currentPosition < text.length()) {
				text.erase(currentPosition, 1);
			}

			cursorPosition = currentPosition;
		} else {
			text.insert(cursorPosition, 1, (char)key);
			cursorPosition++;
		}
	}
	updateTextSize();
	setText(text);
	return true;
}

GLboolean TextBoxWidget::onKeyUp(int key, int special) {
	return true;
}

void TextBoxWidget::onFocus() {
	Widget::onFocus();
	showCursor = true;
}

void TextBoxWidget::onBlur() {
	Widget::onBlur();
}

void TextBoxWidget::updateDimensions() {
	TextWidget::updateDimensions();
	w += _borderWidth * 2;
	h += _borderWidth * 2;
	notifyGeometryChange();
}

void TextBoxWidget::tick(int delta, int absolute) {
	pastTime += delta;

	if (pastTime > 650) {
		pastTime = 0;
		showCursor = !showCursor;
	}
}

GLboolean TextBoxWidget::isAnimating() {
	return focused;
}