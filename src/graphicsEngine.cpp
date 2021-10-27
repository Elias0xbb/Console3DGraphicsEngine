
#ifndef CGFX_ENGINE
#define CGFX_ENGINE
#include "graphicsEngine.h"

void CGfxEngine::setup()
{
	c.fill('.');
}

Vec3 CGfxEngine::projectPoint(const Vec3 &p)
{
// 	std::cout << "Point: "; 
	// p.print();
	// std::cout << '\n';

	Vec3 s1 = viewVector % Vec3(1,1,1);
	Vec3 s2 = viewVector % Vec3(3, 1, -1);
	Vec3 viewP = p - viewerPos;

	/*
	std::cout << "s1: ";
	s1.print();
	std::cout << "\ns2: ";
	s2.print();
	std::cout << "yp: ";
	viewP.print();
	std::cout << '\n';
	*/

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

	// mat3x4.print();

	// std::cout << "solving...\n";

	mat3x4.solve();
	// mat3x4.print();

	double t = mat3x4.get(2, 3);

	return ( viewerPos + viewP * t );
}

void CGfxEngine::projectTriangles()
{
	for(auto it = triangles.begin(); it != triangles.end(); ++it)
	{
		tri t;
		for(int i = 0; i < 3; ++i)
		{
			t.points[i] = projectPoint((*it).points[i]);
		}
		projectedTris.push(t);
	}
}

void CGfxEngine::insertTri(tri t)
{
	triangles.push_back(t);
}

void CGfxEngine::render()
{
	projectTriangles();
}

void CGfxEngine::draw()
{
	while(!projectedTris.empty())
	{
		tri t = projectedTris.front();
		c.triangle(
			t.points[0].getX(), t.points[0].getY(), 
			t.points[1].getX(), t.points[1].getY(),
			t.points[2].getX(), t.points[2].getY(),
			'#'
		);
		projectedTris.pop();
	}

	c.draw();
	// clear the canvas
	c.fill(' ');
}

#endif
