#ifndef MODEL_H
#define MODEL_H

#include "vertex.h"
#include "texturecoordinates.h"
#include "vertexnormal.h"
#include "polygonalface.h"
#include "camera.h"
#include "modelparameters.h"
#include "polygontriangle.h"
#include <vector>
#include <memory>
#include <QImage>

class Model
{
public:
	Model();
	Model(const QString& name, const QString& dir);

	void addVertex(const Vertex &newVertex);
	void addVertex(Vertex &&newVertex);
	void addTextureCoordinates(const TextureCoordinates &newCoordinates);
	void addTextureCoordinates(TextureCoordinates &&newCoordinates);
	void addVertexNormal(const VertexNormal &newVertexNormal);
	void addVertexNormal(VertexNormal &&newVertexNormal);
	void addPolygonalFace(const PolygonalFace &newFace);
	void addPolygonalFace(PolygonalFace &&newFace);

	Model& translate(float x, float y, float z);
	Model& rotateX(float angle);
	Model& rotateY(float angle);
	Model& rotateZ(float angle);
	Model& scale(float x, float y, float z);
	void resetModelMatrix();

	Model& setCamera(const std::shared_ptr<const Camera> camera);
	void resetViewMatrix();

	Model& setOrthographicProjectionMatrix(const Camera& camera);
	Model& setPerspectiveProjectionMatrix(const Camera& camera);
	void resetProjectionMatrix();

	Model& setViewportMatrix(float x, float y);
	void resetViewportMatrix();

	void translateCoordinates();

	void processTriangulation();

	const std::vector<PolygonTriangle>& getPolygons() const;

	const QImage& getNormalMap() const;
	const QImage& getSpecularMap() const;
	const QImage& getAlbedoMap() const;

	std::shared_ptr<const ModelParameters> getParameters() const;

	void resize(float width, float height);

private:
	std::shared_ptr<const Camera> camera;

	std::vector<Vertex> originalVertexList;
	std::vector<TextureCoordinates> textureCoordinatesList;
	std::vector<VertexNormal> vertexNormalList;
	std::vector<PolygonalFace> polygonalFaceList;

	std::vector<PolygonTriangle> triangles;

	QMatrix4x4 translateMatrix;
	QMatrix4x4 rotateXMatrix;
	QMatrix4x4 rotateYMatrix;
	QMatrix4x4 rotateZMatrix;
	QMatrix4x4 scaleMatrix;
	QMatrix4x4 normalizeViewMatrix;
	QMatrix4x4 viewMatrix;
	QMatrix4x4 projectionMatrix;
	QMatrix4x4 viewportMatrix;

	bool isPerspective;

	std::shared_ptr<ModelParameters> parameters;

	float currentWidth;
	float currentHeight;

	QImage normalMap;
	QImage specularMap;
	QImage albedoMap;

	void updateNormalizeViewMatrix();
};

#endif // MODEL_H
