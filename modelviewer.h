#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include "space3d.h"
#include "cameramovementcontroller.h"
#include "projectiontype.h"
#include "zbuffer.h"
#include "polygontriangle.h"
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

	inline static QColor MODEL_COLOR = QColor(255, 0, 0);
	inline static QColor LIGHT_COLOR = QColor(255, 255, 255);
	inline static QColor REFLECTION_LIGHT = QColor(255, 255, 255);

	CameraMovementController cameraController;
	Space3D space;
	ZBuffer zBuffer;
	std::map<Qt::Key, InputHandler> handlers;

	QPointF lastCursorPosition;

	void drawTriangle(PolygonTriangle triangle, QImage& canvas, const QVector3D& light, const QVector3D& camera,
					  const QImage& normalMap, const QImage& specularMap, const QImage& albedoMap);
	void drawLine(const QVector3D& start, const QVector3D& end,
				  const QVector3D& normalStart, const QVector3D& normalEnd,
				  const QVector3D& worldStart, const QVector3D& worldEnd,
				  QImage& canvas, const QVector3D& light, const QVector3D& camera,
				  const QImage& normalMap, const QImage& specularMap, const QImage& albedoMap);
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

	static std::tuple<float, float, float, float> calculateFirstHalfInterpolation(
			PolygonTriangle &triangle, int y);
	static std::tuple<float, float, float, float> calculateSecondHalfInterpolation(
			PolygonTriangle &triangle, int y);
	static std::tuple<QVector3D, QVector3D> calculateFirstHalfNormalInterpolation(
			PolygonTriangle &triangle, float y);
	static std::tuple<QVector3D, QVector3D> calculateSecondHalfNormalInterpolation(
			PolygonTriangle &triangle, float y);
	static std::tuple<QVector3D, QVector3D> calculateFirstHalfWorldInterpolation(
			PolygonTriangle &triangle, float y);
	static std::tuple<QVector3D, QVector3D> calculateSecondHalfWorldInterpolation(
			PolygonTriangle &triangle, float y);
//	static std::tuple<TextureCoordinates, TextureCoordinates> calculateFirstHalfTextureCoordinateInterpolation(
//			PolygonTriangle &triangle, float y);
//	static std::tuple<TextureCoordinates, TextureCoordinates> calculateSecondHalfTextureCoordinateInterpolation(
//			PolygonTriangle &triangle, float y);


	static QColor getTriangleColor(QVector3D &first, QVector3D &second, QVector3D &third, const QVector3D& light);
};

#endif // MODELVIEWER_H
