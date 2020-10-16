#ifndef SPACE3D_H
#define SPACE3D_H

#include "camera.h"
#include "model.h"
#include <vector>

class Space3D
{
public:
	Space3D();

	void addNewModel(const std::shared_ptr<Model>& newModel);
	void addNewModel(std::shared_ptr<Model>&& newModel);

	void recalculateCoordinates();
	void updateCameraPosition();

	void changeCameraUpwardMovement();
	void changeCameraDownwardMovement();
	void changeCameraForwardMovement();
	void changeCameraBackwardMovement();
	void changeCameraMovementToLeft();
	void changeCameraMovementToRight();
	void changeRotationToLeft();
	void changeRotationToRight();

	void translate(float x, float y, float z);
	void rotateX(float x);
	void rotateY(float y);
	void rotateZ(float z);
	void scale(float x, float y, float z);

	void setOrthographicProjection();
	void setPerspectiveProjection();

	void updateViewport(float x, float y, float width, float height);

	bool setCurrentModel(int index);
	void deleteCurrentModel();
	std::shared_ptr<const ModelParameters> getCurrentModelParameters() const;

	std::vector<std::shared_ptr<Model>>::const_iterator begin() const;
	std::vector<std::shared_ptr<Model>>::const_iterator end() const;
private:
	Camera viewCamera;
	std::shared_ptr<Model> currentModel;
	std::vector<std::shared_ptr<Model>> modelList;
};

#endif // SPACE3D_H
