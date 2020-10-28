#ifndef CAMERAMOVEMENTCONTROLLER_H
#define CAMERAMOVEMENTCONTROLLER_H

#include "camera.h"
#include <memory>

class CameraMovementController
{
public:
	CameraMovementController();
	CameraMovementController(std::shared_ptr<Camera> camera);

	void setCamera(std::shared_ptr<Camera> camera);
	std::shared_ptr<const Camera> getCamera() const;

	void changeXPosition(float changeVal);
	void changeYPosition(float changeVal);
	void changeZPosition(float changeVal);

	void changeXAngle(float changeVal);
	void changeYAngle(float changeVal);
	void changeZAngle(float changeVal);

	void moveCamera();

private:
	std::shared_ptr<Camera> controlledCamera;
};

#endif // CAMERAMOVEMENTCONTROLLER_H
