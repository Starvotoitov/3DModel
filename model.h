#ifndef MODEL_H
#define MODEL_H

#include "vertex.h"
#include "texturecoordinates.h"
#include "vertexnormal.h"
#include "polygonalface.h"
#include "camera.h"
#include "modelparameters.h"
#include <vector>
#include <memory>

class Model
{
public:
	Model();
	Model(QString name);

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

	Model& setViewportMatrix(float x, float y, float width, float height);
	void resetViewportMatrix();

	void translateCoordinates();
	void reset();

	std::vector<Vertex> getVertexes() const;
	std::vector<PolygonalFace> getPolygons() const;

	std::shared_ptr<const ModelParameters> getParameters() const;

private:
	std::shared_ptr<const Camera> camera;

	std::vector<Vertex> originalVertexList;
	std::vector<TextureCoordinates> textureCoordinatesList;
	std::vector<VertexNormal> vertexNormalList;
	std::vector<PolygonalFace> polygonalFaceList;

	std::vector<Vertex> transformedVertexList;

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

	float curWidth;
	float curHeight;

	inline static QMatrix4x4 IDENTITY_MATRIX = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	static QMatrix4x4 createTranslateMatrix(float x, float y, float z);
	static QMatrix4x4 createRotateXMatrix(float angle);
	static QMatrix4x4 createRotateYMatrix(float angle);
	static QMatrix4x4 createRotateZMatrix(float angle);
	static float toRadian(float angle);

	void updateNormalizeViewMatrix();
};

#endif // MODEL_H
