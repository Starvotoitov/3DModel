#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include "space3d.h"
#include "projectiontype.h"
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <map>

#include <QTabWidget>

class ModelViewer : public QWidget
//class ModelViewer : public QTabWidget
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
	inline static int TIMER_TICK_TIME = 20;

	using InputHandler = void (ModelViewer::*)();

	Space3D space;
	std::map<Qt::Key, InputHandler> handlers;
	QTimer tickTimer;

	void drawLine(QPointF start, QPointF end, QPainter &painter);
	void render(QPainter& painter);
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

	void moveUpwardHandler();
	void moveDownwardHandler();
	void moveForwardHandler();
	void moveBackwardHandler();
	void moveToLeftHandler();
	void moveToRightHandler();
	void rotateToLeftHandler();
	void rotateToRightHandler();

private slots:
	void tickHandler();
};

#endif // MODELVIEWER_H
