#include "camera.h"

Camera::Camera():
	position(DEFAULT_POSITION),
	viewWidth(DEFAULT_VIEW_WIDTH),
	viewHeight(DEFAULT_VIEW_HEIGHT),
	nearViewingPlane(DEFAULT_NEAR_VIEWING_PLANE),
	farViewingPlane(DEFAULT_FAR_VIEWING_PLANE),
	upwardSpeed(STARTING_VERTICAL_SPEED),
	downwardSpeed(STARTING_VERTICAL_SPEED),
	forwardSpeed(STARTING_HORIZONTAL_SPEED),
	backwardSpeed(STARTING_HORIZONTAL_SPEED),
	speedToLeft(STARTING_HORIZONTAL_SPEED),
	speedToRight(STARTING_HORIZONTAL_SPEED),
	rotationToLeftSpeed(STARTING_ROTATION_SPEED),
	rotationToRightSpeed(STARTING_ROTATION_SPEED)
{
	vectorZ = position - QVector3D(0, 0, 0);
	vectorZ.normalize();

	vectorY = QVector3D(0, 1, 0);

	vectorX = QVector3D::crossProduct(vectorY, vectorZ);
	vectorX.normalize();
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

float Camera::getViewWidth() const
{
	return viewWidth;
}

float Camera::getViewHeight() const
{
	return viewHeight;
}

float Camera::getNearViewingPlane() const
{
	return nearViewingPlane;
}

float Camera::getFarViewingPlane() const
{
	return farViewingPlane;
}

void Camera::changeUpwardMovement()
{
	if (upwardSpeed == STARTING_VERTICAL_SPEED)
	{
		upwardSpeed += DEFAULT_ACCELERATION;
	}
	else
	{
		upwardSpeed -= DEFAULT_ACCELERATION;
	}
}

void Camera::changeDownwardMovement()
{
	if (downwardSpeed == STARTING_VERTICAL_SPEED)
	{
		downwardSpeed += DEFAULT_ACCELERATION;
	}
	else
	{
		downwardSpeed -= DEFAULT_ACCELERATION;
	}
}

void Camera::changeForwardMovement()
{
	if (forwardSpeed == STARTING_HORIZONTAL_SPEED)
	{
		forwardSpeed += DEFAULT_ACCELERATION;
	}
	else
	{
		forwardSpeed -= DEFAULT_ACCELERATION;
	}
}

void Camera::changeBackwardMovement()
{
	if (backwardSpeed == STARTING_HORIZONTAL_SPEED)
	{
		backwardSpeed += DEFAULT_ACCELERATION;
	}
	else
	{
		backwardSpeed -= DEFAULT_ACCELERATION;
	}
}

void Camera::changeMovementToLeft()
{
	if (speedToLeft == STARTING_HORIZONTAL_SPEED)
	{
		speedToLeft += DEFAULT_ACCELERATION;
	}
	else
	{
		speedToLeft -= DEFAULT_ACCELERATION;
	}
}

void Camera::changeMovementToRight()
{
	if (speedToRight == STARTING_HORIZONTAL_SPEED)
	{
		speedToRight += DEFAULT_ACCELERATION;
	}
	else
	{
		speedToRight -= DEFAULT_ACCELERATION;
	}
}

void Camera::changeRotationToLeft()
{
	if (rotationToLeftSpeed == STARTING_ROTATION_SPEED)
	{
		rotationToLeftSpeed += DEFAULT_ROTATION_ACCELERATION;
	}
	else
	{
		rotationToLeftSpeed -= DEFAULT_ROTATION_ACCELERATION;
	}
}

void Camera::changeRotationToRight()
{
	if (rotationToRightSpeed == STARTING_ROTATION_SPEED)
	{
		rotationToRightSpeed += DEFAULT_ROTATION_ACCELERATION;
	}
	else
	{
		rotationToRightSpeed -= DEFAULT_ROTATION_ACCELERATION;
	}
}

void Camera::updateCoordinates()
{
	auto verticaleSpeed = upwardSpeed - downwardSpeed;
	if (verticaleSpeed != 0)
	{
//		auto directionVector = vectorY;
//		directionVector *= verticaleSpeed;
//		vectorY *= verticaleSpeed;
//		vectorX += directionVector;
//		vectorY += directionVector;
//		vectorZ += directionVector;
//		position += directionVector;
//		vectorX.normalize();
//		vectorY.normalize();
//		vectorZ.normalize();
	}
}
