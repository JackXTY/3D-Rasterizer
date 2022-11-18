#include "rasterizer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "segment.h"
#include "camera.h"

Rasterizer::Rasterizer(const std::vector<Polygon>& polygons)
    : m_polygons(polygons), cam(Camera())
{}

QImage Rasterizer::RenderScene()
{
    QImage hr(512*AAratio, 512*AAratio, QImage::Format_RGB32);
    // Fill the image with black pixels.
    // Note that qRgb creates a QColor,
    // and takes in values [0, 255] rather than [0, 1].
    hr.fill(qRgb(0.f, 0.f, 0.f));

    // TODO: Complete the various components of code that make up this function.
    // It should return the rasterized image of the current scene.

    // Make liberal use of helper functions; writing your rasterizer as one
    // long RenderScene function will make it (a) hard to debug and
    // (b) hard to write without copy-pasting. Also, Adam will be sad when
    // he reads your code.

    // Also! As per the style requirements for this assignment, make sure you
    // use std::arrays to store things like your line segments, Triangles, and
    // vertex coordinates. This lets you easily use loops to perform operations
    // on your scene components, rather than copy-pasting operations three times
    // each!

    float initZVal = 99.f;
    if(renderWireframe){ initZVal = 0.f; }
    std::vector<float> zBuffer(512*512*AAratio*AAratio, initZVal);


    for(const Polygon& poly: m_polygons)
    {
        for(unsigned int i = 0; i < poly.m_tris.size(); i++)
        {
            //Triangle& tri = poly.m_tris[i];
            std::array<Vertex, 3> vertices = {
                poly.m_verts[poly.m_tris[i].m_indices[0]],
                poly.m_verts[poly.m_tris[i].m_indices[1]],
                poly.m_verts[poly.m_tris[i].m_indices[2]]
            };

            std::array<glm::vec2, 3> uvArr = {vertices[0].m_uv, vertices[1].m_uv, vertices[2].m_uv};
            std::array<glm::vec4, 3> normalArr = {vertices[0].m_normal, vertices[1].m_normal, vertices[2].m_normal};
            std::array<glm::vec4, 3> worldPosArr = {vertices[0].m_pos, vertices[1].m_pos, vertices[2].m_pos};
            std::array<glm::vec4, 3> posArr;
            for(int i = 0; i < 3; i++)
            {
                posArr[i] = cam.Projection() * cam.View() * worldPosArr[i];
                posArr[i] /= posArr[i].w;
                posArr[i].w = 1.f;
                posArr[i].x = (posArr[i].x + 1) * 256.0f * AAratio;
                posArr[i].y = (1 - posArr[i].y) * 256.0f * AAratio;
            }
            std::array<float, 4> bbox = GetBoundingBox(posArr, AAratio);
            std::array<Segment, 3> segArr = {Segment(posArr[0], posArr[1]), Segment(posArr[1], posArr[2]), Segment(posArr[2], posArr[0])};
            std::array<float, 4> zValues = {posArr[0].z, posArr[1].z, posArr[2].z, 0.f};

//            glm::vec3 triNormal = glm::cross(glm::vec3(worldPosArr[1]-worldPosArr[0]), glm::vec3(worldPosArr[2]-worldPosArr[0]));
//            glm::vec3 tangent = glm::cross(glm::vec3(0.f, 1.f, 0.f), triNormal);
//            glm::vec3 biTangent = glm::cross(triNormal, tangent);
//            glm::mat4 normalTrans = glm::mat4(glm::vec4(tangent, 0.f), glm::vec4(biTangent, 0.f), glm::vec4(triNormal, 0.f), glm::vec4(0.f, 0.f, 0.f, 1.f));

            int minY = std::max((int) std::ceil(bbox[2]), 0);
            int maxY = std::min((int) std::floor(bbox[3]), 512 * AAratio - 1);

            for(int y = minY; y <= maxY; y++)
            {
                float xLeft = 512.f * AAratio;
                float xRight = 0.f;

                float tempX;
                for(int j = 0; j<3; j++)
                {
                    if(segArr[j].GetIntersection(y, &tempX))
                    {
                        xLeft = std::min(xLeft, tempX);
                        xRight = std::max(xRight, tempX);
                    }
                }

                int minX = (int) std::max(std::ceil(xLeft), 0.f);
                int maxX = (int) std::min(std::floor(xRight), 512.f * AAratio - 1.f);

                if(renderWireframe)
                {
                    std::vector<int> xVals = {minX, maxX};
                    // TODO: add minY & maxY
                    if(y == minY || y == maxY)
                    {
                        for(int x = minX+1; x < maxX; x++)
                        {
                            xVals.push_back(x);
                        }
                    }

                    for(int t = 0; t < xVals.size(); t++)
                    {
                        int x = xVals[t];
                        glm::vec4 pos = glm::vec4(x, y, 0.f, 0.f);

                        std::array<float, 4> areas;
                        std::array<glm::vec4, 3> tarr;
                        tarr[0] = pos;
                        areas[3] = GetArea(posArr);
                        for(int i = 0; i < 3; i++)
                        {
                            tarr[1] = posArr[(i+1)%3];
                            tarr[2] = posArr[(i+2)%3];
                            areas[i] = GetArea(tarr);
                        }
                        QRgb color = GetColor(x, y, posArr, {vertices[0].m_color, vertices[1].m_color, vertices[2].m_color});
                        if(zBuffer[x+y*AAratio*512.f] > 0.f)
                        {
                            QRgb oriColor = hr.pixel(x, y);
                            glm::vec3 cVec = glm::vec3(qRed(oriColor), qGreen(oriColor), qBlue(oriColor));
                            cVec = zBuffer[x+y*AAratio*512.f] * cVec + glm::vec3(qRed(color), qGreen(color), qBlue(color));
                            cVec /= (zBuffer[x+y*AAratio*512.f]+1.f);
                            color = qRgb(cVec.x, cVec.y, cVec.z);
                        }
                        zBuffer[x+y*AAratio*512.f]  += 1.f;
                        hr.setPixel(x, y, color);
                    }
                    continue;
                }

                for(int x = minX; x <= maxX; x++)
                {
                    glm::vec4 pos = glm::vec4(x, y, 0.f, 0.f);

                    std::array<float, 4> areas;
                    std::array<glm::vec4, 3> tarr;
                    tarr[0] = pos;
                    areas[3] = GetArea(posArr);
                    for(int i = 0; i < 3; i++)
                    {
                        tarr[1] = posArr[(i+1)%3];
                        tarr[2] = posArr[(i+2)%3];
                        areas[i] = GetArea(tarr);
                    }

                    // ONLY for 2D
                    // float depth = poly.m_verts[poly.m_tris[i].m_indices[0]].m_pos.z;

                    pos.z = areas[3] / (areas[0]/posArr[0].z + areas[1]/posArr[1].z + areas[2]/posArr[2].z);
                    zValues[3] = pos.z;
                    if(pos.z>zBuffer[x +y *AAratio*512.f])
                    {
                        continue;
                    }
                    zBuffer[x+y*AAratio*512.f] = pos.z;

                    glm::vec2 uv = BaryInterpolationWithZ(uvArr, zValues, areas);
                    uv.x = std::clamp(uv.x, 0.f, 1.f);
                    uv.y = std::clamp(uv.y, 0.f, 1.f);

                    glm::vec4 normal = BaryInterpolationWithZ(normalArr, zValues, areas);
                    if(poly.mp_normalMap != nullptr)
                    {
                        // do normal mapping
                        glm::vec3 localNormal = (GetImageColor(uv, poly.mp_normalMap)
                                                 / 255.f - glm::vec3(0.5f, 0.5f, 0.5f))*2.f;

                        //glm::vec3 triNormal = glm::cross(glm::vec3(worldPosArr[1]-worldPosArr[0]), glm::vec3(worldPosArr[2]-worldPosArr[0]));
                        glm::vec3 tangent = glm::cross(glm::vec3(0.f, 1.f, 0.f), glm::vec3(normal));
                        glm::vec3 biTangent = glm::cross(glm::vec3(normal), tangent);
                        glm::mat4 normalTrans = glm::mat4(glm::vec4(tangent, 0.f), glm::vec4(biTangent, 0.f), normal, glm::vec4(0.f, 0.f, 0.f, 1.f));

                        normal = normalTrans * glm::vec4(localNormal, 0.f);
                    }

                    glm::vec4 worldPos = BaryInterpolationWithZ(worldPosArr, zValues, areas);
                    glm::vec4 lightDir = glm::normalize(glm::vec4(cam.worldPos, 0.f) - worldPos);
                    float light = std::clamp(glm::dot(normal, lightDir) + 0.3f, 0.f, 1.f);

                    glm::vec3 lightColor = light * GetImageColor(uv, poly.mp_texture);
                    hr.setPixel(x, y, qRgb(lightColor.x, lightColor.y, lightColor.z));
                }
            }
        }
    }

    if(AAratio == 1){return hr;}
    QImage result(512, 512, QImage::Format_RGB32);
    result.fill(qRgb(0.f, 0.f, 0.f));
    for(int x = 0; x < 512; x++)
    {
        for(int y = 0; y < 512; y++)
        {
            glm::vec3 sum;
            for(int dx = 0; dx < AAratio; dx++)
            {
                for(int dy = 0; dy < AAratio; dy++)
                {
                    QRgb p = hr.pixel(x * AAratio + dx, y * AAratio + dy);
                    sum += glm::vec3(qRed(p), qGreen(p), qBlue(p));
                }
            }

            sum /= (AAratio * AAratio);
            result.setPixel(x, y, qRgb(sum.x, sum.y, sum.z));
        }
    }
    return result;
}

