#include <cmath>
#include <iostream>
#include "consoleCanvas.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "vec3.h"

int main()
{
	int cols = 80;
	int lines = 24;
	std::uint64_t t;

#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	cols = ts.ts_cols;
	lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
	struct winsize ts;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	cols = ts.ws_col;
	lines = ts.ws_row;
#endif
	
	return 0;
}
