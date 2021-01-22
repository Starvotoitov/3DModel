#include "polygonalface.h"

void PolygonalFace::addPolygonVertex(const PolygonVertex &newVertex)
{
	polygonVertexList.push_back(newVertex);
}

std::vector<PolygonVertex> PolygonalFace::getPolygonVertexList() const
{
	return polygonVertexList;
}

bool PolygonalFace::isVisible() const
{
	return _isVisible;
}

void PolygonalFace::setVisibility(bool visibility)
{
	_isVisible = visibility;
}
