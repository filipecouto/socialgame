#ifndef TEXTBOXWIDGET_H
#define TEXTBOXWIDGET_H

#include "TextWidget.h"

class TextBoxWidget : public TextWidget
{
public:
    TextBoxWidget();
    TextBoxWidget(std::string text, GLfloat xPos, GLfloat yPos);
    TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, void* font, GLfloat xPos, GLfloat yPos);
    TextBoxWidget(std::string text, void* font, GLfloat xPos, GLfloat yPos);
    TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat xPos, GLfloat yPos);
	
    virtual GLfloat getMinimumWidth();
    virtual GLfloat getMinimumHeight();
	
    virtual void draw();
    virtual void drawBackground();
	
    virtual void onMouseEnter(int x, int y);
    virtual void onMouseExit();
	
    virtual GLboolean onMouseButtonDown(int button, int x, int y);
    virtual GLboolean onMouseButtonUp(int button, int x, int y);
    virtual GLboolean onKeyDown(int key, int special);
    virtual GLboolean onKeyUp(int key, int special);
	
    virtual void onFocus();
    virtual void onBlur();
	
	virtual GLboolean isAnimating();
	virtual void tick(int delta, int absolute);
	
    virtual ~TextBoxWidget();

protected:
	virtual void updateDimensions();

private:
    int cursorPosition;
	GLfloat _borderWidth;
    GLfloat cursorVisualPosition;
	long pastTime = 0;
	bool showCursor;
	
	void updateCursorPosition();
};

#endif // TEXTBOXWIDGET_H
