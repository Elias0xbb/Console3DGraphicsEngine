#ifndef CONSOLE_CANVAS_H
#define CONSOLE_CANVAS_H

#include <iostream>
#include <cmath>

class ConsoleCanvas
{
public:
	ConsoleCanvas() = delete;
	ConsoleCanvas(int rows, int cols);
	~ConsoleCanvas();
private:
	int rows;
	int cols;

	char **canvas;
public:
	// fills the canvas with a specified character
	void fill(char c);
	// sets a character of the canvas
	void set(int x, int y, char c);
	// draws a circle
	void circle(int cx, int cy, double radius, char filling);
	// draws a line between two points
	void line(int x1, int y1, int x2, int y2, char stroke, double width);
	// draws a triangle
	void triangle(int x1, int y1, int x2, int y2, int x3, int y3, char stroke);
	// writes the canvas to the terminal window
	void draw() const;
};

#endif
