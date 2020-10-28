#include "camera.h"

Camera::Camera():
	position(DEFAULT_POSITION),
	realPosition(DEFAULT_REAL_POSITION),
	angleX(DEFAULT_ANGLE),
	angleY(DEFAULT_ANGLE),
	angleZ(DEFAULT_ANGLE)
{	
	vectorX = QVector3D(1, 0, 0);
	vectorY = QVector3D(0, 1, 0);
	vectorZ = QVector3D(0, 0, 1);

//	vectorZ = position - QVector3D(0, 0, 0);
//	vectorZ.normalize();

//	vectorY = QVector3D(0, 1, 0);

//	vectorX = QVector3D::crossProduct(vectorY, vectorZ);
//	vectorX.normalize();
}

const QVector3D& Camera::getVectorX() const
{
	return vectorX;
}

const QVector3D& Camera::getVectorY() const
{
	return vectorY;
}

const QVector3D& Camera::getVectorZ() const
{
	return vectorZ;
}

const QVector3D& Camera::getPosition() const
{
	return position;
}

const QVector3D& Camera::getRealPosition() const
{
	return realPosition;
}

float Camera::getAngleX() const
{
	return angleX;
}

float Camera::getAngleY() const
{
	return angleY;
}

float Camera::getAngleZ() const
{
	return angleZ;
}

void Camera::changeXPosition(float changeVal)
{
	realPosition[X_INDEX] += changeVal;
}

void Camera::changeYPosition(float changeVal)
{
	realPosition[Y_INDEX] += changeVal;
}

void Camera::changeZPosition(float changeVal)
{
	realPosition[Z_INDEX] += changeVal;
}

void Camera::changeXAngle(float changeVal)
{
	angleX += changeVal;
}

void Camera::changeYAngle(float changeVal)
{
	angleY += changeVal;
}

void Camera::changeZAngle(float changeVal)
{
	angleZ += changeVal;
}
