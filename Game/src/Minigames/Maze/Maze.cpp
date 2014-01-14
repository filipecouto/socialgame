/*
 * Maze - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#include "Maze.h"
#include <stdlib.h>
#include <cstdio>

Maze::Maze(const int width, const int height) : width(width), height(height) {
	matrix = new bool*[width];

	for (int x = 0; x < width; x++) {
		matrix[x] = new bool[height];

		for (int y = 0; y < height; y++)
			matrix[x][y] = true;
	}
}

void Maze::getNeighbours(Cell cell, Maze::Cell * neighbours, int & count) {
	count = 0;
	Cell test;

	test = {cell.x - 2, cell.y};

	if (hasWall(test)) neighbours[count++] = test;

	test = {cell.x + 2, cell.y};

	if (hasWall(test)) neighbours[count++] = test;

	test = {cell.x, cell.y - 2};

	if (hasWall(test)) neighbours[count++] = test;

	test = {cell.x, cell.y + 2};

	if (hasWall(test)) neighbours[count++] = test;
}

bool Maze::hasWall(Maze::Cell cell) {
	if (cell.x < 0 || cell.y < 0) return false;

	if (cell.x + 1 >= width || cell.y + 1 >= height) return false;

	return matrix[cell.x][cell.y];
}

void Maze::generate() {
	std::vector<Cell> cells;
	Cell nc, c = {(rand() % (width / 2)) * 2 + 1, (rand() % (height / 2)) * 2 + 1};
	matrix[c.x][c.y] = false;
	cells.push_back(c);

	int random;

	Cell * neighbours = new Cell[4];
	int neighbourCount;
	bool startFound, endFound;

	int size;

	while ((size = cells.size()) != 0) {
		random = rand() % size;
		c = cells[random];
		getNeighbours(c, neighbours, neighbourCount);

		if (neighbourCount != 0) {
			random = rand() % neighbourCount;
			nc = neighbours[random];

			if (nc.x < c.x) matrix[nc.x + 1][nc.y] = false;
			else if (nc.x > c.x) matrix[nc.x - 1][nc.y] = false;
			else if (nc.y < c.y) matrix[nc.x][nc.y + 1] = false;
			else if (nc.y > c.y) matrix[nc.x][nc.y - 1] = false;

			matrix[nc.x][nc.y] = false;

			cells.push_back(nc);
		} else {
			cells.erase(cells.begin() + random);
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			printf(matrix[x][y] ? "█" : " ");
		}

		printf("\n");
	}

	int depth = 1;

	start = { -1, -1};

	// looks for a start
	while (start.x == -1 && depth < width / 2) start = findFreePosition(0, depth++);

	depth = 1;

	end = { -1, -1};

	// looks for an end
	while (end.x == -1 && depth < width / 2) end = findFreePosition(rand() % 3 + 1, depth++);

	printf("Start (%d,%d) = %d\nEnd (%d,%d) = %d\n", start.x, start.y, matrix[start.x][start.y], end.x, end.y, matrix[end.x][end.y]);
	startD[0] = start.x;
	startD[1] = start.y;

}


Maze::Cell Maze::findFreePosition(int corner, int depth) {
	Cell found = { -1, -1};

	if (corner == 0) {
		for (int y = 0; y < depth && y < height; y++) {
			for (int x = 0; x < depth && x < width; x++) {
				if (!matrix[x][y]) {
					found.x = x;
					found.y = y;
					return found;
				}
			}
		}
	} else if (corner == 1) {
		for (int y = 0; y < depth && y < height; y++) {
			for (int x = 0; x < depth && x < width; x++) {
				if (!matrix[x][height - 1 - y]) {
					found.x = x;
					found.y = height - 1 - y;
					return found;
				}
			}
		}
	} else if (corner == 2) {
		for (int y = 0; y < depth && y < height; y++) {
			for (int x = 0; x < depth && x < width; x++) {
				if (!matrix[width - 1 - x][height - 1 - y]) {
					found.x = width - 1 - x;
					found.y = height - 1 - y;
					return found;
				}
			}
		}
	} else if (corner == 3) {
		for (int y = 0; y < depth && y < height; y++) {
			for (int x = 0; x < depth && x < width; x++) {
				if (!matrix[width - 1 - x][y]) {
					found.x = width - 1 - x;
					found.y = y;
					return found;
				}
			}
		}
	}

	return found;
}

int Maze::getWidth() {
	return width;
}

int Maze::getHeight() {
	return height;
}

bool Maze::getValue(int width, int height) {
	return matrix[width][height];
}

Maze::~Maze() {
	for (int i = 0; i < width; i++) delete matrix[i];

	delete matrix;
}

int * Maze::getEnd() {
	int * ret = new int[2];
	ret[0] = end.x;
	ret[1] = end.y;
	return ret;
}

int * Maze::getStart() {
	int * ret = new int[2];
	ret[0] = start.x;
	ret[1] = start.y;
	return ret;
}

bool Maze::isEnd(int x, int y) {
	return x == end.x && y == end.y;
}

void Maze::addStart(double x, double y) {
	startD[0] += x;
	startD[1] += y;
}

void Maze::setStart(double x, double y) {
	startD[0] = x;
	startD[1] = y;
}

int ** Maze::getSolution() {
	CentralServerMaze * server = new CentralServerMaze();
	vector<int> dimensions;
	dimensions.push_back(width);
	dimensions.push_back(height);
	vector<int> vectorStart;
	vectorStart.push_back(start.x);
	vectorStart.push_back(start.y);
	vector<int> vectorEnd;
	vectorEnd.push_back(end.x);
	vectorEnd.push_back(end.y);
	
	server->calculatePath(vectorStart, vectorEnd, matrix, dimensions);
	return 0;
}
