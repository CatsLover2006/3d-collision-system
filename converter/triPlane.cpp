/**
 *  @file triPlane.cpp
 *
 *  @author Half-Qilin AKA Hail AKA CatsLover2006
 */

#include "triPlane.h"
#include <cmath>

namespace hailLib {
namespace collision {
plane convert(triangle tri) {
    point anchor = tri.p1;
    point point1 = {tri.p2.x - anchor.x, tri.p2.y - anchor.y, tri.p2.z - anchor.z};
    point point2 = {tri.p3.x - anchor.x, tri.p3.y - anchor.y, tri.p3.z - anchor.z};
    point crossProduct = {point1.y * point2.z - point1.z * point2.y, point1.z * point2.x - point1.x * point2.z, point1.x * point2.y - point1.y * point2.x};
    
}
}
}
