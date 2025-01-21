#include "collision.h"
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <iostream>

// Define simplified value types
#define u16 uint16_t
#define u32 uint32_t
#define f32 float

#define get_u16 ntohs(*((u16*) (data + loc)))
#define inc_u16 loc += sizeof(u16)
#define get_u32 ntohl(*((u32*) (data + loc)))
#define inc_u32 loc += sizeof(u32)

namespace hailLib {
namespace collision {

bool check(float x, float y, float z, void* collisionData) {
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
                if (a < x) {
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
                if (a < y) {
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
                if (a < z) {
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
                if (a * x + b * y > c) {
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
                if (a * y + b * z > c) {
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
                if (a * x + b * z > c) {
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
                if (a * x + b * y + z * c > d) {
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
