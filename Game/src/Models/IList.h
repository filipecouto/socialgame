/**
 * IList - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef ILIST_H
#define ILIST_H

template<class T>
class IList {
	public:
		virtual T operator[](int index) = 0;
		
		virtual bool contains(T item) = 0;
		
		virtual int size() = 0;

		virtual ~IList() { }
};

#endif
