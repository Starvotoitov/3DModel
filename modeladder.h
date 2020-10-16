#ifndef MODELADDER_H
#define MODELADDER_H

#include "objparser.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProgressBar>

class ModelAdder : public QWidget
{
	Q_OBJECT
public:
	explicit ModelAdder(QWidget *parent = nullptr);

signals:
	void modelParsed(std::shared_ptr<Model> newModel);

private:
	inline static QString ADD_BUTTON_CAPTION = "Добавить";
	inline static QString FILE_DIALOG_CAPTION = "Выберите файл";
	inline static QString OBJ_FILE_FILTER = "Models (*.obj)";

	QVBoxLayout *layout;
	QProgressBar * parseProgressBar;
	QPushButton *addButton;
	ObjParser parser;

private slots:
	void onModelChoosed();
};

#endif // MODELADDER_H
