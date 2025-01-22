/**
 *  @file collision.h
 *
 *  @author Half-Qilin AKA Hail AKA CatsLover2006
 */

#ifndef HAIL_LIB_COLLISIONSYS_H
#define HAIL_LIB_COLLISIONSYS_H

#include "point.h"

namespace hailLib {
namespace collision {

/**
 * Checks if a point is within collision data
 * @param x x-value of point
 * @param y y-value of point
 * @param z z-value of point
 * @param collisionData pointer to the start of collision data
 */
bool check(point p, void* collisionData);

}
}

#endif
