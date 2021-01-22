#ifndef TEXTURECOORDINATES_H
#define TEXTURECOORDINATES_H


class TextureCoordinates
{
	friend TextureCoordinates& operator*(TextureCoordinates& coord, float factor);
	friend TextureCoordinates& operator*(float factor, TextureCoordinates& coord);
	friend TextureCoordinates& operator/(TextureCoordinates&, float divider);
	friend TextureCoordinates& operator+(TextureCoordinates& coord, const TextureCoordinates& addedCoord);
	friend TextureCoordinates& operator-(TextureCoordinates& coord, const TextureCoordinates& addedCoord);

public:
	TextureCoordinates() = default;
	TextureCoordinates(double u, double v = DEFAULT_VALUE, double w = DEFAULT_VALUE);

	float u() const;
	float v() const;
	float w() const;

	inline static double DEFAULT_VALUE = 0;
private:
	float _u;
	float _v;
	float _w;
};

TextureCoordinates& operator*(TextureCoordinates& coord, float factor);
TextureCoordinates& operator*(float factor, TextureCoordinates& coord);
TextureCoordinates& operator/(TextureCoordinates&, float divider);
TextureCoordinates& operator+(TextureCoordinates& coord, const TextureCoordinates& addedCoord);
TextureCoordinates& operator-(TextureCoordinates& coord, const TextureCoordinates& addedCoord);

#endif // TEXTURECOORDINATES_H
