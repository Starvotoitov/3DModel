#include "modelparameters.h"

ModelParameters::ModelParameters():
	projectionType(DEFAULT_PROJECTION_TYPE),
	x(DEFAULT_X),
	y(DEFAULT_Y),
	z(DEFAULT_Z),
	rotateAngleX(DEFAULT_ROTATE_X_ANGLE),
	rotateAngleY(DEFAULT_ROTATE_Y_ANGLE),
	rotateAngleZ(DEFAULT_ROTATE_Z_ANGLE),
	scaleX(DEFAULT_SCALE_X),
	scaleY(DEFAULT_SCALE_Y),
	scaleZ(DEFAULT_SCALE_Z),
	name(DEFAULT_NAME)
{
}

ProjectionType ModelParameters::getProjectionType() const
{
	return projectionType;
}

float ModelParameters::getX() const
{
	return x;
}

float ModelParameters::getY() const
{
	return y;
}

float ModelParameters::getZ() const
{
	return z;
}

float ModelParameters::getRotateAngleX() const
{
	return rotateAngleX;
}

float ModelParameters::getRotateAngleY() const
{
	return rotateAngleY;
}

float ModelParameters::getRotateAngleZ() const
{
	return rotateAngleZ;
}

float ModelParameters::getScaleX() const
{
	return scaleX;
}

float ModelParameters::getScaleY() const
{
	return scaleY;
}

float ModelParameters::getScaleZ() const
{
	return scaleZ;
}

QString ModelParameters::getName() const
{
	return name;
}

void ModelParameters::setProjectionType(ProjectionType type)
{
	projectionType = type;
}

void ModelParameters::setX(float x)
{
	this->x = x;
}

void ModelParameters::setY(float y)
{
	this->y = y;
}

void ModelParameters::setZ(float z)
{
	this->z = z;
}

void ModelParameters::setRotateAngleX(float angle)
{
	rotateAngleX = angle;
}

void ModelParameters::setRotateAngleY(float angle)
{
	rotateAngleY = angle;
}

void ModelParameters::setRotateAngleZ(float angle)
{
	rotateAngleZ = angle;
}

void ModelParameters::setScaleX(float scale)
{
	scaleX = scale;
}

void ModelParameters::setScaleY(float scale)
{
	scaleY = scale;
}

void ModelParameters::setScaleZ(float scale)
{
	scaleZ = scale;
}

void ModelParameters::setName(QString name)
{
	this->name = name;
}
