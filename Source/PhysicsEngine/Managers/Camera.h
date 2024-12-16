#ifndef _camera_h_
#define _camera_h_
class Camera
{
private:
    Camera();
public:
    static Camera& GetInstance();
    float posX, posY;
    static constexpr float CAMERA_MOVE_SPPED = 5.f;
};

#endif
