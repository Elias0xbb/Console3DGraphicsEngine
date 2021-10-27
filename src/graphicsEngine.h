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
		viewerPos.setX(double(columns)/2.0);
		viewerPos.setY(double(rows)/2.0);
		viewerPos.setZ(-75.0);

		viewVector.setX(0);
		viewVector.setY(0);
		viewVector.setZ(75.0);
	}

	struct tri
	{
		Vec3 points[3];
	};
private:
	ConsoleCanvas c;
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
