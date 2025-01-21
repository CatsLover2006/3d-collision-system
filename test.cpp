#include <criterion/criterion.h>
#include "collision.h"

using namespace hailLib::collision;

unsigned char collision_data_immediate_success[] = {0x8, 0x3};
unsigned char collision_data_immediate_failure[] = {0x8, 0x2};
unsigned char collision_data_planar_x[] = {0x50, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // x-plane of 5
unsigned char collision_data_planar_y[] = {0x54, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // y-plane of 5
unsigned char collision_data_planar_z[] = {0x58, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // z-plane of 5
unsigned char collision_data_xy_plane[] = {0x40, 0x1, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0x10, 0x11, 0x27, 0x8, 0x2}; // 5x + 4x < 2.2510468959808349609375
unsigned char collision_data_yz_plane[] = {0x40, 0x2, 0x0, 0x0, 0x3e, 0x19, 0x7d, 0x62, 0x3f, 0x8c, 0x9b, 0xf3, 0x40, 0x10, 0x11, 0x27, 0x8, 0x2}; // 0.1498923599720001220703125y + 1.09850919246673583984375z < 2.2510468959808349609375

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

Test(xy_plane, test) {
    cr_expect(check(0, 0, 0, (void*)collision_data_xy_plane));
    cr_expect(check(0, 0.562761723995208740234375, 0, (void*)collision_data_xy_plane));
    cr_expect(!check(0, 0.6, 0, (void*)collision_data_xy_plane));
    cr_expect(!check(0.25, 0.3, 0, (void*)collision_data_xy_plane));
    cr_expect(check(0, 0, 5, (void*)collision_data_xy_plane));
}

Test(yz_plane, test) {
    cr_expect(check(0, 0, 0, (void*)collision_data_yz_plane));
    cr_expect(check(0, 15.01775605108, 0, (void*)collision_data_yz_plane));
    cr_expect(!check(0, 17, 0, (void*)collision_data_yz_plane));
    cr_expect(!check(0, 15, 1, (void*)collision_data_yz_plane));
    cr_expect(check(0, 0, 2, (void*)collision_data_yz_plane));
    cr_expect(check(1, 0, 2, (void*)collision_data_yz_plane));
}

Test(xz_plane, test) { // TODO: Make good test (X-Z Plane)
    cr_assert(0, "Test data not finished; XZ Plane");
}

Test(xyz_plane, test) { // TODO: Make good test (3D Plane)
    cr_assert(0, "Test data not finishedl; 3D Plane");
}

Test(compound, test) { // TODO: Make good test (Compound data)
    cr_assert(0, "Test data not finished; Compound Data");
}
