#include "model.h"
#include "matrixarithmetic.h"
#include <cmath>
#include <QtMath>

Model::Model():
	translateMatrix(MatrixArithmetic::identityMatrix()),
	rotateXMatrix(MatrixArithmetic::identityMatrix()),
	rotateYMatrix(MatrixArithmetic::identityMatrix()),
	rotateZMatrix(MatrixArithmetic::identityMatrix()),
	scaleMatrix(MatrixArithmetic::identityMatrix()),
	normalizeViewMatrix(MatrixArithmetic::identityMatrix()),
	viewMatrix(MatrixArithmetic::identityMatrix()),
	projectionMatrix(MatrixArithmetic::identityMatrix()),
	viewportMatrix(MatrixArithmetic::identityMatrix()),
	isPerspective(false),
	parameters(std::make_shared<ModelParameters>())
{
}

Model::Model(QString name):
	translateMatrix(MatrixArithmetic::identityMatrix()),
	rotateXMatrix(MatrixArithmetic::identityMatrix()),
	rotateYMatrix(MatrixArithmetic::identityMatrix()),
	rotateZMatrix(MatrixArithmetic::identityMatrix()),
	scaleMatrix(MatrixArithmetic::identityMatrix()),
	viewMatrix(MatrixArithmetic::identityMatrix()),
	projectionMatrix(MatrixArithmetic::identityMatrix()),
	viewportMatrix(MatrixArithmetic::identityMatrix()),
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
	translateMatrix = MatrixArithmetic::translateMatrix(x, y, z);

	return *this;
}

Model& Model::rotateX(float angle)
{
	parameters->setRotateAngleX(angle);
	rotateXMatrix = MatrixArithmetic::rotateXMatrix(MatrixArithmetic::toRadian(angle));

	return *this;
}

Model& Model::rotateY(float angle)
{
	parameters->setRotateAngleY(angle);
	rotateYMatrix = MatrixArithmetic::rotateYMatrix(MatrixArithmetic::toRadian(angle));

	return *this;
}

Model& Model::rotateZ(float angle)
{
	parameters->setRotateAngleZ(angle);
	rotateZMatrix = MatrixArithmetic::rotateZMatrix(MatrixArithmetic::toRadian(angle));

	return *this;
}

Model& Model::scale(float x, float y, float z)
{
	parameters->setScaleX(x);
	parameters->setScaleY(y);
	parameters->setScaleZ(z);
	scaleMatrix = MatrixArithmetic::scaleMatrix(x, y, z);

	return *this;
}

void Model::resetModelMatrix()
{
	translateMatrix = MatrixArithmetic::identityMatrix();
	rotateXMatrix = MatrixArithmetic::identityMatrix();
	rotateYMatrix = MatrixArithmetic::identityMatrix();
	rotateZMatrix = MatrixArithmetic::identityMatrix();
	scaleMatrix = MatrixArithmetic::identityMatrix();
}

Model& Model::setCamera(const std::shared_ptr<const Camera> camera)
{
	const QVector3D &xAxis = camera->getVectorX();
	const QVector3D &yAxis = camera->getVectorY();
	const QVector3D &zAxis = camera->getVectorZ();
	const QVector3D &cameraPosition = camera->getPosition();
	viewMatrix = MatrixArithmetic::viewMatrix(xAxis, yAxis, zAxis, cameraPosition);
	this->camera = camera;

	return *this;
}

void Model::resetViewMatrix()
{
	viewMatrix = MatrixArithmetic::identityMatrix();
}

Model& Model::setOrthographicProjectionMatrix(const Camera &camera)
{
	isPerspective = false;
	parameters->setProjectionType(ProjectionType::Orthographic);

	float width = camera.getViewWidth();
	float height = camera.getViewHeight();
	float near = camera.getNearViewingPlane();
	float far = camera.getFarViewingPlane();
	projectionMatrix = MatrixArithmetic::orthographicMatrix(width, height, near, far);

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
	projectionMatrix = MatrixArithmetic::perspectiveMatrix(width, height, near, far);

	return *this;
}

void Model::resetProjectionMatrix()
{
	projectionMatrix = MatrixArithmetic::identityMatrix();
}

Model& Model::setViewportMatrix(float x, float y, float width, float height)
{
	viewportMatrix = MatrixArithmetic::viewportMatrix(x, y, width, height);

	return *this;
}

void Model::resetViewportMatrix()
{
	viewportMatrix = MatrixArithmetic::identityMatrix();
}

void Model::translateCoordinates()
{
	updateNormalizeViewMatrix();

	QMatrix4x4 resultTranslateMatrix =
			projectionMatrix * viewMatrix * normalizeViewMatrix * translateMatrix *
			rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

	reset();
	std::for_each(transformedVertexList.begin(), transformedVertexList.end(),
	[this, &resultTranslateMatrix](Vertex& currentVertex){
		currentVertex *= resultTranslateMatrix;
		if (this->isPerspective)
		{
			currentVertex.normalizeW();
		}
		currentVertex *= this->viewportMatrix;
	});
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

void Model::updateNormalizeViewMatrix()
{
	const QVector3D &cameraPosition = camera->getRealPosition();

	normalizeViewMatrix =
		MatrixArithmetic::rotateXMatrix(-MatrixArithmetic::toRadian(camera->getAngleX())) *
		MatrixArithmetic::rotateYMatrix(-MatrixArithmetic::toRadian(camera->getAngleY())) *
		MatrixArithmetic::rotateZMatrix(-MatrixArithmetic::toRadian(camera->getAngleZ())) *
		MatrixArithmetic::translateMatrix(-cameraPosition.x(), -cameraPosition.y(), -cameraPosition.z());
}
