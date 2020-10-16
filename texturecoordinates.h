#ifndef TEXTURECOORDINATES_H
#define TEXTURECOORDINATES_H


class TextureCoordinates
{
public:
	TextureCoordinates() = default;
	TextureCoordinates(double u, double v = DEFAULT_VALUE, double w = DEFAULT_VALUE);

	inline static double DEFAULT_VALUE = 0;
private:
	double u;
	double v;
	double w;
};

#endif // TEXTURECOORDINATES_H
