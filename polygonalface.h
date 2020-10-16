#ifndef POLYGONALFACE_H
#define POLYGONALFACE_H

#include "polygonvertex.h"
#include <vector>

class PolygonalFace
{
public:
	PolygonalFace() = default;
	void addPolygonVertex(const PolygonVertex &newVertex);
	std::vector<PolygonVertex> getPolygonVertexList() const;

private:
	std::vector<PolygonVertex> polygonVertexList;
};

#endif // POLYGONALFACE_H
