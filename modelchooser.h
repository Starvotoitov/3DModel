#ifndef MODELCHOOSER_H
#define MODELCHOOSER_H

#include "model.h"
#include <QWidget>
#include <QTabBar>
#include <QHBoxLayout>

class ModelChooser : public QWidget
{
	Q_OBJECT
public:
	explicit ModelChooser(QWidget *parent = nullptr);

public slots:
	void addNewModel(std::shared_ptr<Model> newModel);
	void deleteCurrentModel();

signals:
	void modelChoosed(int index);

private:
	QTabBar *bar;
	QHBoxLayout *layout;
};

#endif // MODELCHOOSER_H
