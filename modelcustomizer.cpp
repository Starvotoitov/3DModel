#include "modelcustomizer.h"

ModelCustomizer::ModelCustomizer(QWidget *parent):
	QWidget(parent),
	layout(new QGridLayout(this))
{
	createProjectionComboBox();

	coordinateXSpinBox = createCoordinateSpinBox(COORDINATE_X_SPIN_BOX_CAPTION, MIN_COORDINATE, MAX_COORDINATE, 1);
	coordinateYSpinBox = createCoordinateSpinBox(COORDINATE_Y_SPIN_BOX_CAPTION, MIN_COORDINATE, MAX_COORDINATE, 2);
	coordinateZSpinBox = createCoordinateSpinBox(COORDINATE_Z_SPIN_BOX_CAPTION, MIN_COORDINATE, MAX_COORDINATE, 3);

	rotateXSlider = createRotateSlider(ROTATE_X_SLIDER_CAPTION, MIN_ROTATE_ANGLE, MAX_ROTATE_ANGLE, 4);
	rotateYSlider = createRotateSlider(ROTATE_Y_SLIDER_CAPTION, MIN_ROTATE_ANGLE, MAX_ROTATE_ANGLE, 5);
	rotateZSlider = createRotateSlider(ROTATE_Z_SLIDER_CAPTION, MIN_ROTATE_ANGLE, MAX_ROTATE_ANGLE, 6);

	scaleXSlider = createScaleSlider(SCALE_X_SLIDER_CAPTION, MIN_SCALE, MAX_SCALE, 7);
	scaleYSlider = createScaleSlider(SCALE_Y_SLIDER_CAPTION, MIN_SCALE, MAX_SCALE, 8);
	scaleZSlider = createScaleSlider(SCALE_Z_SLIDER_CAPTION, MIN_SCALE, MAX_SCALE, 9);

	QPushButton *deleteButton = new QPushButton(DELETE_BUTTON_CAPTION, this);
	layout->addWidget(deleteButton, 10, 0, 1, 2);

	connect(projectionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &ModelCustomizer::projectionTypeChanged);

	connect(coordinateXSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			this, &ModelCustomizer::coordinateXChanged);
	connect(coordinateYSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			this, &ModelCustomizer::coordinateYChanged);
	connect(coordinateZSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
			this, &ModelCustomizer::coordinateZChanged);

	connect(rotateXSlider, &QSlider::valueChanged,
			this, &ModelCustomizer::angleXChanged);
	connect(rotateYSlider, &QSlider::valueChanged,
			this, &ModelCustomizer::angleYChanged);
	connect(rotateZSlider, &QSlider::valueChanged,
			this, &ModelCustomizer::angleZChanged);

	connect(scaleXSlider, &DoubleSlider::doubleValueChanged,
			this, &ModelCustomizer::scaleXChanged);
	connect(scaleYSlider, &DoubleSlider::doubleValueChanged,
			this, &ModelCustomizer::scaleYChanged);
	connect(scaleZSlider, &DoubleSlider::doubleValueChanged,
			this, &ModelCustomizer::scaleZChanged);

	connect(deleteButton, &QPushButton::clicked,
			this, &ModelCustomizer::deleteCurrentModel);
}

QDoubleSpinBox* ModelCustomizer::createCoordinateSpinBox(QString name, double minValue, double maxValue, int row)
{
	QDoubleSpinBox *coordinateSpinBox = new QDoubleSpinBox(this);
	coordinateSpinBox->setRange(minValue, maxValue);
	coordinateSpinBox->setSingleStep(COORDINATE_STEP);
	layout->addWidget(new QLabel(name, this), row, 0);
	layout->addWidget(coordinateSpinBox, row, 1);
	return coordinateSpinBox;
}

QSlider* ModelCustomizer::createRotateSlider(QString name, int minValue, int maxValue, int row)
{
	QSlider *rotateSlider = new QSlider(Qt::Horizontal, this);
	rotateSlider->setRange(minValue, maxValue);
	rotateSlider->setSingleStep(ROTATE_STEP);
	rotateSlider->setPageStep(ROTATE_STEP);
	rotateSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	layout->addWidget(new QLabel(name), row, 0);
	layout->addWidget(rotateSlider, row, 1);
	return rotateSlider;
}

