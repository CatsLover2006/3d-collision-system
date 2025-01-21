#include <criterion/criterion.h>
#include "collision.h"

using namespace hailLib::collision;

unsigned char collision_data_immediate_success[] = {0x8, 0x3};
unsigned char collision_data_immediate_failure[] = {0x8, 0x2};
unsigned char collision_data_planar_x[] = {0x50, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // x-plane of 5
unsigned char collision_data_planar_y[] = {0x54, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // y-plane of 5
unsigned char collision_data_planar_z[] = {0x58, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // z-plane of 5

Test(immediate_success, test) {
    cr_expect(check(0, 0, 0, (void*)collision_data_immediate_success));
    cr_expect(check(9, 3, 1, (void*)collision_data_immediate_success));
    cr_expect(check(69, 420, 69420, (void*)collision_data_immediate_success));
}

Test(immediate_failure, test) {
    cr_expect(!check(0, 0, 0, (void*)collision_data_immediate_failure));
    cr_expect(!check(9, 3, 1, (void*)collision_data_immediate_failure));
    cr_expect(!check(69, 420, 69420, (void*)collision_data_immediate_failure));
}

Test(x_plane, test) {
    cr_expect(check(0, 0, 0, (void*)collision_data_planar_x));
    cr_expect(check(5, 0, 0, (void*)collision_data_planar_x));
    cr_expect(!check(6, 0, 0, (void*)collision_data_planar_x));
    cr_expect(check(5, 5, 5, (void*)collision_data_planar_x));
}

Test(y_plane, test) {
    cr_expect(check(0, 0, 0, (void*)collision_data_planar_y));
    cr_expect(check(0, 5, 0, (void*)collision_data_planar_y));
    cr_expect(!check(0, 6, 0, (void*)collision_data_planar_y));
    cr_expect(check(5, 5, 5, (void*)collision_data_planar_y));
}

Test(z_plane, test) {
    cr_expect(check(0, 0, 0, (void*)collision_data_planar_z));
    cr_expect(check(0, 0, 5, (void*)collision_data_planar_z));
    cr_expect(!check(0, 0, 6, (void*)collision_data_planar_z));
    cr_expect(check(5, 5, 5, (void*)collision_data_planar_z));
}
