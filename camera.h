#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>

class Camera
{
public:
	Camera();

	const QVector3D& getVectorX() const;
	const QVector3D& getVectorY() const;
	const QVector3D& getVectorZ() const;
	const QVector3D& getPosition() const;
	float getViewWidth() const;
	float getViewHeight() const;
	float getNearViewingPlane() const;
	float getFarViewingPlane() const;

	void changeUpwardMovement();
	void changeDownwardMovement();
	void changeForwardMovement();
	void changeBackwardMovement();
	void changeMovementToLeft();
	void changeMovementToRight();
	void changeRotationToLeft();
	void changeRotationToRight();

	void updateCoordinates();

private:
	QVector3D vectorX;
	QVector3D vectorY;
	QVector3D vectorZ;
	QVector3D position;
	float viewWidth;
	float viewHeight;
	float nearViewingPlane;
	float farViewingPlane;
	float upwardSpeed;
	float downwardSpeed;
	float forwardSpeed;
	float backwardSpeed;
	float speedToLeft;
	float speedToRight;
	float rotationToLeftSpeed;
	float rotationToRightSpeed;

	inline static QVector3D DEFAULT_POSITION = QVector3D(0, 0, 1);
	inline static float DEFAULT_VIEW_WIDTH = 2;
	inline static float DEFAULT_VIEW_HEIGHT = 2;
	inline static float DEFAULT_NEAR_VIEWING_PLANE = 1;
	inline static float DEFAULT_FAR_VIEWING_PLANE = 10;
	inline static float STARTING_VERTICAL_SPEED = 0;
	inline static float STARTING_HORIZONTAL_SPEED = 0;
	inline static float STARTING_ROTATION_SPEED = 0;
	inline static float DEFAULT_ACCELERATION = 0.3;
	inline static float DEFAULT_ROTATION_ACCELERATION = 1;

};

#endif // CAMERA_H
