#include "modelviewer.h"
#include <iterator>
#include <cmath>
#include <QCursor>

ModelViewer::ModelViewer(QWidget *parent):
	QWidget(parent),
	space(cameraController.getCamera()),
	tickTimer(this)
{
	handlers[Qt::Key_Space] = &ModelViewer::moveUpwardHandler;
	handlers[Qt::Key_Shift] = &ModelViewer::moveDownwardHandler;
	handlers[Qt::Key_W] = &ModelViewer::moveForwardHandler;
	handlers[Qt::Key_S] = &ModelViewer::moveBackwardHandler;
	handlers[Qt::Key_A] = &ModelViewer::moveToLeftHandler;
	handlers[Qt::Key_D] = &ModelViewer::moveToRightHandler;
	handlers[Qt::Key_Q] = &ModelViewer::rotateToLeftHandler;
	handlers[Qt::Key_E] = &ModelViewer::rotateToRightHandler;
	handlers[Qt::Key_Escape] = &ModelViewer::removeFocusHandler;

	connect(&tickTimer, &QTimer::timeout, this, &ModelViewer::tickHandler);
	tickTimer.start(TIMER_TICK_TIME);
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

void ModelViewer::drawLine(QPointF start, QPointF end, QPainter &painter)
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
			painter.drawPoint(std::round(x), std::round(y));
			x += deltaX;
			y += deltaY;
		}
	}
}

void ModelViewer::render(QPainter& painter)
{
	space.recalculateCoordinates();

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
						 painter);
			}
			while (toVertex != polygonVertexList.begin());
		}
	}
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
#include <iostream>
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
}

void ModelViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	setFocus();
	lastCursorPosition = QPointF(window()->x() + x() + width() / 2, window()->y() + y() + height() / 2);
}

void ModelViewer::resizeEvent(QResizeEvent *event)
{
//	space.updateViewport(0, 0, width(), height());
}

void ModelViewer::focusInEvent(QFocusEvent *event)
{
	Q_UNUSED(event);
	setMouseTracking(true);
	setCursor(Qt::BlankCursor);
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
}

void ModelViewer::moveDownwardHandler()
{
	cameraController.changeYPosition(-0.1);
}

void ModelViewer::moveForwardHandler()
{
	cameraController.changeZPosition(-0.1);
}

void ModelViewer::moveBackwardHandler()
{
	cameraController.changeZPosition(0.1);
}

void ModelViewer::moveToLeftHandler()
{
	cameraController.changeXPosition(-0.1);
}

void ModelViewer::moveToRightHandler()
{
	cameraController.changeXPosition(0.1);
}

void ModelViewer::rotateToLeftHandler()
{
	cameraController.changeZAngle(1);
}

void ModelViewer::rotateToRightHandler()
{
	cameraController.changeZAngle(-1);
}

void ModelViewer::removeFocusHandler()
{
	clearFocus();
}

void ModelViewer::tickHandler()
{
	update();
}
