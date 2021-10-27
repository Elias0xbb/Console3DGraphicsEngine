#ifndef MATRIX
#define MATRIX

#include "matrix.h"

Matrix::Matrix(int nRows, int nCols)
{
	this->nRows = nRows;
	this->nCols = nCols;

	matrix = new double*[nRows];
	for(int i = 0; i < nRows; ++i) matrix[i] = new double[nCols];
}
Matrix::~Matrix()
{
	for(int i = 0; i < nRows; ++i) delete[] matrix[i];
	delete[] matrix;
}

Vec3 Matrix::operator *(const Vec3 &v) const
{
	assert(nRows == 3);
	assert(nCols == 3);

	return Vec3(
		matrix[0][0] * v.getX() + matrix[0][1] * v.getY() + matrix[0][2] * v.getZ(),
		matrix[1][0] * v.getX() + matrix[1][1] * v.getY() + matrix[1][2] * v.getZ(),
		matrix[2][0] * v.getX() + matrix[2][1] * v.getY() + matrix[2][2] * v.getZ()
	);
}

void Matrix::set(double **matrix)
{
	for(int r = 0; r < nRows; ++r)
		for(int c = 0; c < nCols; ++c)
			this->matrix[r][c] = matrix[r][c];
}

#endif
