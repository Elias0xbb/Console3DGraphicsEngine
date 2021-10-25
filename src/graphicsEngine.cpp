
#ifndef CGFX_ENGINE
#define CGFX_ENGINE
#include "graphicsEngine.h"


Vec3 CGfxEngine::projectPoint(const Vec3 &p)
{
	Vec3 s1 = viewVector % Vec3(1,1,1);
	Vec3 s2 = viewVector % Vec3(3, 1, -1);
	Vec3 viewP = p - viewVector;

	mat3x4.set(0, 0, s1.getX());
	mat3x4.set(1, 0, s1.getY());
	mat3x4.set(2, 0, s1.getZ());

	mat3x4.set(0, 1, s2.getX());
	mat3x4.set(1, 1, s2.getY());
	mat3x4.set(2, 1, s2.getZ());

	mat3x4.set(0, 2, -viewP.getX());
	mat3x4.set(1, 2, -viewP.getY());
	mat3x4.set(2, 2, -viewP.getZ());

	mat3x4.set(0, 3, -viewVector.getX());
	mat3x4.set(1, 3, -viewVector.getY());
	mat3x4.set(2, 3, -viewVector.getZ());

	mat3x4.solve();

	double t = mat3x4.get(2, 3);

	return ( viewerPos + viewP * t );
}


#endif
