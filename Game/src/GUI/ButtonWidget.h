#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include "TextWidget.h"
#include "IWidgetContainer.h"

#include <string>
#include <stdio.h>

class ButtonWidget : public Widget, public IWidgetContainer {
	public:
		ButtonWidget ( );
		ButtonWidget ( Widget * containingWidget );
		ButtonWidget ( Widget * containingWidget, GLfloat xPos, GLfloat yPos );
		// 		ButtonWidget ( std::string text, GLfloat xPos, GLfloat yPos );
		// 		ButtonWidget ( std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, void* font, GLfloat xPos, GLfloat yPos );
		// 		ButtonWidget ( std::string text, void * font, GLfloat xPos, GLfloat yPos );
		// 		ButtonWidget ( std::string text, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat xPos, GLfloat yPos );

		virtual ~ButtonWidget ( );

		virtual void drawBackground ( );
		virtual void draw();

		virtual GLboolean onMouseButtonDown ( int button, int x, int y );
		virtual GLboolean onMouseButtonUp ( int button, int x, int y );

		void setContainingWidget ( Widget* widget );

		Widget * getContainingWidget();

		virtual void onParentGeometryChange ( Widget* widget );

	private:
		GLfloat _minW, _minH;
		GLfloat _borderWidth;
		Widget * _widget;

		GLboolean _clicked;

		GLfloat _hoverAnim;
		GLfloat _clickAnim;
		GLfloat _focusAnim;

};

#endif // BUTTONWIDGET_H
