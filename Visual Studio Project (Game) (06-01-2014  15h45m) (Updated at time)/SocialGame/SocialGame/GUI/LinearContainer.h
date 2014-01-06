#ifndef LINEARCONTAINER_H
#define LINEARCONTAINER_H

#include "WidgetContainer.h"


class LinearContainer : public WidgetContainer {

	public:
		LinearContainer();

		virtual void addWidget(Widget * add_object);
		virtual void removeWidget(Widget * remove_object);
		virtual void onParentGeometryChange(Widget * widget);
		
		void setVertical();
		void setHorizontal();
		
		void setSpacing(GLfloat spacing);
		GLfloat getSpacing();

		virtual ~LinearContainer();
	private:
		void revalidate();
		
		GLboolean orientation = false; // true - vertical, false - horizontal
		GLfloat _spacing = 1;
};

#endif // LINEARCONTAINER_H
