#include "model.h"
#include "QMatrix4x4"
#include "QVector3D"
#include <cmath>
#include <QtMath>

Model::Model():
	translateMatrix(IDENTITY_MATRIX),
	rotateXMatrix(IDENTITY_MATRIX),
	rotateYMatrix(IDENTITY_MATRIX),
	rotateZMatrix(IDENTITY_MATRIX),
	scaleMatrix(IDENTITY_MATRIX),
	viewMatrix(IDENTITY_MATRIX),
	projectionMatrix(IDENTITY_MATRIX),
	viewportMatrix(IDENTITY_MATRIX),
	isPerspective(false),
	parameters(std::make_shared<ModelParameters>())
{
}

Model::Model(QString name):
	translateMatrix(IDENTITY_MATRIX),
	rotateXMatrix(IDENTITY_MATRIX),
	rotateYMatrix(IDENTITY_MATRIX),
	rotateZMatrix(IDENTITY_MATRIX),
	scaleMatrix(IDENTITY_MATRIX),
	viewMatrix(IDENTITY_MATRIX),
	projectionMatrix(IDENTITY_MATRIX),
	viewportMatrix(IDENTITY_MATRIX),
	isPerspective(false),
	parameters(std::make_shared<ModelParameters>())
{
	parameters->setName(name);
}

void Model::addVertex(const Vertex &newVertex)
{
	originalVertexList.push_back(newVertex);
}

void Model::addVertex(Vertex &&newVertex)
{
	originalVertexList.push_back(std::forward<Vertex>(newVertex));
}

void Model::addVertexNormal(const VertexNormal &newVertexNormal)
{
	vertexNormalList.push_back(newVertexNormal);
}

void Model::addVertexNormal(VertexNormal &&newVertexNormal)
{
	vertexNormalList.push_back(std::forward<VertexNormal>(newVertexNormal));
}

void Model::addPolygonalFace(const PolygonalFace &newFace)
{
	polygonalFaceList.push_back(newFace);
}

void Model::addPolygonalFace(PolygonalFace &&newFace)
{
	polygonalFaceList.push_back(std::forward<PolygonalFace>(newFace));
}

void Model::addTextureCoordinates(const TextureCoordinates &newCoordinates)
{
	textureCoordinatesList.push_back(newCoordinates);
}

void Model::addTextureCoordinates(TextureCoordinates &&newCoordinates)
{
	textureCoordinatesList.push_back(std::forward<TextureCoordinates>(newCoordinates));
}

Model& Model::translate(float x, float y, float z)
{
	parameters->setX(x);
	parameters->setY(y);
	parameters->setZ(z);
	translateMatrix = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return *this;
}

Model& Model::rotateX(float angle)
{
	parameters->setRotateAngleX(angle);
	angle *= M_PI / 180;
	rotateXMatrix = {
		1,		 0,				   0,         0,
		0, std::cos(angle), -std::sin(angle), 0,
		0, std::sin(angle),  std::cos(angle), 0,
		0,       0,                0,         1
	};
	return *this;
}

Model& Model::rotateY(float angle)
{
	parameters->setRotateAngleY(angle);
	angle *= M_PI / 180;
	rotateYMatrix = {
		std::cos(angle), 0, std::sin(angle), 0,
			  0,         1,       0,         0,
	   -std::sin(angle), 0, std::cos(angle), 0,
			  0,         0,       0,         1
	};
	return *this;
}

Model& Model::rotateZ(float angle)
{
	parameters->setRotateAngleZ(angle);
	angle *= M_PI / 180;
	rotateZMatrix = {
		std::cos(angle), -std::sin(angle), 0, 0,
		std::sin(angle),  std::cos(angle), 0, 0,
			  0,                0,         1, 0,
			  0,                0,         0, 1
	};
	return *this;
}

Model& Model::scale(float x, float y, float z)
{
	parameters->setScaleX(x);
	parameters->setScaleY(y);
	parameters->setScaleZ(z);
	scaleMatrix = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
	return *this;
}

