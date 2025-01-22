/**
 *  @file collision.cpp
 *
 *  @author Half-Qilin AKA Hail AKA CatsLover2006
 */

#include "collision.h"
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <iostream>

#include <cfloat>

// Define simplified value types
#define u16 uint16_t
#define u32 uint32_t
#define f32 float

#define get_u16 ntohs(*((u16*) (data + loc)))
#define inc_u16 loc += sizeof(u16)
#define get_u32 ntohl(*((u32*) (data + loc)))
#define inc_u32 loc += sizeof(u32)

#if (UINT16_MAX != 65535)
#error "16 bit integer isn't 16 bits long"
#endif

#if (UINT32_MAX != 4294967295)
#error "32 bit integer isn't 32 bits long"
#endif

#if (FLT_MANT_DIG != 24 || FLT_MAX_EXP != 128)
#warning "float isn't using IEEE 754"
#endif

namespace hailLib {
namespace collision {

bool check(point p, void* collisionData) {
    char* data = (char*) collisionData;
    u16 offset;
    u16 instruction;
    u32 reader;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    size_t loc = 0;
    while (true) {
        instruction = get_u16;
        inc_u16;
        switch (instruction & 0x1FFF) {
            case 0x1000: { // Planar X
                if (!(instruction & 0x2000)) {
                    offset = get_u16;
                    inc_u16;
                }
                reader = get_u32;
                a = *(f32*)&reader;
                inc_u32;
                if (instruction & 0x2000) {
                    offset = get_u16;
                    inc_u16;
                }
                if (a < p.x) {
                    if (instruction & 0x8000) return true; // Success on top
                    loc += offset;
                } else {
                    if (instruction & 0x4000) return true; // Success on bottom
                }
                break;
            }
            case 0x1400: { // Planar Y
                if (!(instruction & 0x2000)) {
                    offset = get_u16;
                    inc_u16;
                }
                reader = get_u32;
                a = *(f32*)&reader;
                inc_u32;
                if (instruction & 0x2000) {
                    offset = get_u16;
                    inc_u16;
                }
                if (a < p.y) {
                    if (instruction & 0x8000) return true; // Success on top
                    loc += offset;
                } else {
                    if (instruction & 0x4000) return true; // Success on bottom
                }
                break;
            }
            case 0x1800: { // Planar Z
                if (!(instruction & 0x2000)) {
                    offset = get_u16;
                    inc_u16;
                }
                reader = get_u32;
                a = *(f32*)&reader;
                inc_u32;
                if (instruction & 0x2000) {
                    offset = get_u16;
                    inc_u16;
                }
                if (a < p.z) {
                    if (instruction & 0x8000) return true; // Success on top
                    loc += offset;
                } else {
                    if (instruction & 0x4000) return true; // Success on bottom
                }
                break;
            }
            case 0x0001: { // XY plane
                if (!(instruction & 0x2000)) {
                    offset = get_u16;
                    inc_u16;
                }
                reader = get_u32;
                a = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                b = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                c = *(f32*)&reader;
                inc_u32;
                if (instruction & 0x2000) {
                    offset = get_u16;
                    inc_u16;
                }
                if (a * p.x + b * p.y > c) {
                    if (instruction & 0x8000) return true; // Success on top
                    loc += offset;
                } else {
                    if (instruction & 0x4000) return true; // Success on bottom
                }
                break;
            }
            case 0x0002: { // YZ plane
                if (!(instruction & 0x2000)) {
                    offset = get_u16;
                    inc_u16;
                }
                reader = get_u32;
                a = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                b = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                c = *(f32*)&reader;
                inc_u32;
                if (instruction & 0x2000) {
                    offset = get_u16;
                    inc_u16;
                }
                if (a * p.y + b * p.z > c) {
                    if (instruction & 0x8000) return true; // Success on top
                    loc += offset;
                } else {
                    if (instruction & 0x4000) return true; // Success on bottom
                }
                break;
            }
            case 0x0003: { // XZ plane
                if (!(instruction & 0x2000)) {
                    offset = get_u16;
                    inc_u16;
                }
                reader = get_u32;
                a = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                b = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                c = *(f32*)&reader;
                inc_u32;
                if (instruction & 0x2000) {
                    offset = get_u16;
                    inc_u16;
                }
                if (a * p.x + b * p.z > c) {
                    if (instruction & 0x8000) return true; // Success on top
                    loc += offset;
                } else {
                    if (instruction & 0x4000) return true; // Success on bottom
                }
                break;
            }
            case 0x0000: { // 3D plane
                if (!(instruction & 0x2000)) {
                    offset = get_u16;
                    inc_u16;
                }
                reader = get_u32;
                a = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                b = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                c = *(f32*)&reader;
                inc_u32;
                reader = get_u32;
                d = *(f32*)&reader;
                inc_u32;
                if (instruction & 0x2000) {
                    offset = get_u16;
                    inc_u16;
                }
                if (a * p.x + b * p.y + p.z * c > d) {
                    if (instruction & 0x8000) return true; // Success on top
                    loc += offset;
                } else {
                    if (instruction & 0x4000) return true; // Success on bottom
                }
                break;
            }
            case 0x0802: // Immediate failure
                return false;
            case 0x0803: // Immediate success
                return true;
            default: // Unknown flag
                return false;
        }
    }
};

}
}
