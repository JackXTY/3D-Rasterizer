#ifndef SEGMENT_H
#define SEGMENT_H

#include <glm/glm.hpp>

class Segment
{
public:
    Segment(glm::vec4 point0, glm::vec4 point1);

    bool GetIntersection(int y, float *x);

    glm::vec4 p0;
    glm::vec4 p1;
    float slope;
};

#endif // SEGMENT_H
