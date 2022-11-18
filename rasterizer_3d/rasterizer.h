#pragma once
#include <polygon.h>
#include <QImage>
#include <camera.h>

class Rasterizer
{
private:
    //This is the set of Polygons loaded from a JSON scene file
    std::vector<Polygon> m_polygons;
public:
    Rasterizer(const std::vector<Polygon>& polygons);
    QImage RenderScene();
    void ClearScene();

    Camera cam;
    int AAratio = 1;
    bool renderWireframe = false;
};

std::array<float, 4> GetBoundingBox(const std::array<glm::vec4, 3>& arr, const unsigned int AAratio);

QRgb GetColor(int x, int y, const std::array<glm::vec4, 3>& arr, const std::array<glm::vec3, 3>& colorArr);

float GetArea(const std::array<glm::vec4, 3>& arr);

glm::vec4 BaryInterpolationWithZ(const std::array<glm::vec4, 3>& arr, const std::array<float, 4>& zValues, const std::array<float, 4>& areas);

glm::vec2 BaryInterpolationWithZ(const std::array<glm::vec2, 3>& arr, const std::array<float, 4>& zValues, const std::array<float, 4>& areas);
