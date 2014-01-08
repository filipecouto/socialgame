#ifndef GUI_H
#define GUI_H

#include "WidgetContainer.h"
#include "IWidgetEventsListener.h"
#include "Dialog.h"

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
		virtual int getWidth();
		virtual int getHeigth();
		
		void setEventsListener(IWidgetEventsListener * listener);
		virtual void onWidgetClicked(Widget * clicked);
		virtual void onDialogResult(Dialog * dialog, int buttonId);
		
		Dialog * showMessage(std::string message);
		Dialog * showMessage(std::string id, std::string message);
		Dialog * showYesNoCancelMessage(std::string id, std::string message);
		Dialog * showYesNoCancelMessage(std::string id, std::string message, std::string yes, std::string no, std::string cancel);

	private:
		int _width, _height;
		
		IWidgetEventsListener * _listener;
		
		Dialog * _dialog = NULL;
};

#endif // GUI_H
