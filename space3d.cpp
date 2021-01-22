#include "space3d.h"

Space3D::Space3D():
	viewCamera(nullptr),
	currentModel(nullptr)
{
}

Space3D::Space3D(std::shared_ptr<const Camera> camera):
	viewCamera(camera),
	currentModel(nullptr)
{
}

void Space3D::addNewModel(const std::shared_ptr<Model> &newModel)
{
	newModel->setPerspectiveProjectionMatrix(*viewCamera);
	newModel->setCamera(viewCamera);
	newModel->setViewportMatrix(0, 0);
	modelList.push_back(newModel);
	currentModel = newModel;
}

void Space3D::addNewModel(std::shared_ptr<Model> &&newModel)
{
	newModel->setPerspectiveProjectionMatrix(*viewCamera);
	newModel->setCamera(viewCamera);
	newModel->setViewportMatrix(0, 0);
	modelList.push_back(std::forward<std::shared_ptr<Model>>(newModel));
	currentModel = newModel;
}

void Space3D::recalculateCoordinates()
{
	for (auto& currentModel : modelList)
	{
		currentModel->translateCoordinates();
	}
}

void Space3D::translate(float x, float y, float z)
{
	if (currentModel != nullptr)
	{
		currentModel->translate(x, y, z);
	}
}

void Space3D::rotateX(float x)
{
	if (currentModel != nullptr)
	{
		currentModel->rotateX(x);
	}
}

void Space3D::rotateY(float y)
{
	if (currentModel != nullptr)
	{
		currentModel->rotateY(y);
	}
}

void Space3D::rotateZ(float z)
{
	if (currentModel != nullptr)
	{
		currentModel->rotateZ(z);
	}
}

void Space3D::scale(float x, float y, float z)
{
	if (currentModel != nullptr)
	{
		currentModel->scale(x, y, z);
	}
}

void Space3D::setOrthographicProjection()
{
	if (currentModel != nullptr)
	{
		currentModel->setOrthographicProjectionMatrix(*viewCamera);
	}
}

void Space3D::setPerspectiveProjection()
{
	if (currentModel != nullptr)
	{
		currentModel->setPerspectiveProjectionMatrix(*viewCamera);
	}
}
/*
void Space3D::updateViewport(float x, float y, float width, float height)
{
	for (auto &currentModel : modelList)
	{
		currentModel->setViewportMatrix(x, y, width, height);
	}
}*/

void Space3D::resize(float width, float height)
{
	for (auto &currentModel : modelList)
	{
		currentModel->resize(width, height);
		currentModel->setPerspectiveProjectionMatrix(*viewCamera);
		currentModel->setViewportMatrix(0, 0);
	}
}

bool Space3D::setCurrentModel(int index)
{
	if (index > -1 && index < modelList.size())
	{
		currentModel = modelList.at(index);
		return true;
	}
	return false;
}

void Space3D::deleteCurrentModel()
{
	if (currentModel != nullptr)
	{
		auto currentModelIter = std::find(modelList.begin(), modelList.end(), currentModel);
		modelList.erase(currentModelIter);
		currentModel = nullptr;
	}
}

std::shared_ptr<const ModelParameters> Space3D::getCurrentModelParameters() const
{
	return currentModel->getParameters();
}

QVector3D Space3D::getCameraDirection() const
{
	return QVector3D(0, 0, 0) - viewCamera->getVectorZ();
}

QVector3D Space3D::getRealCamera() const
{
	return viewCamera->getRealPosition();
}

std::vector<std::shared_ptr<Model>>::const_iterator Space3D::begin() const
{
	return modelList.cbegin();
}

std::vector<std::shared_ptr<Model>>::const_iterator Space3D::end() const
{
	return modelList.cend();
}

