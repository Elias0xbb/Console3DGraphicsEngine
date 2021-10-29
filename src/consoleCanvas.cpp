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

void ConsoleCanvas::line(int x1, int y1, int x2, int y2, char stroke, double width)
{
	// looking how close each pixel is to the line using complex numbers
	// line = x * ( dx + dyi)
	double dx = x2 - x1;
	double dy = y2 - y1;

	for(int y = 0; y < cols; ++y)
		for(int x = 0; x < rows; ++x)
		{
			double p = (y*dx - x*dy) / (dx*dx + dy*dy);
			if(p < width) set(x, y, stroke);
		}
}

void ConsoleCanvas::triangle(int x1, int y1, int x2, int y2, int x3, int y3, char stroke)
{
	line(x1,y1, x2,y2, stroke, 0.01);
	line(x2,y2, x3,y3, stroke, 0.01);
	line(x1,y1, x3,y3, stroke, 0.01);
}

#endif



