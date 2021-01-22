#ifndef POLYGONALFACE_H
#define POLYGONALFACE_H

#include "polygonvertex.h"
#include <vector>
#include <QVector3D>

class PolygonalFace
{
public:
	PolygonalFace() = default;
	void addPolygonVertex(const PolygonVertex &newVertex);
	std::vector<PolygonVertex> getPolygonVertexList() const;
	bool isVisible() const;
	void setVisibility(bool visibility);
private:
	bool _isVisible;
	std::vector<PolygonVertex> polygonVertexList;
};

#endif // POLYGONALFACE_H
