#ifndef POLYGONVERTEX_H
#define POLYGONVERTEX_H

//#include "vertex.h"
//#include "texturecoordinates.h"
//#include "vertexnormal.h"

struct PolygonVertex
{
	int vertexIndex;
	int textureCoordinatesIndex;
	int vertexNormalIndex;

//	Vertex *vertex;
//	TextureCoordinates *textureCoordinates;
//	VertexNormal *vertexNormal;

	inline static int NO_INDEX_VALUE = 0;
};

#endif // POLYGONVERTEX_H
