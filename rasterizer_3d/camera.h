#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    glm::vec4 forward;
    glm::vec4 right;
    glm::vec4 up;
    float fov;
    glm::vec3 worldPos;
    float near;
    float far;
    float ratio;

    glm::mat4 View();
    glm::mat4 Projection();
    void TranslateForward(float);
    void TranslateRight(float);
    void TranslateUp(float);
    void RotateAboutForward(float);
    void RotateAboutRight(float);
    void RotateAboutUp(float);
};

#endif // CAMERA_H
