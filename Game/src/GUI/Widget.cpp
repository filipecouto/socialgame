#include "Widget.h"

Widget::Widget ( ) : Widget ( 0, 0 ) {}

Widget::Widget ( GLfloat xPos, GLfloat yPos ) : x ( xPos ), y ( yPos ), visible ( true ), hover ( false ) {}

Widget::~Widget ( ) { }
