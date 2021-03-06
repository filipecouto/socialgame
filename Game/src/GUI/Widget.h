#ifndef WIDGET_H
#define WIDGET_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#include <vector>
#endif

#ifdef _WIN32
#include <GL/glaux.h>
#endif

#include <string>
#include "IWidgetContainer.h"

/**
  * class Widget
  * This class represents an empty Widget.
  */
class Widget {
	public:
		Widget ( );
		Widget ( GLfloat xPos, GLfloat yPos );

		virtual ~Widget ( );

		/**
		 * Draws this Widget on the screen.
		 */
		virtual void draw ( );

		/**
		 * Draws the background of this widget in the screen.
		 */
		virtual void drawBackground ( );

		virtual GLfloat getMinimumWidth() {
			return w;
		}

		virtual GLfloat getMinimumHeight() {
			return h;
		}

		virtual void onMouseEnter ( int x, int y ) {
			hover = true;
		}

		virtual void onMouseMove ( int x, int y ) {

		}

		virtual void onMouseExit() {
			hover = false;
		}

		virtual GLboolean onMouseButtonDown ( int button, int x, int y ) {
			requestFocus();
			return true;
		}

		virtual GLboolean onMouseButtonUp ( int button, int x, int y ) {
			return false;
		}

		virtual GLboolean onKeyDown ( int key, int special ) {
			return false;
		}

		virtual GLboolean onKeyUp ( int key, int special ) {
			return false;
		}

		virtual void onFocus() {
			focused = true;
		}

		virtual void onBlur() {
			focused = false;
		}

		// The X position of the Widget in the screen
		GLfloat x;
		// The Y position of the Widget in the screen
		GLfloat y;

		// The width of the Widget in the screen
		GLfloat w;
		// The height of the Widget in the screen
		GLfloat h;

		// Whether the Widget is visible or not, making it invisible mutes any event notification
		GLboolean visible;

		void setParent ( IWidgetContainer * parent ) {
			_parent = parent;
		}

		IWidgetContainer * getParent() {
			return _parent;
		}
		
		virtual GLboolean isAnimating() {
			return false;
		}
		
		virtual void tick(int delta, int absolute) { }

		void requestFocus();
		void notifyGeometryChange();
		void performClick();

	protected:
		GLboolean hover = GL_FALSE, focused = GL_FALSE;
		IWidgetContainer * _parent = NULL;
};

#endif // WIDGET_H
