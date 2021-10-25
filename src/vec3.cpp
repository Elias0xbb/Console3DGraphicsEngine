#ifndef VEC3
#define VEC3
#include "vec3.h"

Vec3::Vec3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vec3::length() const
{
	return ( std::sqrt(x*x + y*y + z*z) );
}

double Vec3::dist(const Vec3 &v) const
{
	return Vec3(x-v.x, y-v.y, z-v.z).length();
}

Vec3 Vec3::operator +(const Vec3 &v) const
{
	return Vec3(x+v.x, y+v.y, z+v.z);
}
void Vec3::operator +=(const Vec3 &v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
}

Vec3 Vec3::operator -(const Vec3 &v) const
{
	return Vec3(x-v.x, y-v.y, z-v.z);
}
void Vec3::operator -=(const Vec3 &v)
{
	x-=v.x;
	y-=v.y;
	z-=v.z;
}

Vec3 Vec3::operator *(double scalar) const
{
	return Vec3(x*scalar, y*scalar, z*scalar);
}
void Vec3::operator *=(double scalar)
{
	x*=scalar;
	y*=scalar;
	z*=scalar;
}

double Vec3::operator *(const Vec3 &v) const
{
	return (x*v.x + y*v.y + z*v.z);
}

Vec3 Vec3::operator %(const Vec3 &v) const
{
	return Vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}
void Vec3::operator %=(const Vec3 &v)
{
	*this = *this % v;
}

void Vec3::print() const
{
	std::cout << '(' << x << '|' << y << '|' << z << ')';
}

#endif
