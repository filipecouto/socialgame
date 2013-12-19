#include "TextBoxWidget.h"

TextBoxWidget::TextBoxWidget()
{

}

TextBoxWidget::TextBoxWidget(std::string text, GLfloat xPos, GLfloat yPos): TextWidget(text, xPos, yPos)
{

}

TextBoxWidget::TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, void* font, GLfloat xPos, GLfloat yPos): TextWidget(text, xPos, yPos)
{

}

TextBoxWidget::TextBoxWidget(std::string text, void* font, GLfloat xPos, GLfloat yPos): TextWidget(text, xPos, yPos)
{

}

TextBoxWidget::TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat xPos, GLfloat yPos): TextWidget(text, xPos, yPos)
{

}

TextBoxWidget::~TextBoxWidget()
{

}

GLfloat TextBoxWidget::getMinimumWidth()
{
    return TextWidget::getMinimumWidth();
}

GLfloat TextBoxWidget::getMinimumHeight()
{
    return TextWidget::getMinimumHeight();
}

void TextBoxWidget::draw()
{
    TextWidget::draw();
    glBegin(GL_LINES);
      glVertex2f(textSize, 0);
      glVertex2f(textSize, getMinimumHeight());
    glEnd();
}

void TextBoxWidget::drawBackground()
{
    TextWidget::drawBackground();
    glBegin(GL_LINES);
      glVertex2f(0, 0);
      glVertex2f(getMinimumWidth(), 0);
      glVertex2f(getMinimumWidth(), getMinimumHeight());
      glVertex2f(0, getMinimumHeight());
    glEnd();
}

void TextBoxWidget::onMouseEnter(int x, int y)
{
    TextWidget::onMouseEnter(x, y);
}

void TextBoxWidget::onMouseExit()
{
    TextWidget::onMouseExit();
}

GLboolean TextBoxWidget::onMouseButtonDown(int button, int x, int y)
{
    return TextWidget::onMouseButtonDown(button, x, y);
}

GLboolean TextBoxWidget::onMouseButtonUp(int button, int x, int y)
{
    return TextWidget::onMouseButtonUp(button, x, y);
}

GLboolean TextBoxWidget::onKeyDown(int key)
{
    std::string text = getText();
    int currentPosition = cursorPosition;
    switch(key) {
    case GLUT_KEY_LEFT:
	currentPosition--;
	if(currentPosition < 0) {
	  currentPosition = 0;
	}
	cursorPosition = currentPosition;
        break;
    case GLUT_KEY_RIGHT:
	currentPosition++;
	if(currentPosition > text.length()) {
	  currentPosition = text.length();
	}
	cursorPosition = currentPosition;
        break;
    case 8:
	if(currentPosition > 0) {
	  text.erase(currentPosition-1, 1);
	}
        break;
    case 127:
	if(currentPosition < text.length()) {
	  text.erase(currentPosition, 1);
	}
        break;
    default:
	text+=key;
        break;
    }
    textSize = glutBitmapLength(getFont(), (const unsigned char*) text.c_str());
    setText ( text );
    return true;
}

GLboolean TextBoxWidget::onKeyUp(int key)
{
    return true;
}

void TextBoxWidget::onFocus()
{
    Widget::onFocus();
}

void TextBoxWidget::onBlur()
{
    Widget::onBlur();
}

