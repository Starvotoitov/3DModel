#include "modelviewer.h"
#include <iterator>
#include <cmath>
#include <QCursor>
#include <QRgb>
#include <QDebug>
#include <QElapsedTimer>

ModelViewer::ModelViewer(QWidget *parent):
	QWidget(parent),
	space(cameraController.getCamera()),
	zBuffer(width(), height())
{
	handlers[Qt::Key_Space] = &ModelViewer::moveUpwardHandler;
	handlers[Qt::Key_Control] = &ModelViewer::moveDownwardHandler;
	handlers[Qt::Key_W] = &ModelViewer::moveForwardHandler;
	handlers[Qt::Key_S] = &ModelViewer::moveBackwardHandler;
	handlers[Qt::Key_A] = &ModelViewer::moveToLeftHandler;
	handlers[Qt::Key_D] = &ModelViewer::moveToRightHandler;
	handlers[Qt::Key_Q] = &ModelViewer::rotateToLeftHandler;
	handlers[Qt::Key_E] = &ModelViewer::rotateToRightHandler;
	handlers[Qt::Key_Escape] = &ModelViewer::removeFocusHandler;
}

void ModelViewer::addNewModel(std::shared_ptr<Model> newModel)
{
	newModel->resize(width(), height());
//	newModel->setViewportMatrix(0, 0, width(), height());
	space.addNewModel(newModel);
	emit newModelChosed(newModel->getParameters());
}

void ModelViewer::deleteCurrentModel()
{
	space.deleteCurrentModel();
}

void ModelViewer::changeCurrentModel(int index)
{
	if (space.setCurrentModel(index))
	{
		emit newModelChosed(space.getCurrentModelParameters());
	}
}

void ModelViewer::translate(float x, float y, float z)
{
	space.translate(x, y, z);
}

void ModelViewer::rotateX(float angle)
{
	space.rotateX(angle);
}

void ModelViewer::rotateY(float angle)
{
	space.rotateY(angle);
}

void ModelViewer::rotateZ(float angle)
{
	space.rotateZ(angle);
}

void ModelViewer::scale(float x, float y, float z)
{
	space.scale(x, y, z);
}

void ModelViewer::setProjectionType(ProjectionType newType)
{
	if (newType == ProjectionType::Perspective)
	{
		space.setPerspectiveProjection();
	}
	else
	{
		space.setOrthographicProjection();
	}
}

void ModelViewer::drawTriangle(PolygonTriangle triangle, QImage &canvas, const QVector3D& light, const QVector3D& camera,
							   const QImage& normalMap, const QImage& specularMap, const QImage& albedoMap)
{
	if (triangle.v1.y() > triangle.v2.y())
	{
		std::swap(triangle.v1, triangle.v2);
		std::swap(triangle.vn1, triangle.vn2);
		std::swap(triangle.world1, triangle.world2);
	}
	if (triangle.v1.y() > triangle.v3.y())
	{
		std::swap(triangle.v1, triangle.v3);
		std::swap(triangle.vn1, triangle.vn3);
		std::swap(triangle.world1, triangle.world3);
	}
	if (triangle.v2.y() > triangle.v3.y())
	{
		std::swap(triangle.v2, triangle.v3);
		std::swap(triangle.vn2, triangle.vn3);
		std::swap(triangle.world2, triangle.world3);
	}

	auto startY = std::ceil(triangle.v1.y());
	auto endY = std::ceil(triangle.v2.y());
	for (auto y = startY; y < endY; ++y)
	{
		auto [xa, xb, za, zb] = calculateFirstHalfInterpolation(
				triangle, y);

		auto [normalStart, normalEnd] = calculateFirstHalfNormalInterpolation(
				triangle, y);

		auto [worldStart, worldEnd] = calculateFirstHalfWorldInterpolation(
				triangle, y);

		QVector3D start(xa, y, za);
		QVector3D end(xb, y, zb);
		drawLine(start, end, normalStart, normalEnd, worldStart, worldEnd, canvas, light, camera,
				normalMap, specularMap, albedoMap);
	}

	startY = std::ceil(triangle.v2.y());
	endY = std::ceil(triangle.v3.y());
	for (auto y = startY; y < endY; ++y)
	{
		auto [xa, xb, za, zb] = calculateSecondHalfInterpolation(
				triangle, y);

		auto [normalStart, normalEnd] = calculateSecondHalfNormalInterpolation(
				triangle, y);

		auto [worldStart, worldEnd] = calculateSecondHalfWorldInterpolation(
				triangle, y);

		QVector3D start(xa, y, za);
		QVector3D end(xb, y, zb);
		drawLine(start, end, normalStart, normalEnd, worldStart, worldEnd, canvas, light, camera,
				normalMap, specularMap, albedoMap);
	}
}

