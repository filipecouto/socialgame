#ifndef GUI_H
#define GUI_H

#include "WidgetContainer.h"

class Gui : public WidgetContainer {
	public:
		/**
		 * Empty Constructor
		 */
		Gui ( );

		/**
		 * Empty Destructor
		 */
		virtual ~Gui ( );

		/**
		 * Draws all GUI widgets onto the screen
		 */
		void drawGui();

		virtual void onMouseEnter ( int x, int y );
		virtual void onMouseMove ( int x, int y );
		virtual GLboolean onMouseButtonDown ( int button, int x, int y );
		virtual GLboolean onMouseButtonUp ( int button, int x, int y );

		virtual void requestFocus ( Widget * from );

		void setDimensions ( int width, int height );

	private:
		int _width, _height;
};

#endif // GUI_H
