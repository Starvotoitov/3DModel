#ifndef MODELCURSOMIZER_H
#define MODELCURSOMIZER_H

#include "modelparameters.h"
#include "doubleslider.h"
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QComboBox>

class ModelCustomizer : public QWidget
{
	Q_OBJECT
public:
	explicit ModelCustomizer(QWidget *parent = nullptr);

public slots:
	void setModel(std::shared_ptr<const ModelParameters> newModel);

signals:
	void translated(float x, float y, float z);
	void rotatedX(float angle);
	void rotatedY(float angle);
	void rotatedZ(float angle);
	void scaled(float x, float y, float z);
	void settedProjectionType(ProjectionType newType);
	void deleteCurrentModel();

private:
	inline static QString COORDINATE_X_SPIN_BOX_CAPTION = "Координата X";
	inline static QString COORDINATE_Y_SPIN_BOX_CAPTION = "Координата Y";
	inline static QString COORDINATE_Z_SPIN_BOX_CAPTION = "Координата Z";
	inline static QString ROTATE_X_SLIDER_CAPTION = "Поворот вокруг X";
	inline static QString ROTATE_Y_SLIDER_CAPTION = "Поворот вокруг Y";
	inline static QString ROTATE_Z_SLIDER_CAPTION = "Поворот вокруг Z";
	inline static QString SCALE_X_SLIDER_CAPTION = "Масштаб X";
	inline static QString SCALE_Y_SLIDER_CAPTION = "Масштаб Y";
	inline static QString SCALE_Z_SLIDER_CAPTION = "Масштаб Z";
	inline static QString DELETE_BUTTON_CAPTION = "Удалить";
	inline static QString PERSPECTIVE_PROJECTION_CAPTION = "Перспективная";
	inline static QString ORTHOGRAPHIC_PROJECTION_CAPTION = "Ортографическая";

	inline static double MIN_COORDINATE = -10.0;
	inline static double MAX_COORDINATE = 10.0;
	inline static double COORDINATE_STEP = 0.1;
	inline static int MIN_ROTATE_ANGLE = 0;
	inline static int MAX_ROTATE_ANGLE = 360;
	inline static int ROTATE_STEP = 1;
	inline static double MIN_SCALE = 0.25;
	inline static double MAX_SCALE = 5.0;
	inline static double SCALE_STEP = 0.25;

	QGridLayout *layout;
	QComboBox *projectionComboBox;
	QDoubleSpinBox *coordinateXSpinBox;
	QDoubleSpinBox *coordinateYSpinBox;
	QDoubleSpinBox *coordinateZSpinBox;
	QSlider *rotateXSlider;
	QSlider *rotateYSlider;
	QSlider *rotateZSlider;
	DoubleSlider *scaleXSlider;
	DoubleSlider *scaleYSlider;
	DoubleSlider *scaleZSlider;

	QDoubleSpinBox* createCoordinateSpinBox(QString name, double minValue, double maxValue, int row);
	QSlider* createRotateSlider(QString name, int minValue, int maxValue, int row);
	DoubleSlider* createScaleSlider(QString name, double minValue, double maxValue, int row);
	void createProjectionComboBox();
	void blockSignals();
	void unblockSignals();

private slots:
	void projectionTypeChanged(int typeIndex);
	void coordinateXChanged(double newX);
	void coordinateYChanged(double newY);
	void coordinateZChanged(double newZ);
	void angleXChanged(int newAngle);
	void angleYChanged(int newAngle);
	void angleZChanged(int newAngle);
	void scaleXChanged(double newScale);
	void scaleYChanged(double newScale);
	void scaleZChanged(double newScale);
};

#endif // MODELCURSOMIZER_H