void ModelViewer::drawLine(const QVector3D& start, const QVector3D& end,
				const QVector3D& normalStart, const QVector3D& normalEnd,
				const QVector3D& worldStart, const QVector3D& worldEnd,
				QImage& canvas, const QVector3D& light, const QVector3D& camera,
				const QImage& normalMap, const QImage& specularMap, const QImage& albedoMap)
{
	if (!canvas.valid(start.x(), start.y()) || !canvas.valid(end.x(), end.y()))
	{
		return;
	}

	auto L = std::abs(std::ceil(end.x()) - std::ceil(start.x()));

	if (L != 0)
	{
		auto x = (std::min(start.x(), end.x()));
		auto y = start.y();
		for (int i = 0; i < L; ++i)
		{
			float depth = start.z() + (end.z() - start.z()) *
					((x - start.x()) / (end.x() - start.x()));

			auto normal = normalStart + (x - start.x()) *
					(normalEnd - normalStart) / (end.x() - start.x());

			auto world = worldStart + (x - start.x()) *
					(worldEnd - worldStart) / (end.x() - start.x());

			normal.normalize();
			auto lightVector = light - world;
			lightVector.normalize();

			auto intensity = QVector3D::dotProduct(normal, lightVector);
			if (intensity < 0)
			{
				intensity = 0;
			}

			auto reflectionVector = -lightVector - 2 * QVector3D::dotProduct(-lightVector, normal) * normal;
			reflectionVector.normalize();
			auto viewVector = camera - world;
			viewVector.normalize();
			auto reflection = std::pow(std::max(0.0f, QVector3D::dotProduct(reflectionVector, viewVector)), 4);

			auto red = ((0.2 + intensity) * MODEL_COLOR.red() + reflection * REFLECTION_LIGHT.red()) *
					LIGHT_COLOR.red() / 255;
			if (red > 255) red = 255;
			auto green = ((0.2 + intensity) * MODEL_COLOR.green() + reflection * REFLECTION_LIGHT.green()) *
					LIGHT_COLOR.green() / 255;
			if (green > 255) green = 255;
			auto blue = ((0.2 + intensity) * MODEL_COLOR.blue() + reflection * REFLECTION_LIGHT.blue()) *
					LIGHT_COLOR.blue() / 255;
			if (blue > 255) blue = 255;

			QColor color(red, green, blue);

			if (zBuffer.checkAndSet(x, y, depth))
			{
				drawPoint(QPoint(x, y), canvas, color);
			}
			x += 1;
		}
	}
}

void ModelViewer::drawPoint(const QPoint& point, QImage &canvas, const QColor& color)
{
	auto pixels = (QRgb*)canvas.bits();
	pixels[point.x() + point.y() * canvas.width()] = color.rgb();
}

void ModelViewer::render(QPainter& painter)
{
//	qDebug() << space.getRealCamera();
	QElapsedTimer timer;
	timer.start();
	space.recalculateCoordinates();
//	qDebug() << "Recalculation: " << timer.elapsed();

	timer.start();
	zBuffer.clear();
	QImage image(width(), height(), QImage::Format_RGB32);
	image.fill(QColor(255, 255, 255));

	static int i;
	for (const auto& currentModel : space)
	{
		i = 1;
		auto polygons = currentModel->getPolygons();
		auto normalMap = currentModel->getNormalMap();
		auto specularMap = currentModel->getSpecularMap();
		auto albedoMap = currentModel->getAlbedoMap();
		std::for_each(polygons.begin(), polygons.end(), [this, &image, normalMap, specularMap, albedoMap](const PolygonTriangle& currentPolygon){
			if (currentPolygon.isVisible)
			{
				drawTriangle(currentPolygon, image, QVector3D(0, 0, 5), space.getRealCamera(),
							 normalMap, specularMap, albedoMap);
			}
		});
	}
	painter.drawImage(0, 0, image);
//	qDebug() << "Drawing: " << timer.elapsed();

}

