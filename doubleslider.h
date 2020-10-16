#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QSlider>

class DoubleSlider : public QSlider
{
	Q_OBJECT

public:
	explicit DoubleSlider(QWidget *parent = nullptr);
	explicit DoubleSlider(Qt::Orientation orientation, QWidget *parent = nullptr);

	void setMinimum(double min);
	void setMaximum(double max);
	void setRange(double min, double max);
	void setValue(double value);
	void setStep(double step);

	double value() const;

signals:
	void doubleValueChanged(double realValue);

private slots:
	void sliderValueChanged(int value);

private:
	inline static double DEFAULT_MIN_VALUE = 0.0;
	inline static double DEFAULT_MAX_VALUE = 1.0;
	inline static double DEFAULT_CURRENT_VALUE = 0.0;
	inline static double DEFAULT_STEP = 0.5;
	inline static int REAL_STEP = 1;

	double minValue;
	double maxValue;
	double currentValue;
	double step;

	void changeRealSliderRange();
};

#endif // DOUBLESLIDER_H
