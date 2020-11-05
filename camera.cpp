#include "camera.h"
#include "matrixarithmetic.h"

Camera::Camera():
	position(DEFAULT_POSITION),
	realPosition(DEFAULT_REAL_POSITION),
	angleX(DEFAULT_ANGLE),
	angleY(DEFAULT_ANGLE),
	angleZ(DEFAULT_ANGLE),
	vectorX(VECTOR_X),
	vectorY(VECTOR_Y),
	vectorZ(VECTOR_Z)
{
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
	QVector3D directionVector =
		MatrixArithmetic::rotateYMatrix(MatrixArithmetic::toRadian(angleY)) *
		MatrixArithmetic::rotateZMatrix(MatrixArithmetic::toRadian(angleZ)) *
		VECTOR_X *
		changeVal;

	realPosition[X_INDEX] += directionVector.x();
	realPosition[Y_INDEX] += directionVector.y();
	realPosition[Z_INDEX] += directionVector.z();
}

void Camera::changeYPosition(float changeVal)
{
	QVector3D directionVector =
		MatrixArithmetic::rotateXMatrix(MatrixArithmetic::toRadian(angleX)) *
		MatrixArithmetic::rotateZMatrix(MatrixArithmetic::toRadian(angleZ)) *
		VECTOR_Y *
		changeVal;

	realPosition[X_INDEX] += directionVector.x();
	realPosition[Y_INDEX] += directionVector.y();
	realPosition[Z_INDEX] += directionVector.z();
}

void Camera::changeZPosition(float changeVal)
{
	QVector3D directionVector =
		MatrixArithmetic::rotateXMatrix(MatrixArithmetic::toRadian(angleX)) *
		MatrixArithmetic::rotateYMatrix(MatrixArithmetic::toRadian(angleY)) *
		VECTOR_Z *
		changeVal;

	realPosition[X_INDEX] += directionVector.x();
	realPosition[Y_INDEX] += directionVector.y();
	realPosition[Z_INDEX] += directionVector.z();
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
