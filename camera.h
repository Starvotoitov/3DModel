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

	const QVector3D& getRealPosition() const;
	float getAngleX() const;
	float getAngleY() const;
	float getAngleZ() const;

	constexpr float getViewWidth() const;
	constexpr float getViewHeight() const;
	constexpr float getNearViewingPlane() const;
	constexpr float getFarViewingPlane() const;

	void changeXPosition(float changeVal);
	void changeYPosition(float changeVal);
	void changeZPosition(float changeVal);

	void changeXAngle(float changeVal);
	void changeYAngle(float changeVal);
	void changeZAngle(float changeVal);

private:
	QVector3D vectorX;
	QVector3D vectorY;
	QVector3D vectorZ;
	QVector3D position;

	QVector3D realPosition;
	float angleX;
	float angleY;
	float angleZ;

	inline static QVector3D DEFAULT_POSITION = QVector3D(0, 0, 0);
	inline static QVector3D DEFAULT_REAL_POSITION = QVector3D(0, 0, 2);
	constexpr inline static float DEFAULT_VIEW_WIDTH = 1;
	constexpr inline static float DEFAULT_VIEW_HEIGHT = 1;
	constexpr inline static float DEFAULT_NEAR_VIEWING_PLANE = 1.25;
	constexpr inline static float DEFAULT_FAR_VIEWING_PLANE = 10;
	inline static float DEFAULT_ANGLE = 0;
	inline static int X_INDEX = 0;
	inline static int Y_INDEX = 1;
	inline static int Z_INDEX = 2;
};

constexpr float Camera::getViewWidth() const
{
	return DEFAULT_VIEW_WIDTH;
}

constexpr float Camera::getViewHeight() const
{
	return DEFAULT_VIEW_HEIGHT;
}

constexpr float Camera::getNearViewingPlane() const
{
	return DEFAULT_NEAR_VIEWING_PLANE;
}

constexpr float Camera::getFarViewingPlane() const
{
	return DEFAULT_FAR_VIEWING_PLANE;
}

#endif // CAMERA_H