void ModelViewer::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	render(painter);
}

void ModelViewer::keyPressEvent(QKeyEvent *event)
{
	Qt::Key keyPressed = static_cast<Qt::Key>(event->key());
	if (handlers.count(keyPressed))
	{
		InputHandler handler = handlers[keyPressed];
		(this->*handler)();
	}
}

void ModelViewer::keyReleaseEvent(QKeyEvent *event)
{
	Qt::Key keyRelease = static_cast<Qt::Key>(event->key());
	if (handlers.count(keyRelease))
	{
		InputHandler handler = handlers[keyRelease];
		(this->*handler)();
	}
}

void ModelViewer::mouseMoveEvent(QMouseEvent *event)
{
	QCursor::setPos(lastCursorPosition.x(), lastCursorPosition.y());

	float changeXAngle = (event->globalY() - lastCursorPosition.y());
	if (changeXAngle != 0)
	{
		cameraController.changeXAngle(-changeXAngle);
	}

	float changeYAngle = (event->globalX() - lastCursorPosition.x());
	if (changeYAngle != 0)
	{
		cameraController.changeYAngle(-changeYAngle);
	}

	update();
}

void ModelViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	setFocus();
}

void ModelViewer::resizeEvent(QResizeEvent *event)
{
//	zBuffer.resize(width(), height());
	space.resize(width(), height());
	zBuffer.resize(width(), height());
}

void ModelViewer::focusInEvent(QFocusEvent *event)
{
	Q_UNUSED(event);
	setMouseTracking(true);
	setCursor(Qt::BlankCursor);
	lastCursorPosition = QPointF(window()->x() + x() + width() / 2, window()->y() + y() + height() / 2);
	QCursor::setPos(lastCursorPosition.x(), lastCursorPosition.y());
}

void ModelViewer::focusOutEvent(QFocusEvent *event)
{
	Q_UNUSED(event);
	setMouseTracking(false);
	setCursor(Qt::ArrowCursor);
}

void ModelViewer::moveUpwardHandler()
{
	cameraController.changeYPosition(0.1);
	update();
}

void ModelViewer::moveDownwardHandler()
{
	cameraController.changeYPosition(-0.1);
	update();
}

void ModelViewer::moveForwardHandler()
{
	cameraController.changeZPosition(-0.1);
	update();
}

void ModelViewer::moveBackwardHandler()
{
	cameraController.changeZPosition(0.1);
	update();
}

void ModelViewer::moveToLeftHandler()
{
	cameraController.changeXPosition(-0.1);
	update();
}

void ModelViewer::moveToRightHandler()
{
	cameraController.changeXPosition(0.1);
	update();
}

void ModelViewer::rotateToLeftHandler()
{
	cameraController.changeZAngle(1);
	update();
}

void ModelViewer::rotateToRightHandler()
{
	cameraController.changeZAngle(-1);
	update();
}

void ModelViewer::removeFocusHandler()
{
	clearFocus();
}

std::tuple<float, float, float, float> ModelViewer::calculateFirstHalfInterpolation(
		PolygonTriangle &triangle, int y)
{
	auto multiplierA = (y - triangle.v1.y()) / (triangle.v2.y() - triangle.v1.y());
	auto multiplierB = (y - triangle.v1.y()) / (triangle.v3.y() - triangle.v1.y());
	return std::tuple{
		triangle.v1.x() + (triangle.v2.x() - triangle.v1.x()) * multiplierA,
		triangle.v1.x() + (triangle.v3.x() - triangle.v1.x()) * multiplierB,
		triangle.v1.z() + (triangle.v2.z() - triangle.v1.z()) * multiplierA,
		triangle.v1.z() + (triangle.v3.z() - triangle.v1.z()) * multiplierB
	};
}

