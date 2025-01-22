#include <criterion/criterion.h>
#include "point.h"
#include "collision.h"

using namespace hailLib::collision;

unsigned char collision_data_immediate_success[] = {0x8, 0x3};
unsigned char collision_data_immediate_failure[] = {0x8, 0x2};
unsigned char collision_data_planar_x[] = {0x50, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // x-plane of 5
unsigned char collision_data_planar_y[] = {0x54, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // y-plane of 5
unsigned char collision_data_planar_z[] = {0x58, 0x0, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x8, 0x2}; // z-plane of 5
unsigned char collision_data_xy_plane[] = {0x40, 0x1, 0x0, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x40, 0x80, 0x0, 0x0, 0x40, 0x10, 0x11, 0x27, 0x8, 0x2}; // 5x + 4x < 2.2510468959808349609375
unsigned char collision_data_yz_plane[] = {0x40, 0x2, 0x0, 0x0, 0x3e, 0x19, 0x7d, 0x62, 0x3f, 0x8c, 0x9b, 0xf3, 0x40, 0x10, 0x11, 0x27, 0x8, 0x2}; // 0.1498923599720001220703125y + 1.09850919246673583984375z < 2.2510468959808349609375
unsigned char collision_data_cliff[] = {0x10, 0x0, 0x0, 0xa, 0x40, 0xa0, 0x0, 0x0, 0x54, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x2, 0x74, 0x0, 0x40, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x2}; // cliff at x=5; if below x=5, y=0 is height; else, y=5 is height

Test(immediate_success, test) {
    cr_expect(check((point){0, 0, 0}, (void*)collision_data_immediate_success));
    cr_expect(check((point){9, 3, 1}, (void*)collision_data_immediate_success));
    cr_expect(check((point){69, 420, 69420}, (void*)collision_data_immediate_success));
}

Test(immediate_failure, test) {
    cr_expect(!check((point){0, 0, 0}, (void*)collision_data_immediate_failure));
    cr_expect(!check((point){9, 3, 1}, (void*)collision_data_immediate_failure));
    cr_expect(!check((point){69, 420, 69420}, (void*)collision_data_immediate_failure));
}

Test(x_plane, test) {
    cr_expect(check((point){0, 0, 0}, (void*)collision_data_planar_x));
    cr_expect(check((point){5, 0, 0}, (void*)collision_data_planar_x));
    cr_expect(!check((point){6, 0, 0}, (void*)collision_data_planar_x));
    cr_expect(check((point){5, 5, 5}, (void*)collision_data_planar_x));
}

Test(y_plane, test) {
    cr_expect(check((point){0, 0, 0}, (void*)collision_data_planar_y));
    cr_expect(check((point){0, 5, 0}, (void*)collision_data_planar_y));
    cr_expect(!check((point){0, 6, 0}, (void*)collision_data_planar_y));
    cr_expect(check((point){5, 5, 5}, (void*)collision_data_planar_y));
}

Test(z_plane, test) {
    cr_expect(check((point){0, 0, 0}, (void*)collision_data_planar_z));
    cr_expect(check((point){0, 0, 5}, (void*)collision_data_planar_z));
    cr_expect(!check((point){0, 0, 6}, (void*)collision_data_planar_z));
    cr_expect(check((point){5, 5, 5}, (void*)collision_data_planar_z));
}

Test(xy_plane, test) {
    cr_expect(check((point){0, 0, 0}, (void*)collision_data_xy_plane));
    cr_expect(check((point){0, 0.562761723995208740234375, 0}, (void*)collision_data_xy_plane));
    cr_expect(!check((point){0, 0.6, 0}, (void*)collision_data_xy_plane));
    cr_expect(!check((point){0.25, 0.3, 0}, (void*)collision_data_xy_plane));
    cr_expect(check((point){0, 0, 5}, (void*)collision_data_xy_plane));
}

Test(yz_plane, test) {
    cr_expect(check((point){0, 0, 0}, (void*)collision_data_yz_plane));
    cr_expect(check((point){0, 15.01775605108, 0}, (void*)collision_data_yz_plane));
    cr_expect(!check((point){0, 17, 0}, (void*)collision_data_yz_plane));
    cr_expect(!check((point){0, 15, 1}, (void*)collision_data_yz_plane));
    cr_expect(check((point){0, 0, 2}, (void*)collision_data_yz_plane));
    cr_expect(check((point){1, 0, 2}, (void*)collision_data_yz_plane));
}

Test(xz_plane, test) { // TODO: Make good test (X-Z Plane)
    cr_assert(0, "Test data not finished; XZ Plane");
}

Test(xyz_plane, test) { // TODO: Make good test (3D Plane)
    cr_assert(0, "Test data not finished; 3D Plane");
}

Test(small_compound, test) {
    cr_expect(check((point){0, 0, 0}, (void*)collision_data_cliff));
    cr_expect(!check((point){0, 4, 0}, (void*)collision_data_cliff));
    cr_expect(check((point){6, 4, 0}, (void*)collision_data_cliff));
    cr_expect(!check((point){6, 7, 0}, (void*)collision_data_cliff));
    cr_expect(check((point){6, 0, 0}, (void*)collision_data_cliff));
}

Test(large_compound, test) { // TODO: Make good test (Big Compound Data)
    cr_assert(0, "Test data not finished; Big Compound Data");
}
