#include "segment.h"
#include <cmath>

Segment::Segment(glm::vec4 point0, glm::vec4 point1) :
    p0(point0), p1(point1),
    slope(
        point0.x==point1.x ? 0 : (point1.y-point0.y)/(point1.x-point0.x)
    )
{}

bool Segment::GetIntersection(int y, float *x)
{
    if(y > std::max(p0.y, p1.y) ||y < std::min(p0.y, p1.y) || p0.y == p1.y)
    {
        return false;
    }
    if(slope == 0)
    {
        *x = p0.x;
    }
    else
    {
        //slope = p1.y - y / p1.x - *x
        *x = p1.x - (p1.y - (float)y)/slope;
    }

    return true;
}
