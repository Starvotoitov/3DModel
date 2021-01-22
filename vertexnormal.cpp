#include "vertexnormal.h"

VertexNormal::VertexNormal(float i, float j, float k):
	i(i),
	j(j),
	k(k)
{
}

QVector3D VertexNormal::toVector() const
{
	return QVector3D(i, j, k);
}

void VertexNormal::fromVector(const QVector3D &vector)
{
	i = vector.x();
	j = vector.y();
	k = vector.z();
}

VertexNormal& VertexNormal::operator*=(QMatrix4x4 &matrix)
{
	auto vector = toVector();
	vector = matrix * vector;
	fromVector(vector);
	return *this;
}
