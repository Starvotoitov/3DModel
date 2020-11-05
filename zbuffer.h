#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <vector>
#include <limits>

class ZBuffer
{
public:
	ZBuffer() = default;
	ZBuffer(int width, int height);

	void clear();
	void resize(int width, int height);
	void setDepth(int x, int y, float newDepth);
	bool isVisible(int x, int y, float depth);

private:
	std::vector<float> zBuffer;
	int width;
	int height;
};

#endif // ZBUFFER_H