DoubleSlider* ModelCustomizer::createScaleSlider(QString name, double minValue, double maxValue, int row)
{
	DoubleSlider *scaleSlider = new DoubleSlider(Qt::Horizontal, this);
	scaleSlider->setRange(minValue, maxValue);
	scaleSlider->setStep(SCALE_STEP);
	scaleSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	layout->addWidget(new QLabel(name), row, 0);
	layout->addWidget(scaleSlider, row, 1);
	return scaleSlider;
}

void ModelCustomizer::createProjectionComboBox()
{
	projectionComboBox = new QComboBox(this);
	QVariant variant;
	variant.setValue(ProjectionType::Perspective);
	projectionComboBox->addItem(PERSPECTIVE_PROJECTION_CAPTION, variant);
	variant.setValue(ProjectionType::Orthographic);
	projectionComboBox->addItem(ORTHOGRAPHIC_PROJECTION_CAPTION, variant);
	layout->addWidget(projectionComboBox, 0, 0, 1, 2);
}

void ModelCustomizer::blockSignals()
{
	coordinateXSpinBox->blockSignals(true);
	coordinateYSpinBox->blockSignals(true);
	coordinateZSpinBox->blockSignals(true);
	rotateXSlider->blockSignals(true);
	rotateYSlider->blockSignals(true);
	rotateZSlider->blockSignals(true);
	scaleXSlider->blockSignals(true);
	scaleYSlider->blockSignals(true);
	scaleZSlider->blockSignals(true);
}

void ModelCustomizer::unblockSignals()
{
	coordinateXSpinBox->blockSignals(false);
	coordinateYSpinBox->blockSignals(false);
	coordinateZSpinBox->blockSignals(false);
	rotateXSlider->blockSignals(false);
	rotateYSlider->blockSignals(false);
	rotateZSlider->blockSignals(false);
	scaleXSlider->blockSignals(false);
	scaleYSlider->blockSignals(false);
	scaleZSlider->blockSignals(false);
}

void ModelCustomizer::setModel(std::shared_ptr<const ModelParameters> newModel)
{
	blockSignals();
	coordinateXSpinBox->setValue(newModel->getX());
	coordinateYSpinBox->setValue(newModel->getY());
	coordinateZSpinBox->setValue(newModel->getZ());
	rotateXSlider->setValue(newModel->getRotateAngleX());
	rotateYSlider->setValue(newModel->getRotateAngleY());
	rotateZSlider->setValue(newModel->getRotateAngleZ());
	scaleXSlider->setValue(newModel->getScaleX());
	scaleYSlider->setValue(newModel->getScaleY());
	scaleZSlider->setValue(newModel->getScaleZ());
	unblockSignals();
}

void ModelCustomizer::projectionTypeChanged(int typeIndex)
{
	Q_UNUSED(typeIndex);
	auto type = qvariant_cast<ProjectionType>(projectionComboBox->currentData());
	emit settedProjectionType(type);
}

void ModelCustomizer::coordinateXChanged(double newX)
{
	emit translated(newX, coordinateYSpinBox->value(), coordinateZSpinBox->value());
}

void ModelCustomizer::coordinateYChanged(double newY)
{
	emit translated(coordinateXSpinBox->value(), newY, coordinateZSpinBox->value());
}

void ModelCustomizer::coordinateZChanged(double newZ)
{
	emit translated(coordinateXSpinBox->value(), coordinateYSpinBox->value(), newZ);
}

void ModelCustomizer::angleXChanged(int newAngle)
{
	emit rotatedX(newAngle);
}

void ModelCustomizer::angleYChanged(int newAngle)
{
	emit rotatedY(newAngle);
}

void ModelCustomizer::angleZChanged(int newAngle)
{
	emit rotatedZ(newAngle);
}

void ModelCustomizer::scaleXChanged(double newScale)
{
	emit scaled(newScale, scaleYSlider->value(), scaleZSlider->value());
}

void ModelCustomizer::scaleYChanged(double newScale)
{
	emit scaled(scaleXSlider->value(), newScale, scaleZSlider->value());
}

void ModelCustomizer::scaleZChanged(double newScale)
{
	emit scaled(scaleXSlider->value(), scaleYSlider->value(), newScale);
}

