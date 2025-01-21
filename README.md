# 3d-collision-system
WIP 3D Collision System (Might not finish)<br>
## Format Specs
Collision data is stored as a 16-bit integer type, zero or one unsigned 16-bit integer offsets, and zero or more 32-bit floating point numbers. All are stored as big-endian.  
The two most significant bits will determine when the collision check succeeds. If the most significant bit is set, the collision check will succeed when the difference between the plane and the point is positive (I.E. for a 3D plane, it would succeed when above the plane); if the most significant bit is *not* set, the 16-bit integer offset is used to jump ahead a that number of bytes in the file in case the difference between the plane and the point is positive. If the second most significant bit is set, the collision check will succeed when the difference between the plane and the point is negative (I.E. for a 3D plane, it would succeed when below the plane); if the second most significant bit is *not* set, the immediately following data is used to read annother piece of collision data.  
If a collision is exactly on the plane, it will assume the difference is negative.  
The third most significant bit decides where the 16-bit integer offset is present relative to the parameters of the collision type. If it is set, the offset will be after the parameters; if it is not set, the offset will be before the parameters. If the most significant bit is set, this bit is ignored as the offset will not be present. This should only be used to align the parameters to 32-bit boundaries to avoid trying to read from misaligned memory.  
The following collision types are defined:
- 0bXXX0000000000000
  - Basic 3D Plane Collision
  - ax + by + cz + m
  - 4 Parameters:
    - a
    - b
    - c
    - m
- 0bXXX0000000000001
  - Basic 2D Plane Collision
  - ax + by + m
  - 3 Parameters:
    - a
    - b
    - m
- 0bXXX0000000000010
  - Immediate Failure
  - Immediately returns that there is no collision
- 0bXXX0000000000011
  - Immediate Success
  - Immediately returns that there is a collision