void Model::resetModelMatrix()
{
	translateMatrix = IDENTITY_MATRIX;
	rotateXMatrix = IDENTITY_MATRIX;
	rotateYMatrix = IDENTITY_MATRIX;
	rotateZMatrix = IDENTITY_MATRIX;
	scaleMatrix = IDENTITY_MATRIX;
}

Model& Model::changeCamera(const Camera &camera)
{
	const QVector3D &xAxis = camera.getVectorX();
	const QVector3D &yAxis = camera.getVectorY();
	const QVector3D &zAxis = camera.getVectorZ();
	const QVector3D &cameraPosition = camera.getPosition();

	QMatrix4x4 coordinateSystemMatrix = {
		xAxis.x(), xAxis.y(), xAxis.z(), 0,
		yAxis.x(), yAxis.y(), yAxis.z(), 0,
		zAxis.x(), zAxis.y(), zAxis.z(), 0,
			0,         0,         0,     1
	};

	QMatrix4x4 cameraPositionMatrix = {
		1, 0, 0, -cameraPosition.x(),
		0, 1, 0, -cameraPosition.y(),
		0, 0, 1, -cameraPosition.z(),
		0, 0, 0,          1
	};

	viewMatrix = coordinateSystemMatrix * cameraPositionMatrix;

	return *this;
}

void Model::resetViewMatrix()
{
	viewMatrix = IDENTITY_MATRIX;
}

Model& Model::setOrthographicProjectionMatrix(const Camera &camera)
{
	isPerspective = false;
	parameters->setProjectionType(ProjectionType::Orthographic);

	float width = camera.getViewWidth();
	float height = camera.getViewHeight();
	float near = camera.getNearViewingPlane();
	float far = camera.getFarViewingPlane();

	projectionMatrix = {
		2 / width,      0,            0,                 0,
			0,     2 / height,        0,                 0,
			0,          0,     1 / (near - far), near / (near - far),
			0,          0,            0,                 1
	};
	return *this;
}

Model& Model::setPerspectiveProjectionMatrix(const Camera &camera)
{
	isPerspective = true;
	parameters->setProjectionType(ProjectionType::Perspective);

	float width = camera.getViewWidth();
	float height = camera.getViewHeight();
	float near = camera.getNearViewingPlane();
	float far = camera.getFarViewingPlane();

	projectionMatrix = {
		2 * near / width,            0,                       0,                      0,
			  0,             2 * near / height,               0,                      0,
			  0,                     0,              far / (near - far), (near * far) / (near - far),
			  0,                     0,                      -1,                      0
	};
	return *this;
}

void Model::resetProjectionMatrix()
{
	projectionMatrix = IDENTITY_MATRIX;
}

Model& Model::setViewportMatrix(float x, float y, float width, float height)
{
	viewportMatrix = {
		width / 2,      0,      0, x + width / 2,
			0,     -height / 2, 0, y + height / 2,
			0,          0,      1,       0,
			0,          0,      0,       1
	};
	return *this;
}

void Model::resetViewportMatrix()
{
	viewportMatrix = IDENTITY_MATRIX;
}

void Model::translateCoordinates()
{
	QMatrix4x4 resultTranslateMatrix =
			projectionMatrix * viewMatrix * translateMatrix *
			rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

	reset();
	for (auto& currentVertex : transformedVertexList)
	{
		currentVertex *= resultTranslateMatrix;
		if (isPerspective)
		{
			currentVertex.normalizeW();
		}
		currentVertex *= viewportMatrix;
	}
}

void Model::reset()
{
	transformedVertexList = originalVertexList;
}

std::vector<Vertex> Model::getVertexes() const
{
	return transformedVertexList;
}

std::vector<PolygonalFace> Model::getPolygons() const
{
	return polygonalFaceList;
}

std::shared_ptr<const ModelParameters> Model::getParameters() const
{
	return parameters;
}