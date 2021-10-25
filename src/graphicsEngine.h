#include "consoleCanvas.h"
#include "vec3.h"
#include "../lib/GaussMatrix.h"

class CGfxEngine
{
public:
	CGfxEngine() = delete;
	CGfxEngine(int rows, int columns): c(rows, columns), mat3x4(3, 4) {}

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

	tri projectedTriangles[10];

public:
	tri triangles[10];
	
	void draw() const;
};
