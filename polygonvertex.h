#ifndef POLYGONVERTEX_H
#define POLYGONVERTEX_H


struct PolygonVertex
{
	int vertexIndex;
	int textureCoordinatesIndex;
	int vertexNormalIndex;

	inline static int NO_INDEX_VALUE = 0;
};

#endif // POLYGONVERTEX_H
