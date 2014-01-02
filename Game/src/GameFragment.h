/**
 * GameFragment - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

/**
 * A GameFragment is an interface that represents a part of the game that has its
 * own drawing and input processing methods.
 * GameController and mini-game instances are GameFragments.
 */
class GameFragment {
	public:
		virtual void draw() = 0;

		virtual void tick(int delta, int current) { }

		virtual void onKeyDown(int key, int special) { }
		virtual void onKeyUp(int key, int special) { }

		virtual void onMouseMove(int x, int y) { }
		virtual void onMouseButton(int button, int state, int x, int y) { }


		// these methods may be useful to handle mouse events

		virtual void setViewportDimensions(int width, int height) {
			vpWidth = width;
			vpHeight = height;
		}

		int getViewportWidth() {
			return vpWidth;
		}

		int getViewportHeight() {
			return vpHeight;
		}

	private:
		int vpWidth, vpHeight;
};

#endif
