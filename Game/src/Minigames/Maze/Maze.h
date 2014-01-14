/*
 * Maze - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#ifndef MAZE_H
#define MAZE_H
#include "CentralServerMaze.h"
#include <vector>

class Maze {
	public:
		Maze(const int width, const int height);

		void generate();
		
		bool getValue(int width, int height);
		
		int getHeight();
		int getWidth();
		int* getStart();
		int* getEnd();
		void addStart(double x, double y);
		void setStart(double x, double y);
		vector<int*> getSolution(int, int);
		
		bool isEnd(int x, int y);
		
		~Maze();
		
	private:
		int width, height;
		bool ** matrix;
		
		

		typedef struct Cell {
			int x;
			int y;
		} Cell;
		
		double startD[2];
		Cell start, end;
		void getNeighbours(Maze::Cell cell, Maze::Cell * neighbours, int & count);
		bool hasWall(Maze::Cell cell);
		Cell findFreePosition(int corner, int depth);
		
};

#endif // MAZE_H
