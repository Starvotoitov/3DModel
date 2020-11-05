#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include "space3d.h"
#include "cameramovementcontroller.h"
#include "projectiontype.h"
#include "zbuffer.h"
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <map>
#include <QImage>

class ModelViewer : public QWidget
{
	Q_OBJECT
public:
	explicit ModelViewer(QWidget *parent = nullptr);

public slots:
	void addNewModel(std::shared_ptr<Model> newModel);
	void deleteCurrentModel();
	void changeCurrentModel(int index);
	void translate(float x, float y, float z);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void scale(float x, float y, float z);
	void setProjectionType(ProjectionType newType);

signals:
	void newModelChosed(std::shared_ptr<const ModelParameters> newModel);

private:
	using InputHandler = void (ModelViewer::*)();

	CameraMovementController cameraController;
	Space3D space;
	ZBuffer zBuffer;
	std::map<Qt::Key, InputHandler> handlers;

	QPointF lastCursorPosition;

	void drawLine(QPointF start, QPointF end, QImage& canvas);
	void drawPoint(const QPoint& point, QImage& canvas, const QColor& color);
	void render(QPainter& painter);
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
	void focusInEvent(QFocusEvent *event) override;
	void focusOutEvent(QFocusEvent *event) override;

	void moveUpwardHandler();
	void moveDownwardHandler();
	void moveForwardHandler();
	void moveBackwardHandler();
	void moveToLeftHandler();
	void moveToRightHandler();
	void rotateToLeftHandler();
	void rotateToRightHandler();
	void removeFocusHandler();
};

#endif // MODELVIEWER_H
