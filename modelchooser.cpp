#include "modelchooser.h"

ModelChooser::ModelChooser(QWidget *parent):
	QWidget(parent),
	bar(new QTabBar(this)),
	layout(new QHBoxLayout(this))
{
	bar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(bar);
	connect(bar, &QTabBar::currentChanged,
			this, &ModelChooser::modelChoosed);
}

void ModelChooser::addNewModel(std::shared_ptr<Model> newModel)
{
	int newBarIndex = bar->addTab(newModel->getParameters()->getName());
	bar->setCurrentIndex(newBarIndex);
}

void ModelChooser::deleteCurrentModel()
{
	if (bar->count() > 0)
	{
		bar->removeTab(bar->currentIndex());
		if (bar->count() > 0)
		{
			bar->setCurrentIndex(0);
			emit modelChoosed(0);
		}
	}
}