std::tuple<float, float, float, float> ModelViewer::calculateSecondHalfInterpolation(
		PolygonTriangle &triangle, int y)
{
	return std::tuple{
		triangle.v2.x() + (triangle.v3.x() - triangle.v2.x()) *
				((y - triangle.v2.y()) / (triangle.v3.y() - triangle.v2.y())),
		triangle.v1.x() + (triangle.v3.x() - triangle.v1.x()) *
				((y - triangle.v1.y()) / (triangle.v3.y() - triangle.v1.y())),
		triangle.v2.z() + (triangle.v3.z() - triangle.v2.z()) *
				((y - triangle.v2.y()) / (triangle.v3.y() - triangle.v2.y())),
		triangle.v1.z() + (triangle.v3.z() - triangle.v1.z()) *
				((y - triangle.v1.y()) / (triangle.v3.y() - triangle.v1.y()))
	};
}

std::tuple<QVector3D, QVector3D> ModelViewer::calculateFirstHalfNormalInterpolation(
		PolygonTriangle &triangle, float y)
{
	QVector3D normal13 = triangle.vn1 + (y - triangle.v1.y()) *
			(triangle.vn3 - triangle.vn1) / (triangle.v3.y() - triangle.v1.y());
	QVector3D normal12 = triangle.vn1 + (y - triangle.v1.y()) *
			(triangle.vn2 - triangle.vn1) / (triangle.v2.y() - triangle.v1.y());
	return {
		normal12, normal13
	};
}

std::tuple<QVector3D, QVector3D> ModelViewer::calculateSecondHalfNormalInterpolation(
		PolygonTriangle &triangle, float y)
{
	QVector3D normal13 = triangle.vn1 + (y - triangle.v1.y()) *
			(triangle.vn3 - triangle.vn1) / (triangle.v3.y() - triangle.v1.y());
	QVector3D normal23 = triangle.vn2 + (y - triangle.v2.y()) *
			(triangle.vn3 - triangle.vn2) / (triangle.v3.y() - triangle.v2.y());
	return {
		normal23, normal13
	};
}

std::tuple<QVector3D, QVector3D> ModelViewer::calculateFirstHalfWorldInterpolation(
		PolygonTriangle &triangle, float y)
{
	QVector3D world13 = triangle.world1 + (y - triangle.v1.y()) *
			(triangle.world3 - triangle.world1) / (triangle.v3.y() - triangle.v1.y());
	QVector3D world12 = triangle.world1 + (y - triangle.v1.y()) *
			(triangle.world2 - triangle.world1) / (triangle.v2.y() - triangle.v1.y());
	return {
		world12, world13
	};
}

std::tuple<QVector3D, QVector3D> ModelViewer::calculateSecondHalfWorldInterpolation(
		PolygonTriangle &triangle, float y)
{
	QVector3D world13 = triangle.world1 + (y - triangle.v1.y()) *
			(triangle.world3 - triangle.world1) / (triangle.v3.y() - triangle.v1.y());
	QVector3D world23 = triangle.world2 + (y - triangle.v2.y()) *
			(triangle.world3 - triangle.world2) / (triangle.v3.y() - triangle.v2.y());
	return {
		world23, world13
	};
}
/*
std::tuple<TextureCoordinates, TextureCoordinates> ModelViewer::calculateFirstHalfTextureCoordinateInterpolation(
			PolygonTriangle &triangle, float y)
{
	return {
		triangle.vt1 + (y - triangle.v1.y()) *
			(triangle.vt2 - triangle.vt1) / (triangle.v2.y() - triangle.v1.y()),
		triangle.vt1 + (y - triangle.v1.y()) *
			(triangle.vt3 - triangle.vt1) / (triangle.v3.y() - triangle.v1.y())
	};
}

std::tuple<TextureCoordinates, TextureCoordinates> ModelViewer::calculateSecondHalfTextureCoordinateInterpolation(
			PolygonTriangle &triangle, float y)
{
	return {
		triangle.vt2 + (y - triangle.v2.y()) *
			(triangle.vt3 - triangle.vt2) / (triangle.v3.y() - triangle.v2.y()),
		triangle.vt1 + (y - triangle.v1.y()) *
			(triangle.vt3 - triangle.vt1) / (triangle.v3.y() - triangle.v1.y())
	};
}
*/
QColor ModelViewer::getTriangleColor(
			QVector3D &first, QVector3D &second, QVector3D &third, const QVector3D &light)
{
	auto polygonNormal = first + second + third;
	polygonNormal.normalize();
	auto intensity = QVector3D::dotProduct(polygonNormal, light);
	return QColor(255 * intensity, 255 * intensity, 255 * intensity);
}
