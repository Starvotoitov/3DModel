#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->adder, &ModelAdder::modelParsed,
			ui->viewer, &ModelViewer::addNewModel);
	connect(ui->adder, &ModelAdder::modelParsed,
			ui->chooser, &ModelChooser::addNewModel);

	connect(ui->customizer, &ModelCustomizer::translated,
			ui->viewer, &ModelViewer::translate);
	connect(ui->customizer, &ModelCustomizer::rotatedX,
			ui->viewer, &ModelViewer::rotateX);
	connect(ui->customizer, &ModelCustomizer::rotatedY,
			ui->viewer, &ModelViewer::rotateY);
	connect(ui->customizer, &ModelCustomizer::rotatedZ,
			ui->viewer, &ModelViewer::rotateZ);
	connect(ui->customizer, &ModelCustomizer::scaled,
			ui->viewer, &ModelViewer::scale);
	connect(ui->customizer, &ModelCustomizer::settedProjectionType,
			ui->viewer, &ModelViewer::setProjectionType);
	connect(ui->customizer, &ModelCustomizer::deleteCurrentModel,
			ui->viewer, &ModelViewer::deleteCurrentModel);
	connect(ui->customizer, &ModelCustomizer::deleteCurrentModel,
			ui->chooser, &ModelChooser::deleteCurrentModel);

	connect(ui->viewer, &ModelViewer::newModelChosed,
			ui->customizer, &ModelCustomizer::setModel);

	connect(ui->chooser, &ModelChooser::modelChoosed,
			ui->viewer, &ModelViewer::changeCurrentModel);
}

MainWindow::~MainWindow()
{
	delete ui;
}

