#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <vector>
#include <limits>
#include <QPoint>

class ZBuffer
{
public:
	ZBuffer() = default;
	ZBuffer(int width, int height);

	void clear();
	void resize(int width, int height);
//	void setDepth(int x, int y, float newDepth);
//	void setDepth(QPoint& point, float newDepth);
//	bool isVisible(int x, int y, float depth);
//	bool isVisible(QPoint& point, float depth);
	bool checkAndSet(int x, int y, float depth);

private:
	void _setDepth(int x, int y, float newDepth);
	bool _isVisible(int x, int y, float depth);

	std::vector<float> zBuffer;
	int width;
	int height;
};

#endif // ZBUFFER_H
