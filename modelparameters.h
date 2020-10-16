#ifndef MODELPARAMETERS_H
#define MODELPARAMETERS_H

#include "projectiontype.h"

class ModelParameters
{
public:
	ModelParameters();

	ProjectionType getProjectionType() const;
	float getX() const;
	float getY() const;
	float getZ() const;
	float getRotateAngleX() const;
	float getRotateAngleY() const;
	float getRotateAngleZ() const;
	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;
	QString getName() const;

	void setProjectionType(ProjectionType type);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setRotateAngleX(float angle);
	void setRotateAngleY(float angle);
	void setRotateAngleZ(float angle);
	void setScaleX(float scale);
	void setScaleY(float scale);
	void setScaleZ(float scale);
	void setName(QString name);

private:
	inline static ProjectionType DEFAULT_PROJECTION_TYPE = ProjectionType::Perspective;
	inline static float DEFAULT_X = 0.0;
	inline static float DEFAULT_Y = 0.0;
	inline static float DEFAULT_Z = 0.0;
	inline static float DEFAULT_ROTATE_X_ANGLE = 0.0;
	inline static float DEFAULT_ROTATE_Y_ANGLE = 0.0;
	inline static float DEFAULT_ROTATE_Z_ANGLE = 0.0;
	inline static float DEFAULT_SCALE_X = 1.0;
	inline static float DEFAULT_SCALE_Y = 1.0;
	inline static float DEFAULT_SCALE_Z = 1.0;
	inline static QString DEFAULT_NAME = "DEFAULT";

	ProjectionType projectionType;
	float x;
	float y;
	float z;
	float rotateAngleX;
	float rotateAngleY;
	float rotateAngleZ;
	float scaleX;
	float scaleY;
	float scaleZ;
	QString name;
};

#endif // MODELPARAMETERS_H
