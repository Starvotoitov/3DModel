#include "matrixarithmetic.h"
#include <QtMath>

namespace MatrixArithmetic
{

float toRadian(float angle)
{
	return angle * M_PI / 180;
}

QMatrix4x4 identityMatrix()
{
	return QMatrix4x4 {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

QMatrix4x4 translateMatrix(float x, float y, float z)
{
	return QMatrix4x4 {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
}

QMatrix4x4 rotateXMatrix(float angle)
{
	return QMatrix4x4 {
		1,		 0,				   0,         0,
		0, std::cos(angle), -std::sin(angle), 0,
		0, std::sin(angle),  std::cos(angle), 0,
		0,       0,                0,         1
	};
}

QMatrix4x4 rotateYMatrix(float angle)
{
	return QMatrix4x4 {
		std::cos(angle), 0, std::sin(angle), 0,
			  0,         1,       0,         0,
	   -std::sin(angle), 0, std::cos(angle), 0,
			  0,         0,       0,         1
	};
}

QMatrix4x4 rotateZMatrix(float angle)
{
	return QMatrix4x4 {
		std::cos(angle), -std::sin(angle), 0, 0,
		std::sin(angle),  std::cos(angle), 0, 0,
			  0,                0,         1, 0,
			  0,                0,         0, 1
	};
}

QMatrix4x4 scaleMatrix(float x, float y, float z)
{
	return QMatrix4x4 {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
}

QMatrix4x4 viewMatrix(const QVector3D &xAxis, const QVector3D &yAxis,
					  const QVector3D &zAxis, const QVector3D &cameraPosition)
{
	QMatrix4x4 coordinateSystemMatrix = {
		xAxis.x(), xAxis.y(), xAxis.z(), 0,
		yAxis.x(), yAxis.y(), yAxis.z(), 0,
		zAxis.x(), zAxis.y(), zAxis.z(), 0,
			0,         0,         0,     1
	};

	QMatrix4x4 cameraPositionMatrix = {
		1, 0, 0, -cameraPosition.x(),
		0, 1, 0, -cameraPosition.y(),
		0, 0, 1, -cameraPosition.z(),
		0, 0, 0,          1
	};

	return coordinateSystemMatrix * cameraPositionMatrix;
}

QMatrix4x4 orthographicMatrix(float width, float height,
							  float near, float far)
{
	return QMatrix4x4 {
		2 / width,      0,            0,                 0,
			0,     2 / height,        0,                 0,
			0,          0,     1 / (near - far), near / (near - far),
			0,          0,            0,                 1
	};
}

QMatrix4x4 perspectiveMatrix(float width, float height,
							 float near, float far)
{
	return QMatrix4x4 {
		2 * near / width,            0,                       0,                      0,
			  0,             2 * near / height,               0,                      0,
			  0,                     0,              far / (near - far), (near * far) / (near - far),
			  0,                     0,                      -1,                      0
	};
}

QMatrix4x4 viewportMatrix(float x, float y,
						  float width, float height)
{
	return QMatrix4x4 {
		width / 2,      0,      0, x + width / 2,
			0,     -height / 2, 0, y + height / 2,
			0,          0,      1,       0,
			0,          0,      0,       1
	};
}

}
