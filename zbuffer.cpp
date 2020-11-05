#include "zbuffer.h"
#include <algorithm>

ZBuffer::ZBuffer(int width, int height):
	zBuffer(width * height, std::numeric_limits<float>::min()),
	width(width),
	height(height)
{
}

void ZBuffer::clear()
{
	std::fill(zBuffer.begin(), zBuffer.end(), std::numeric_limits<float>::min());
}

void ZBuffer::resize(int width, int height)
{
	zBuffer.resize(width * height);
	clear();
}

void ZBuffer::setDepth(int x, int y, float newDepth)
{
	zBuffer[x + y * width] = newDepth;
}

bool ZBuffer::isVisible(int x, int y, float depth)
{
	return depth > zBuffer[x + y * width];
}
