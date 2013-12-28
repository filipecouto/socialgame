#ifndef WINDOW_H
#define WINDOW_H

#include "WidgetContainer.h"

class Window : public WidgetContainer {
	public:
		Window();
		Window(Widget * contents);

		virtual void draw();
		virtual void drawBackground();
		
		virtual GLboolean onMouseButtonDown(int button, int x, int y);
		virtual GLboolean onMouseButtonUp(int button, int x, int y);
		
		void setPadding(GLfloat padding);
		
		void setContent(Widget * content);
		
		virtual GLboolean isAnimating();
		virtual void tick(int delta, int absolute);
		
		virtual void onParentGeometryChange(Widget * widget);
		
		void hide();
		void show();
		
		void avoidOutside();

		virtual ~Window();
		
	protected:
		virtual GLfloat getBiggestMinimumHeight();
		virtual GLfloat getBiggestMinimumWidth();
		
	private:
		Widget * _contents = NULL;
		
		GLfloat _padding;
		
		GLfloat _ct = 0, _tt = 0;
};

#endif // WINDOW_H
