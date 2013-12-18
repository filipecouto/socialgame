#ifndef TEXTBOXWIDGET_H
#define TEXTBOXWIDGET_H

#include <../../home/filipe/crosswebsocialgame/Game/src/GUI/TextWidget.h>


class TextBoxWidget : public TextWidget
{

public:
    TextBoxWidget();
    TextBoxWidget(std::string text, GLfloat xPos, GLfloat yPos);
    TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, void* font, GLfloat xPos, GLfloat yPos);
    TextBoxWidget(std::string text, void* font, GLfloat xPos, GLfloat yPos);
    TextBoxWidget(std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat xPos, GLfloat yPos);
    virtual ~TextBoxWidget();
    virtual GLfloat getMinimumWidth();
    virtual GLfloat getMinimumHeight();
    virtual void draw();
    virtual void drawBackground();
    virtual void onMouseEnter(int x, int y);
    virtual void onMouseExit();
    virtual GLboolean onMouseButtonDown(int button, int x, int y);
    virtual GLboolean onMouseButtonUp(int button, int x, int y);
    virtual GLboolean onKeyDown(int key);
    virtual GLboolean onKeyUp(int key);
    virtual void onFocus();
    virtual void onBlur();
    
private:
    int cursorPosition = 0;
    GLfloat textSize = 0.0f;
};

#endif // TEXTBOXWIDGET_H
