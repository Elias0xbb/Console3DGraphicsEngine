#ifndef CONSOLE_CANVAS
#define CONSOLE_CANVAS
#include "consoleCanvas.h"

ConsoleCanvas::ConsoleCanvas(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	canvas = new char *[cols];
	for(int i = 0; i < cols; ++i) canvas[i] = new char[rows];
}

ConsoleCanvas::~ConsoleCanvas()
{
	for(int i = 0; i < cols; ++i) delete canvas[i];
	delete[] canvas;
}

void ConsoleCanvas::fill(char c)
{
	for(int x = 0; x < cols; ++x)
		for(int y = 0; y < rows; ++y)
			canvas[x][y] = c;
}

void ConsoleCanvas::set(int x, int y, char c)
{
	canvas[x][y] = c;
}

void ConsoleCanvas::draw() const
{
	for(int row = 0; row < rows; ++row)
	{
		std::cout << "\e[" << row << ";1H";
		for(int col = 0; col < cols; ++col) std::cout << canvas[col][row];
	}
	// std::cout << "rows: " << rows << ", cols: " << cols << '\n';
}

void ConsoleCanvas::circle(int cx, int cy, double radius, char filling)
{
	for(int x = 0; x < cols; ++x)
	{
		for(int y = 0; y < rows; ++y)
		{
			double dist = std::sqrt( double( (x-cx)*(x-cx) + (y-cy)*(y-cy) ) );
			if(dist < radius) canvas[x][y] = filling;
		}
	}
}

void ConsoleCanvas::line(int x1, int y1, int x2, int y2, char stroke)
{
	if(x1 > x2)
	{
		int x1tmp = x1, y1tmp = y1;
		x1 = x2;
		y1 = y2;
		x2 = x1tmp;
		y2 = y1tmp;
	}

	double m = double(y2 - y1) / double(x2 - x1);
	double b = y1 - m*x1;

	// draw the line
	for(int x = x1; x <= x2; ++x)
	{
		double y = m*x+b;
		int py = (int)y;
		// TODO: remove error checking here
		if(x >= 0 && x < cols && y >= 0 && y < rows)
		set(x, py, stroke);
	}
}

void ConsoleCanvas::triangle(int x1, int y1, int x2, int y2, int x3, int y3, char stroke)
{
	line(x1,y1, x2,y2, stroke);
	line(x2,y2, x3,y3, stroke);
	line(x1,y1, x3,y3, stroke);
}

#endif



