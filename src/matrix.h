#ifndef MATRIX_H
#define MATRIX_H

#include "vec3.h"
#include <assert.h>

class Matrix
{
public:
	Matrix() = delete;
	Matrix(int nRows, int nCols);
	~Matrix();

private:
	double **matrix;
	int nRows, nCols;

public:
	double get(int row, int col) const { return matrix[row][col]; }
	void set(int row, int col, double value) { matrix[row][col] = value; }
	void set(double **matrix);

	Vec3 operator *(const Vec3 &v) const;
};


#endif
