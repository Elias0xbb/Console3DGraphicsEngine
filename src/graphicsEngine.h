#ifndef GFX_ENGINE_H
#define GFX_ENGINE_H

#include "consoleCanvas.h"
#include "vec3.h"
#include "../lib/GaussMatrix.h"
#include <vector>
#include <queue>

class CGfxEngine
{
public:
	CGfxEngine() = delete;
	CGfxEngine(int rows, int columns): c(rows, columns), mat3x4(3, 4)
	{
		viewerPos = Vec3(0,0,-1);
		viewVector = Vec3(0,0,1);

		this->rows = rows;
		this->cols = columns;
	}

	struct tri
	{
		tri() = default;
		tri(Vec3 p0, Vec3 p1, Vec3 p2)
		{
			points[0] = p0;
			points[1] = p1;
			points[2] = p2;
		}
		Vec3 points[3];
	};

private:
	ConsoleCanvas c;
	int rows, cols;
	double xScalar = 0.5, yScalar = 1;
	// position of the viewer
	Vec3 viewerPos;
	// view direction, distance to canvas
	Vec3 viewVector;
	GaussMatrix mat3x4;

	// projects a point on to the field of view
	Vec3 projectPoint(const Vec3 &p);
	std::vector<tri> triangles;
	std::queue<tri> projectedTris;

	void projectTriangles();

public:
	void insertTri(tri t);
	void deleteTris()
	{
		triangles.clear();
	}
	void render();
	void draw();
	void setup();
};

#endif
