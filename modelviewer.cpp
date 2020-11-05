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
	newModel->setViewportMatrix(0, 0, width(), height());
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

void ModelViewer::drawLine(QPointF start, QPointF end, QImage& canvas)
{
	float L = std::abs(end.x() - start.x()) > std::abs(end.y() - start.y()) ?
				std::abs(end.x() - start.x()) :
				std::abs(end.y() - start.y());
	if (L != 0)
	{
		float x = start.x();
		float y = start.y();
		float deltaX = (end.x() - start.x()) / L;
		float deltaY = (end.y() - start.y()) / L;
		for (int i = 0; i < L; ++i)
		{
			drawPoint(QPoint(x, y), canvas, QColor(Qt::white));
			x += deltaX;
			y += deltaY;
		}
	}
}

void ModelViewer::drawPoint(const QPoint& point, QImage &canvas, const QColor& color)
{
	if (point.x() < canvas.width() && point.x() > -1 &&
			point.y() < canvas.height() && point.y() > -1)
	{
		auto pixels = (QRgb*)canvas.bits();
		pixels[point.x() + point.y() * canvas.width()] = color.rgb();
	}
}

void ModelViewer::render(QPainter& painter)
{
	QElapsedTimer timer;
	timer.start();
	space.recalculateCoordinates();
	qDebug() << "Recalculation: " << timer.elapsed();

	timer.start();
	zBuffer.clear();
	QImage image(width(), height(), QImage::Format_RGB32);
	for (const auto& currentModel : space)
	{
		auto polygons = currentModel->getPolygons();
		auto vertexes = currentModel->getVertexes();
		for (const auto& currentPolygon : polygons)
		{
			auto polygonVertexList = currentPolygon.getPolygonVertexList();

			auto fromVertex = polygonVertexList.begin();
			auto toVertex = fromVertex;
			do
			{
				fromVertex = toVertex;
				toVertex = std::next(fromVertex);
				if (toVertex == polygonVertexList.end())
				{
					toVertex = polygonVertexList.begin();
				}

				int fromIndex = (*fromVertex).vertexIndex;
				int toIndex = (*toVertex).vertexIndex;

				drawLine(QPoint(vertexes[fromIndex - 1].getX(), vertexes[fromIndex - 1].getY()),
						QPoint(vertexes[toIndex - 1].getX(), vertexes[toIndex - 1].getY()),
						image);
			}
			while (toVertex != polygonVertexList.begin());
		}
	}
	painter.drawImage(0, 0, image);
	qDebug() << "Drawing: " << timer.elapsed();

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

	float changeXAngle = event->globalY() - lastCursorPosition.y();
	if (changeXAngle != 0)
	{
		cameraController.changeXAngle(-changeXAngle);
	}

	float changeYAngle = event->globalX() - lastCursorPosition.x();
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
