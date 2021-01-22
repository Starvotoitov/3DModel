#include "zbuffer.h"
#include <algorithm>
#include <qdebug.h>

ZBuffer::ZBuffer(int width, int height):
	zBuffer(width * height, std::numeric_limits<float>::max()),
	width(width),
	height(height)
{
}

#include <QDebug>

int i = 0;

void ZBuffer::clear()
{
//	qDebug() << "Clear start";
	i = 0;
	std::fill(zBuffer.begin(), zBuffer.end(), std::numeric_limits<float>::max());
//	qDebug() << "Clear end";
}

void ZBuffer::resize(int width, int height)
{
	auto size = width * height;
	if (size != zBuffer.size())
	{
		zBuffer.resize(width * height);
		this->width = width;
		this->height = height;
	}
	clear();
}
/*
void ZBuffer::setDepth(int x, int y, float newDepth)
{
	_setDepth(x, y, newDepth);
}

void ZBuffer::setDepth(QPoint &point, float newDepth)
{
	setDepth(point.x(), point.y(), newDepth);
}

bool ZBuffer::isVisible(int x, int y, float depth)
{
	return _isVisible(x, y, depth);
}

bool ZBuffer::isVisible(QPoint &point, float depth)
{
	return isVisible(point.x(), point.y(), depth);
}
*/
bool ZBuffer::checkAndSet(int x, int y, float depth)
{
	if (_isVisible(x, y, depth))
	{
		_setDepth(x, y, depth);
		return true;
	}
	return false;
}

void ZBuffer::_setDepth(int x, int y, float newDepth)
{
	zBuffer[x + y * width] = newDepth;
}

bool ZBuffer::_isVisible(int x, int y, float depth)
{
//	if (zBuffer[x + y * width] <= depth)
//		qDebug() << i++ << " " << x << " " << y << " " << zBuffer[x + y * width] << " " << depth;
	return depth < zBuffer[x + y * width];
}
