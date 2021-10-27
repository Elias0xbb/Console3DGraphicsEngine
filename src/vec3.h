#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3
{
public:
	Vec3() = default;
	Vec3(double x, double y, double z);
	Vec3(const Vec3 &v): Vec3(v.x, v.y, v.z) {};

private:
	double x = 0, y = 0, z = 0;
	double w = 0;

public:
	double length() const;

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }
	double getW() const { return w; }

	void setX(double value) { x = value; }
	void setY(double value) { y = value; }
	void setZ(double value) { z = value; }
	void setW(double value) { w = value; }
	void setW(const Vec3 &v1, const Vec3 &v2) { w = v1.dist(v2); }

	double dist(const Vec3 &v) const;

	// Vector addition / subtraction
	Vec3 operator +(const Vec3 &v) const;
	void operator +=(const Vec3 &v);
	Vec3 operator -(const Vec3 &v) const;
	void operator -=(const Vec3 &v);

	// scaling
	Vec3 operator *(double scalar) const;
	void operator *=(double scalar);

	// dot product
	double operator *(const Vec3 &v) const;
	
	// cross product
	Vec3 operator %(const Vec3 &v) const;
	void operator %=(const Vec3 &v);

	// print the vector
	void print() const;
};

#endif
