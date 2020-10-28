#include "cameramovementcontroller.h"

CameraMovementController::CameraMovementController():
	controlledCamera(std::make_shared<Camera>())
{
}

CameraMovementController::CameraMovementController(std::shared_ptr<Camera> camera):
	controlledCamera(camera)
{
}

void CameraMovementController::setCamera(std::shared_ptr<Camera> camera)
{
	controlledCamera = camera;
}

std::shared_ptr<const Camera> CameraMovementController::getCamera() const
{
	return controlledCamera;
}

void CameraMovementController::changeXPosition(float changeVal)
{
	controlledCamera->changeXPosition(changeVal);
}

void CameraMovementController::changeYPosition(float changeVal)
{
	controlledCamera->changeYPosition(changeVal);
}

void CameraMovementController::changeZPosition(float changeVal)
{
	controlledCamera->changeZPosition(changeVal);
}

void CameraMovementController::changeXAngle(float changeVal)
{
	controlledCamera->changeXAngle(changeVal);
}

void CameraMovementController::changeYAngle(float changeVal)
{
	controlledCamera->changeYAngle(changeVal);
}

void CameraMovementController::changeZAngle(float changeVal)
{
	controlledCamera->changeZAngle(changeVal);
}
