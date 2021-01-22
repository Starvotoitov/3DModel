#ifndef POLYGONTRIANGLE_H
#define POLYGONTRIANGLE_H

#include "texturecoordinates.h"
#include <QVector3D>

struct PolygonTriangle
{
	bool isVisible;
	QVector3D v1;
	QVector3D v2;
	QVector3D v3;
	QVector3D vn1;
	QVector3D vn2;
	QVector3D vn3;
	QVector3D world1;
	QVector3D world2;
	QVector3D world3;
//	TextureCoordinates vt1;
//	TextureCoordinates vt2;
//	TextureCoordinates vt3;
};

#endif // POLYGONTRIANGLE_H
