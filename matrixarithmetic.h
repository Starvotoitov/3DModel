#ifndef MATRIXARITHMETIC_H
#define MATRIXARITHMETIC_H

#include <QMatrix4x4>
#include <QVector3D>

namespace MatrixArithmetic
{

float toRadian(float angle);

QMatrix4x4 identityMatrix();

QMatrix4x4 translateMatrix(float x, float y, float z);

QMatrix4x4 rotateXMatrix(float angle);
QMatrix4x4 rotateYMatrix(float angle);
QMatrix4x4 rotateZMatrix(float angle);

QMatrix4x4 scaleMatrix(float x, float y, float z);

QMatrix4x4 viewMatrix(const QVector3D &xAxis, const QVector3D &yAxis,
					  const QVector3D &zAxis, const QVector3D &cameraPosition);

QMatrix4x4 orthographicMatrix(float width, float height,
							  float near, float far);
QMatrix4x4 perspectiveMatrix(float width, float height,
							 float near, float far);

QMatrix4x4 viewportMatrix(float x, float y,
						  float width, float height);

}

#endif // MATRIXARITHMETIC_H
