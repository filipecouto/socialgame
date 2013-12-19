/**
 * IGraphic - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IGRAPHIC_H
#define IGRAPHIC_H

/**
 * This interface represents something visual that will represent things
 * in the network such as people and connections.
 */
class IGraphic {
	public:
		virtual void draw() { }
};

#endif