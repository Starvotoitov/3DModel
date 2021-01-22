#ifndef VERTEXNORMAL_H
#define VERTEXNORMAL_H

#include <QVector3D>

class VertexNormal
{
public:
	VertexNormal() = default;
	VertexNormal(float i, float j, float k);
	QVector3D toVector() const;
	void fromVector(const QVector3D& vector);

	VertexNormal& operator*=(QMatrix4x4& matrix);

private:
	float i;
	float j;
	float k;
};

#endif // VERTEXNORMAL_H
