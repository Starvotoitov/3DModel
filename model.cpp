#include "model.h"
#include "matrixarithmetic.h"
#include <cmath>
#include <QtMath>
#include <QRgb>

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
	parameters(std::make_shared<ModelParameters>()),
	normalMap(nullptr),
	specularMap(nullptr),
	albedoMap(nullptr)
{
}

Model::Model(const QString& name, const QString& dir):
	translateMatrix(MatrixArithmetic::identityMatrix()),
	rotateXMatrix(MatrixArithmetic::identityMatrix()),
	rotateYMatrix(MatrixArithmetic::identityMatrix()),
	rotateZMatrix(MatrixArithmetic::identityMatrix()),
	scaleMatrix(MatrixArithmetic::identityMatrix()),
	viewMatrix(MatrixArithmetic::identityMatrix()),
	projectionMatrix(MatrixArithmetic::identityMatrix()),
	viewportMatrix(MatrixArithmetic::identityMatrix()),
	isPerspective(false),
	parameters(std::make_shared<ModelParameters>()),
	normalMap(dir + "/Normal Map"),
	specularMap(dir + "Specular Map"),
	albedoMap(dir + "Albedo Map")
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
//	projectionMatrix = MatrixArithmetic::perspectiveMatrix(currentWidth, currentHeight, near, far);
	projectionMatrix = MatrixArithmetic::perspectiveMatrix(width, height, near, far);
	return *this;
}

void Model::resetProjectionMatrix()
{
	projectionMatrix = MatrixArithmetic::identityMatrix();
}

Model& Model::setViewportMatrix(float x, float y)
{
	viewportMatrix = MatrixArithmetic::viewportMatrix(x, y, currentWidth, currentHeight);

	return *this;
}

void Model::resetViewportMatrix()
{
	viewportMatrix = MatrixArithmetic::identityMatrix();
}

void Model::translateCoordinates()
{
	updateNormalizeViewMatrix();
//	QMatrix4x4 resultTranslateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
	QMatrix4x4 resultTranslateMatrix = translateMatrix * rotateXMatrix * rotateYMatrix *
			rotateZMatrix * scaleMatrix;
	triangles.resize(polygonalFaceList.size());
/*
	for (int y = 0; y < normalMap.height(); ++y)
	{
		for (int x = 0; x < normalMap.width(); ++x)
		{
			auto pixels = (QRgb*)normalMap.bits();

			auto normalX = qRed(pixels[x + y * normalMap.width()]) / 255.0 * 2 - 1;
			auto normalY = qGreen(pixels[x + y * normalMap.width()]) / 255.0 * 2 - 1;
			auto normalZ = qBlue(pixels[x + y * normalMap.width()]) / 255.0 * 2 - 1;

			QVector3D normal(normalX, normalY, normalZ);
			normal = resultTranslateMatrix * normal;

			pixels[x + y * normalMap.width()] = QColor(normal.x() * 255, normal.y() * 255, normal.z() * 255).rgb();

		}
	}
*/
	for (int i = 0; i < triangles.size(); ++i)
	{
		auto polygonVertexes = polygonalFaceList[i].getPolygonVertexList();

		triangles[i].vn1 = resultTranslateMatrix * vertexNormalList[polygonVertexes[0].vertexNormalIndex - 1].toVector();
		triangles[i].vn2 = resultTranslateMatrix * vertexNormalList[polygonVertexes[1].vertexNormalIndex - 1].toVector();
		triangles[i].vn3 = resultTranslateMatrix * vertexNormalList[polygonVertexes[2].vertexNormalIndex - 1].toVector();

		triangles[i].world1 = resultTranslateMatrix * originalVertexList[polygonVertexes[0].vertexIndex - 1].toVector3D();
		triangles[i].world2 = resultTranslateMatrix * originalVertexList[polygonVertexes[1].vertexIndex - 1].toVector3D();
		triangles[i].world3 = resultTranslateMatrix * originalVertexList[polygonVertexes[2].vertexIndex - 1].toVector3D();

	}

	resultTranslateMatrix = projectionMatrix * viewMatrix * normalizeViewMatrix * resultTranslateMatrix;

	for (int i = 0; i < triangles.size(); ++i)
	{
		auto polygonVertexes = polygonalFaceList[i].getPolygonVertexList();
		auto v1 = originalVertexList[polygonVertexes[0].vertexIndex - 1];
		auto v2 = originalVertexList[polygonVertexes[1].vertexIndex - 1];
		auto v3 = originalVertexList[polygonVertexes[2].vertexIndex - 1];
		v1 *= resultTranslateMatrix;
		v2 *= resultTranslateMatrix;
		v3 *= resultTranslateMatrix;
		if (isPerspective)
		{
			v1.normalizeW();
			v2.normalizeW();
			v3.normalizeW();
		}
		triangles[i].v1 = v1.toVector3D();
		triangles[i].v2 = v2.toVector3D();
		triangles[i].v3 = v3.toVector3D();
	}

	for (int i = 0; i < triangles.size(); ++i)
	{
		auto first = triangles[i].v2 - triangles[i].v1;
		auto second = triangles[i].v3 - triangles[i].v1;
		auto perpendicular = QVector3D::crossProduct(first, second);
		triangles[i].isVisible = QVector3D::dotProduct(QVector3D(0, 0, 0) - this->camera->getVectorZ(), perpendicular) < 0;
	}

	for (int i = 0; i < triangles.size(); ++i)
	{
		triangles[i].v1 = viewportMatrix * triangles[i].v1;
		triangles[i].v2 = viewportMatrix * triangles[i].v2;
		triangles[i].v3 = viewportMatrix * triangles[i].v3;
	}

/*	for (int i = 0; i < triangles.size(); ++i)
	{
		auto polygonVertexes = polygonalFaceList[i].getPolygonVertexList();
		triangles[i].vt1 = textureCoordinatesList[polygonVertexes[0].textureCoordinatesIndex - 1];
		triangles[i].vt2 = textureCoordinatesList[polygonVertexes[1].textureCoordinatesIndex - 1];
		triangles[i].vt3 = textureCoordinatesList[polygonVertexes[2].textureCoordinatesIndex - 1];
	}*/
}

const std::vector<PolygonTriangle>& Model::getPolygons() const
{
	return triangles;
}

const QImage& Model::getNormalMap() const
{
	return normalMap;
}

const QImage& Model::getSpecularMap() const
{
	return specularMap;
}

const QImage& Model::getAlbedoMap() const
{
	return albedoMap;
}

std::shared_ptr<const ModelParameters> Model::getParameters() const
{
	return parameters;
}

void Model::resize(float width, float height)
{
	currentWidth = width;
	currentHeight = height;
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
