#ifndef LINEARCONTAINER_H
#define LINEARCONTAINER_H

#include <../../home/filipe/crosswebsocialgame/Game/src/GUI/WidgetContainer.h>


class LinearContainer : public WidgetContainer {

	public:
		LinearContainer();
		virtual void addWidget(Widget * add_object);
		virtual void removeWidget(Widget * remove_object);
		virtual ~LinearContainer();
		virtual void onParentGeometryChange(Widget * widget);
	private:
		virtual void revalidate();
		
		GLboolean orientation; // true - vertical, false - horizontal
		GLfloat spacing = 1;
};

#endif // LINEARCONTAINER_H
