#include "vertex.h"

Vertex::Vertex(double x, double y, double z, double w):
	x(x),
	y(y),
	z(z),
	w(w)
{
}

QVector4D Vertex::toVector() const
{
	return QVector4D(x, y, z, w);
}

void Vertex::fromVector(QVector4D &vector)
{
	x = vector.x();
	y = vector.y();
	z = vector.z();
	w = vector.w();
}

int Vertex::getX() const
{
	return x;
}

int Vertex::getY() const
{
	return y;
}

int Vertex::getZ() const
{
	return z;
}

void Vertex::normalizeW()
{
	x /= w;
	y /= w;
	z /= w;
	w = 1;
}

Vertex& Vertex::operator*=(QMatrix4x4 &matrix)
{
	QVector4D vector(x, y, z, w);
	vector = matrix * vector;
	fromVector(vector);
	return *this;
}
