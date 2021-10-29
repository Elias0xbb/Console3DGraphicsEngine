#include <cmath>
#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "vec3.h"
#include "graphicsEngine.h"
#include "matrix.h"

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

	std::uint64_t time = 0;

	CGfxEngine gfx(lines, cols);
	gfx.setup();


	// 2D rotation matrix
	const double angle = 0.0001;
	Matrix rotY(3, 3);
	rotY.set(0,0, std::cos(angle)); rotY.set(0,1, 0); rotY.set(0,2, std::sin(angle));
	rotY.set(1,0, 0); rotY.set(1,1, 1); rotY.set(1,2, 0);
	rotY.set(2,0, -std::sin(angle)); rotY.set(2,1, 0); rotY.set(2,2, std::cos(angle));

	Matrix rotX(3, 3);
	rotX.set(0,0, 1); rotX.set(0,1, 0); rotX.set(0,2, 0);
	rotX.set(1,0, 0); rotX.set(1,1, std::cos(angle)); rotX.set(1,2, -std::sin(angle));
	rotX.set(2,0, 0); rotX.set(2,1, std::sin(angle)); rotX.set(2,2, std::cos(angle));

	CGfxEngine::tri tris[12] = {
		CGfxEngine::tri(Vec3(-1,-1,1), Vec3(-1,1,1), Vec3(1,-1,1)),
		CGfxEngine::tri(Vec3(1,-1,1), Vec3(-1,1,1), Vec3(1,1,1)),

		CGfxEngine::tri(Vec3(1,-1,2), Vec3(1,-1,1), Vec3(1,1,1)),
		CGfxEngine::tri(Vec3(1,-1,2), Vec3(1,1,1), Vec3(1,1,2)),

		CGfxEngine::tri(Vec3(-1,-1,2), Vec3(-1,-1,1), Vec3(1,-1,1)),
		CGfxEngine::tri(Vec3(1,-1,1), Vec3(1,-1,2), Vec3(-1,-1,2)),

		CGfxEngine::tri(Vec3(1,-1,2), Vec3(-1,-1,2), Vec3(1,1,2)),
		CGfxEngine::tri(Vec3(1,1,2), Vec3(-1,-1,2), Vec3(-1,1,2)),

		CGfxEngine::tri(Vec3(-1,-1,2), Vec3(-1,-1,1), Vec3(-1,1,2)),
		CGfxEngine::tri(Vec3(-1,-1,1), Vec3(-1,1,1), Vec3(-1,1,2)),

		CGfxEngine::tri(Vec3(1,1,2), Vec3(-1,1,1), Vec3(1,1,1)),
		CGfxEngine::tri(Vec3(1,1,2), Vec3(-1,1,2), Vec3(-1,1,1))
	};

	while(1)
	{
 		gfx.deleteTris();
		
		// get the middle of the triangle
		Vec3 axis(tris[0].points[1]);

		for(int tr = 0; tr < 12; ++tr)
		{
			for(int i = 0; i < 3; ++i)
			{
				Vec3 pr = rotX * (rotY * (tris[tr].points[i] - axis)) + axis;
				tris[tr].points[i] = pr;
 				tris[tr].points[i].setZ(double(tris[tr].points[i].getZ()) + 0.0001);
			}
			gfx.insertTri(tris[tr]);
		}


		// render all points
		gfx.render();

		// draw the buffer to the canvas
		gfx.draw();

		++time;
	}
	
	return 0;
}
