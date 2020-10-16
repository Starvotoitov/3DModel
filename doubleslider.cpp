#include "doubleslider.h"
#include <cmath>

DoubleSlider::DoubleSlider(QWidget *parent):
	QSlider(parent),
	minValue(DEFAULT_MIN_VALUE),
	maxValue(DEFAULT_MAX_VALUE),
	currentValue(DEFAULT_CURRENT_VALUE),
	step(DEFAULT_STEP)
{
	setSingleStep(REAL_STEP);
	setPageStep(REAL_STEP);
	connect(this, &DoubleSlider::valueChanged,
			this, &DoubleSlider::sliderValueChanged);
}

DoubleSlider::DoubleSlider(Qt::Orientation orientation, QWidget *parent):
	QSlider(orientation, parent),
	minValue(0.0),
	maxValue(1.0),
	currentValue(0.0),
	step(0.5)
{
	setSingleStep(1);
	setPageStep(1);
	connect(this, &DoubleSlider::valueChanged,
			this, &DoubleSlider::sliderValueChanged);
}

void DoubleSlider::setMinimum(double min)
{
	minValue = min;
	changeRealSliderRange();
}

void DoubleSlider::setMaximum(double max)
{
	maxValue = max;
	changeRealSliderRange();
}

void DoubleSlider::setRange(double min, double max)
{
	minValue = min;
	maxValue = max;
	changeRealSliderRange();
}

void DoubleSlider::setValue(double value)
{
	currentValue = value;
	QSlider::setValue(value / step - 1);
}

void DoubleSlider::setStep(double step)
{
	this->step = step;
	changeRealSliderRange();
}

double DoubleSlider::value() const
{
	return currentValue;
}

void DoubleSlider::changeRealSliderRange()
{
	int realMaxValue = std::ceil((maxValue - minValue) / step);
	QSlider::setRange(0, realMaxValue);
}

void DoubleSlider::sliderValueChanged(int realValue)
{
	double value = (realValue * step) + minValue;
	if (value > maxValue)
	{
		value = maxValue;
	}
	currentValue = value;
	emit doubleValueChanged(value);
}
