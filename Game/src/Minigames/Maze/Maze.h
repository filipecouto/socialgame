/*
 * Maze - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#ifndef MAZE_H
#define MAZE_H
#include <vector>

class Maze {
	public:
		Maze(const int width, const int height);

		void generate();

		~Maze();

	private:
		int width, height;
		bool ** matrix;

		typedef struct Cell {
			int x;
			int y;
		} Cell;
		void getNeighbours(Maze::Cell cell, Maze::Cell * neighbours, int & count);
		bool hasWall(Cell cell);
};

#endif // MAZE_H
