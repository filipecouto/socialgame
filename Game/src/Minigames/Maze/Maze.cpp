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
	Cell nc, c = {rand() % width, rand() % height};
	matrix[c.x][c.y] = false;
	cells.push_back(c);

	int random;

	Cell * neighbours = new Cell[4];
	int neighbourCount;

	int size;
	bool startFound = false, endFound = false;

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

	// finds the start
	for(int i=0; i < width; i++) { // j = 0
		if(!matrix[i][0]) {
			startFound = true;
			start = {i, 0};
			break;
		}
		
	}
	for(int i=0; i < width; i++) { // j = height
		if(startFound) break;
		if(!matrix[i][height]) {
			startFound = true;
			start = {i, height};
		}
	}
	for(int i=0; i < height; i++) { // j = 0
		if(startFound) break;
		if(!matrix[0][i]) {
			startFound = true;
			start = {0, i};
		}
	}
	for(int i=0; i < height; i++) { // j = width
		if(startFound) break;
		if(!matrix[width][i]) {
			startFound = true;
			start = {width, i};
		}
	}
	
	// finds the end
	int minWidth = (int)width/2; // 50% of the maze
	int minHeight = (int)height/2; // 50% of the maze
	int startRangeX , endRangeX;
	int startRangeY , endRangeY;
	startRangeX = (start.x >= minWidth) ? start.x - minWidth : start.x + minWidth;
	endRangeX = (start.x >= minWidth) ? 0 : width;
	startRangeY = (start.y >= minHeight) ? start.y - minHeight : start.y + minHeight;
	endRangeY = (start.y >= minHeight) ? 0 : height;
	int endX, endY;
	Cell test;
	while(true) {
		
		endX = rand() % (endRangeX - startRangeX) + startRangeX;
		endY = rand() % (endRangeY - startRangeY) + startRangeY;
		test.x = endX-1;
		test.y = endY-1;
		if(!hasWall(test)) break; 
	} 
	end = {endX, endY};
	
	printf("Start (%d,%d) = %d\nEnd (%d,%d) = %d\n", start.x, start.y, matrix[start.x][start.y], end.x, end.y, matrix[end.x][end.y]);
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




