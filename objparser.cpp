#include "objparser.h"
#include <regex>
#include <QTextStream>
#include <QRegularExpression>
#include <QFileInfo>
#include <QDir>
#include <qdebug.h>

int ObjParser::line = 1;

ObjParser::ObjParser():
	file()
{
	typeMap[QString(VERTEX)] = ObjParser::parseVertex;
	typeMap[QString(TEXTURE_COORDINATES)] = ObjParser::parseTextureCoordinates;
	typeMap[QString(VERTEX_NORMAL)] = ObjParser::parseVertexNormal;
	typeMap[QString(POLYGONAL_FACE)] = ObjParser::parsePolygonalFace;
}

ObjParser::ObjParser(QString fileName):
	file(fileName)
{
	typeMap[QString(VERTEX)] = ObjParser::parseVertex;
	typeMap[QString(TEXTURE_COORDINATES)] = ObjParser::parseTextureCoordinates;
	typeMap[QString(VERTEX_NORMAL)] = ObjParser::parseVertexNormal;
	typeMap[QString(POLYGONAL_FACE)] = ObjParser::parsePolygonalFace;
}

void ObjParser::setObjFile(QString fileName)
{
	file.setFileName(fileName);
}

void ObjParser::parse()
{
	qDebug() << "Parse start";
	if (!file.open(QFile::ReadOnly))
	{
		// ADD EXCEPTION
		throw;
	}

	QFileInfo fileInfo(file);
	model = std::make_shared<Model>(file.fileName(), fileInfo.dir().absolutePath());
	QTextStream stream(&file);
	QRegularExpression regEx("[^\\s]+");
	while (!stream.atEnd())
	{
		QString currentLine = stream.readLine();
		QRegularExpressionMatchIterator matchs = regEx.globalMatch(currentLine);
		if (matchs.hasNext())
		{
			QString tokenType = matchs.next().captured();
			try
			{
				typeMap.at(tokenType)(matchs, model);
			}
			catch (std::out_of_range &ex)
			{
				// // // // // // // // // // // // // // // // // // // // // // // // // // // //
			}
		}
	}
	qDebug() << "Parse end";
}

std::shared_ptr<Model> ObjParser::getModel() const
{
	return model;
}

void ObjParser::parseVertex(QRegularExpressionMatchIterator &matchs, std::shared_ptr<Model> model)
{
	double x = matchs.next().captured().toDouble();
	double y = matchs.next().captured().toDouble();
	double z = matchs.next().captured().toDouble();
	double w = Vertex::DEFAULT_VALUE;
	if (matchs.hasNext())
	{
		 w = matchs.next().captured().toDouble();
	}
	model->addVertex(Vertex(x, y, z, w));
}

void ObjParser::parseTextureCoordinates(QRegularExpressionMatchIterator &matchs, std::shared_ptr<Model> model)
{
	double u = matchs.next().captured().toDouble();
	double v = TextureCoordinates::DEFAULT_VALUE;
	double w = TextureCoordinates::DEFAULT_VALUE;
	if (matchs.hasNext())
	{
		v = matchs.next().captured().toDouble();
		if (matchs.hasNext())
		{
			w = matchs.next().captured().toDouble();
		}
	}
	model->addTextureCoordinates(TextureCoordinates(u, v, w));
}

void ObjParser::parseVertexNormal(QRegularExpressionMatchIterator &matchs, std::shared_ptr<Model> model)
{
	double i = matchs.next().captured().toDouble();
	double j = matchs.next().captured().toDouble();
	double k = matchs.next().captured().toDouble();
	model->addVertexNormal(VertexNormal(i, j, k));
}

void ObjParser::parsePolygonalFace(QRegularExpressionMatchIterator &matchs, std::shared_ptr<Model> model)
{
	PolygonalFace newFace;
	QRegularExpression indexLineExpression("(?<v>[\\d]+)(\\/(?<vt>[\\d]+))?(\\/?\\/(?<vn>[\\d]+))?");
	while (matchs.hasNext())
	{
		QString indexLine = matchs.next().captured();
		QRegularExpressionMatch indexMatch = indexLineExpression.match(indexLine);

		newFace.addPolygonVertex(PolygonVertex{
									 indexMatch.captured(VERTEX).toInt(),
									 indexMatch.captured(TEXTURE_COORDINATES).toInt(),
									 indexMatch.captured(VERTEX_NORMAL).toInt()
								 });
	}
	model->addPolygonalFace(newFace);
}
