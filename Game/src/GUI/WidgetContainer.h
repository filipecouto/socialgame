#ifndef WIDGETCONTAINER_H
#define WIDGETCONTAINER_H

#include <string>
#include <vector>

#include "Widget.h"
#include "IWidgetContainer.h"

class WidgetContainer : public Widget, public IWidgetContainer {
	public:
		WidgetContainer ( );

		virtual void addWidget ( Widget * add_object );
		virtual void removeWidget ( Widget * remove_object );

		virtual void draw();
		virtual void onMouseMove ( int x, int y );

		virtual GLboolean onMouseButtonDown ( int button, int x, int y );
		virtual GLboolean onMouseButtonUp ( int button, int x, int y );

		virtual GLboolean onKeyDown ( int key );
		virtual GLboolean onKeyUp ( int key );

		virtual void requestFocus ( Widget * from );
		virtual void onFocus();
		virtual void onBlur();

		virtual ~WidgetContainer ( );

	private:
		Widget * getWidget ( int x, int y );

		Widget * _widgetHover;

	protected:
		Widget * _focused;
		
		std::vector<Widget*> m_widgetVector;
};

#endif // WIDGETCONTAINER_H
