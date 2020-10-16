#include "modelviewer.h"
#include <iterator>
#include <cmath>

ModelViewer::ModelViewer(QWidget *parent):
	QWidget(parent),
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

void ModelViewer::mousePressEvent(QMouseEvent *event)
{

}

void ModelViewer::mouseMoveEvent(QMouseEvent *event)
{

}

void ModelViewer::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void ModelViewer::resizeEvent(QResizeEvent *event)
{
	space.updateViewport(0, 0, width(), height());
}

void ModelViewer::moveUpwardHandler()
{
	space.changeCameraUpwardMovement();
}

void ModelViewer::moveDownwardHandler()
{
	space.changeCameraDownwardMovement();
}

void ModelViewer::moveForwardHandler()
{
	space.changeCameraForwardMovement();
}

void ModelViewer::moveBackwardHandler()
{
	space.changeCameraBackwardMovement();
}

void ModelViewer::moveToLeftHandler()
{
	space.changeCameraMovementToLeft();
}

void ModelViewer::moveToRightHandler()
{
	space.changeCameraMovementToRight();
}

void ModelViewer::rotateToLeftHandler()
{
	space.changeRotationToLeft();
}

void ModelViewer::rotateToRightHandler()
{
	space.changeRotationToRight();
}

void ModelViewer::tickHandler()
{
	space.updateCameraPosition();
	update();
}
