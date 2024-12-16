#include "Camera.h"
Camera::Camera()
{
    posX = 0;
    posY = 0;
}

Camera &Camera::GetInstance()
{
    static Camera instance;
    return instance;
}
