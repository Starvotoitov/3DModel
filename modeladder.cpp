#include "modeladder.h"
#include <QFileDialog>

ModelAdder::ModelAdder(QWidget *parent):
	QWidget(parent),
	layout(new QVBoxLayout(this)),
	parseProgressBar(new QProgressBar(this)),
	addButton(new QPushButton(ADD_BUTTON_CAPTION, this))
{
	layout->addWidget(parseProgressBar);
	layout->addWidget(addButton);
	connect(addButton, &QPushButton::clicked, this, &ModelAdder::onModelChoosed);
}

void ModelAdder::onModelChoosed()
{
	QString filePath = QFileDialog::getOpenFileName(this, FILE_DIALOG_CAPTION, QString(), OBJ_FILE_FILTER);
	if (filePath != nullptr)
	{
		parser.setObjFile(filePath);
		parser.parse();
		emit modelParsed(parser.getModel());
	}
}
