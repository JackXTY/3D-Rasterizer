#include "camera.h"
#include "glm/gtx/transform.hpp"
#include <cmath>
#include <iostream>

Camera::Camera() :
    forward(glm::vec4(0.f, 0.f, -1.0f, 0.f)),
    right(glm::vec4(1.f, 0.f, 0.f, 0.f)),
    up(glm::vec4(0.f, 1.f, 0.f, 0.f)),
    fov(45.f),
    worldPos(glm::vec4(0.f, 0.f, 10.f, 1.f)),
    near(0.01f), far(100.0f), ratio(1.0f)
{}

glm::mat4 Camera::View()
{
    glm::mat4 translation =
        glm::mat4(
            glm::vec4(1.f, 0.f, 0.f, 0.f),
            glm::vec4(0.f, 1.f, 0.f, 0.f),
            glm::vec4(0.f, 0.f, 1.f, 0.f),
            glm::vec4(-worldPos.x, -worldPos.y, -worldPos.z, 1.f)
        );
    glm::mat4 rotation =
        glm::mat4(
            glm::vec4(right.x, up.x, forward.x, 0.f),
            glm::vec4(right.y, up.y, forward.y, 0.f),
            glm::vec4(right.z, up.z, forward.z, 0.f),
            glm::vec4(0.f, 0.f, 0.f, 1.f)
        );
    glm::mat4 res =  rotation * translation;
    return res;
}

glm::mat4 Camera::Projection()
{
    float tan = std::tan(std::acos(-1) * fov /180.f / 2.f);
    // float tan = std::tan(fov/2.f);
    return glm::mat4(
                glm::vec4(1/(ratio * tan), 0.f, 0.f, 0.f),
                glm::vec4(0.f, 1/tan, 0.f, 0.f),
                glm::vec4(0.f, 0.f, far/(far-near), 1.f),
                glm::vec4(0.f, 0.f, -far*near/(far-near), 0.f)
            );
}

void Camera::TranslateForward(float dis)
{
    worldPos += glm::vec3(forward.x, forward.y, forward.z) * dis;
}

void Camera::TranslateRight(float dis)
{
    worldPos += glm::vec3(right.x, right.y, right.z) * dis;
}

void Camera::TranslateUp(float dis)
{
    worldPos += glm::vec3(up.x, up.y, up.z) * dis;
}

void Camera::RotateAboutForward(float angle)
{
    float r = std::acos(-1) * angle /180.f;
    glm::mat4 rot = glm::rotate(r, glm::vec3(forward.x, forward.y, forward.z));
    right = rot * right;
    up = rot * up;
}

void Camera::RotateAboutRight(float angle)
{
    float r = std::acos(-1) * angle /180.f;
    glm::mat4 rot = glm::rotate(r, glm::vec3(right.x, right.y, right.z));
    forward = rot * forward;
    up = rot * up;
}

void Camera::RotateAboutUp(float angle)
{
    float r = std::acos(-1) * angle /180.f;
    glm::mat4 rot = glm::rotate(r, glm::vec3(up.x, up.y, up.z));
    forward = rot * forward;
    right = rot * right;
}
