#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "model.h"
#include <memory>
#include <map>
#include <QFile>
#include <QRegularExpressionMatchIterator>

class ObjParser
{
public:
	ObjParser();
	ObjParser(QString fileName);
	void setObjFile(QString fileName);
	void parse();
	std::shared_ptr<Model> getModel() const;
private:
	using parseFunction = void (*)(QRegularExpressionMatchIterator&, std::shared_ptr<Model>);

	std::shared_ptr<Model> model;
	std::map<QString, parseFunction> typeMap;
	QFile file;

	inline static const char* VERTEX = "v";
	inline static const char* TEXTURE_COORDINATES = "vt";
	inline static const char* VERTEX_NORMAL = "vn";
	inline static const char* POLYGONAL_FACE = "f";

	static int line;
	static void parsePolygonalFace(QRegularExpressionMatchIterator& matchs, std::shared_ptr<Model> model);
	static void parseTextureCoordinates(QRegularExpressionMatchIterator& matchs, std::shared_ptr<Model> model);
	static void parseVertex(QRegularExpressionMatchIterator& matchs, std::shared_ptr<Model> model);
	static void parseVertexNormal(QRegularExpressionMatchIterator& matchs, std::shared_ptr<Model> model);
};

#endif // OBJPARSER_H
