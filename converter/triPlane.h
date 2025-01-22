/**
 *  @file triPlane.h
 *
 *  @author Half-Qilin AKA Hail AKA CatsLover2006
 */

#ifndef HAIL_LIB_COLLISIONSYS_CONVERTER_TRIPLANE_H
#define HAIL_LIB_COLLISIONSYS_CONVERTER_TRIPLANE_H

#include "../point.h"

namespace hailLib {
namespace collision {
struct triangle {
    point p1, p2, p3;
};
struct plane {
    float a, b, c, m;
};

plane convert(triangle tri);
    
}
}

#endif