// return minX, maxX, minY, maxY
std::array<float, 4> GetBoundingBox(const std::array<glm::vec4, 3>& arr, unsigned int AAratio)
{
    std::array<float, 4> res = {arr[0].x, arr[0].x, arr[0].y, arr[0].y};
    for(int i = 1; i < 3; i++)
    {
        res[0] = std::min(res[0], arr[i].x);
        res[1] = std::max(res[1], arr[i].x);
        res[2] = std::min(res[2], arr[i].y);
        res[3] = std::max(res[3], arr[i].y);
    }
    res[0] = std::max(res[0], 0.f);
    res[1] = std::min(res[1], 512.f * AAratio - 1.f);
    res[2] = std::max(res[2], 0.f);
    res[3] = std::min(res[3], 511.f * AAratio - 1.f);
    return res;
}

QRgb GetColor(int x, int y, const std::array<glm::vec4, 3>& arr, const std::array<glm::vec3, 3>& colorArr)
{
    glm::vec4 p = glm::vec4(x, y, 0.f, 0.f);
    float s = GetArea(arr);
    std::array<glm::vec4, 3> tarr = {p, arr[1], arr[2]};
    float s0 = GetArea(tarr);
    tarr[1] = arr[2];
    tarr[2] = arr[0];
    float s1 = GetArea(tarr);
    tarr[1] = arr[0];
    tarr[2] = arr[1];
    float s2 = GetArea(tarr);

    glm::vec3 c =  s0/s * colorArr[0] + s1/s * colorArr[1] + s2/s * colorArr[2];
    return qRgb(std::clamp(c.x, 0.f, 255.f), std::clamp(c.y, 0.f, 255.f), std::clamp(c.z, 0.f, 255.f));
}

glm::vec4 BaryInterpolationWithZ(const std::array<glm::vec4, 3>& arr, const std::array<float, 4>& zValues, const std::array<float, 4>& areas)
{
    return (zValues[3] / areas[3]) * (arr[0] *(areas[0]/zValues[0]) + arr[1] * (areas[1]/zValues[1]) + arr[2] * (areas[2]/zValues[2]));
}

glm::vec2 BaryInterpolationWithZ(const std::array<glm::vec2, 3>& arr, const std::array<float, 4>& zValues, const std::array<float, 4>& areas)
{
    return (zValues[3] / areas[3]) * (arr[0] *(areas[0]/zValues[0]) + arr[1] * (areas[1]/zValues[1]) + arr[2] * (areas[2]/zValues[2]));
}

void Rasterizer::ClearScene()
{
    m_polygons.clear();
}

float GetArea(const std::array<glm::vec4, 3>& arr)
{
    glm::vec3 v0 = glm::vec3(arr[0].x - arr[1].x, arr[0].y - arr[1].y, 0.f);
    glm::vec3 v1 = glm::vec3(arr[2].x - arr[1].x, arr[2].y - arr[1].y, 0.f);
    return 0.5 * glm::length(glm::cross(v0, v1));
}
