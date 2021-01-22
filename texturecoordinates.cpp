#include "texturecoordinates.h"

TextureCoordinates::TextureCoordinates(double u, double v, double w):
	_u(u),
	_v(v),
	_w(w)
{
}

TextureCoordinates& operator*(TextureCoordinates& coord, float factor)
{
	coord._u *= factor;
	coord._v *= factor;
	coord._w *= factor;
	return coord;
}

TextureCoordinates& operator*(float factor, TextureCoordinates& coord)
{
	coord._u *= factor;
	coord._v *= factor;
	coord._w *= factor;
	return coord;
}

TextureCoordinates& operator/(TextureCoordinates &coord, float divider)
{
	coord._u /= divider;
	coord._v /= divider;
	coord._w /= divider;
	return coord;
}

TextureCoordinates& operator+(TextureCoordinates& coord, const TextureCoordinates& addedCoord)
{
	coord._u += addedCoord._u;
	coord._v += addedCoord._v;
	coord._w += addedCoord._w;
	return coord;
}

TextureCoordinates& operator-(TextureCoordinates& coord, const TextureCoordinates& addedCoord)
{
	coord._u -= addedCoord._u;
	coord._v -= addedCoord._v;
	coord._w -= addedCoord._w;
	return coord;
}
