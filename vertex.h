#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

class Vertex
{
public:
	Vertex() = default;
	Vertex(double x, double y, double z, double w = DEFAULT_VALUE);

	QVector4D toVector4D() const;
	QVector3D toVector3D() const;
	void fromVector(QVector4D& vector);
	int getX() const;
	int getY() const;
	int getZ() const;

	void normalizeW();

	Vertex& operator*=(QMatrix4x4& matrix);

	inline static double DEFAULT_VALUE = 1;

private:
	double x;
	double y;
	double z;
	double w;
};

#endif // VERTEX_H
