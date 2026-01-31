///////////////////////////////////////////////////////////////////////
// Geometric objects (vec3s, vec3s, Planes, ...) and operations.
////////////////////////////////////////////////////////////////////////

#include "geomlib.h"
#include <vector>
#include <cassert>
#include <float.h> // FLT_EPSILON

////////////////////////////////////////////////////////////////////////
// Distance methods
////////////////////////////////////////////////////////////////////////

// Return the distance from a point to a line.
float Distance(const vec3& point, const Line& line)
{
    throw Unimplemented();      // #1
}

// Return the distance from a point to a plane.
float Distance(const vec3& point, const Plane& plane)
{
    throw Unimplemented();      // #2
}

////////////////////////////////////////////////////////////////////////
// Containment methods
////////////////////////////////////////////////////////////////////////

// Determines if point (known to be on a line) is contained within a segment.
bool Segment::contains(const vec3& point) const
{
    throw Unimplemented();      // #3
}

// Determines if point (known to be on a line) is contained within a ray.
bool Ray::contains(const vec3& point, float *rt) const
{
    throw Unimplemented();      // #4
}

// Determines if point is contained within a box.
bool Box::contains(const vec3& point) const
{
    throw Unimplemented();      // #5
}

// Determines if point (known to be on a plane) is contained within a triangle.
bool Triangle::contains(const vec3& point) const
{
    throw Unimplemented();      // #6
}

////////////////////////////////////////////////////////////////////////
// Intersects functions
// In the following Intersects function these rules apply:
//
// * Most test are to determine if a *unique* solution exists. (Or in
//   some cases up to two intersection points exist.)  Parallel
//   objects have either zero or infinitely many solutions and so
//   return false.
//
// * If a unique solution exists, a function value of true is
//   returned.  (Or in the cases where several solutions can exist,
//   the number of intersection parameters are returned.)
//
// * If a unique solution does exist, the calling program may provide
//   a memory location into which the intersection parameter can be
//   returned.  Such pointer may be NULL to indicate that the
//   intersection parameter is not to be returned.
//
////////////////////////////////////////////////////////////////////////

// Determines if  line and plane have a unique intersection.  
// If true and t is not NULL, returns intersection parameter.
bool Intersects(const Line& line, const Plane& plane, float *rt)
{
    throw Unimplemented();      // #7
}

// Determines if  segment and plane have a unique intersection.  
// If true and rt is not NULL, returns intersection parameter.
bool Intersects(const Segment& seg, const Plane& plane, float *rt)
{
    throw Unimplemented();      // #8
}

// Determines if  ray and triangle have a unique intersection.  
// If true and rt is not NULL, returns intersection parameter.
bool AIntersects(const Ray& ray, const Triangle& tri, float *rt, float *ru, float *rv)
{
    throw Unimplemented();      // #9
}
bool Intersects(const Ray& ray, const Triangle& tri, float *rt, float *ru, float *rv)
{
    float t, u, v;
    
    bool r = AIntersects(ray, tri, &t, &u, &v);

    // printf("TestRayTriangle(%d, %f, %f, %f, vec3(%f, %f, %f), vec3(%f, %f, %f), vec3(%f, %f, %f), vec3(%f, %f, %f), vec3(%f, %f, %f));\n",
    //        r, t, u, v,
    //        ray.origin.x, ray.origin.y, ray.origin.z,
    //        ray.direction.x, ray.direction.y, ray.direction.z,
    //        tri.points[0].x, tri.points[0].y, tri.points[0].z,
    //        tri.points[1].x, tri.points[1].y, tri.points[1].z,
    //        tri.points[2].x, tri.points[2].y, tri.points[2].z);
    
    if (rt) *rt = t;
    if (ru) *ru = u;
    if (rv) *rv = v;
    
    return r;
}

// Determines if  segment and triangle have a unique intersection.  
// If true and rt is not NULL, returns intersection parameter.
bool Intersects(const Segment& seg, const Triangle& tri, float *rt)
{
    throw Unimplemented();      // #10
}

// Determines if  ray and sphere intersect.  
// If so and rt is not NULL, returns intersection parameter.
bool Intersects(const Ray& ray, const Sphere& sphere, float *rt)
{
    throw Unimplemented();      // #11

}

// Determines if  ray and AABB intersect.  
// If so and rt is not NULL, returns intersection parameter.
bool Intersects(const Ray& ray, const Box& box, float *rt)
{
    throw Unimplemented();      // #12
}

// Determines if  triangles intersect.  
// If parallel, returns false. (This may be considered misleading.)
// If true and rpoint is not NULL, returns two edge/triangle intersections.
int Intersects(const Triangle& tri1, const Triangle& tri2,
			   std::pair<vec3, vec3> *rpoints)
{
    throw Unimplemented();      // #13

}

////////////////////////////////////////////////////////////////////////
// Geometric relationships
////////////////////////////////////////////////////////////////////////

// Compute angle between two geometric entities (in radians;  use acos)
float AngleBetween(const Plane& plane1, const Plane& plane2)
{
    throw Unimplemented();      // #14
}

// Compute angle between two geometric entities (in radians;  use acos)
float AngleBetween(const Line& line1, const Line& line2)
{
    throw Unimplemented();      // #15
}

// Compute angle between two geometric entities (in radians;  use acos)
float AngleBetween(const Line& line, const Plane& plane)
{
    throw Unimplemented();      // #16
}

// Determine if two lines are coplanar
bool Coplanar(const Line& line1, const Line& line2)
{
    throw Unimplemented();      // #17
}

bool Perpendicular(const vec3& v1, const vec3& v2)
{
    throw Unimplemented();      // #18
}

// Determine if two vectors are parallel.
bool Parallel(const vec3& v1, const vec3& v2)
{
    throw Unimplemented();      // #19
}

// Determine if two geometric entities are parallel.
bool Parallel(const Line& line1, const Line& line2)
{
    throw Unimplemented();      // #20
}

// Determine if two geometric entities are parallel.
bool Parallel(const Line& line, const Plane& plane)
{
    throw Unimplemented();      // #21
}

// Determine if two geometric entities are parallel.
bool Parallel(const Plane& plane1, const Plane& plane2)
{
    throw Unimplemented();      // #22
}

// Determine if two geometric entities are perpendicular.
bool Perpendicular(const Line& line1, const Line& line2)
{
    throw Unimplemented();      // #23
}

// Determine if two geometric entities are perpendicular.
bool Perpendicular(const Line& line, const Plane& plane)
{
    throw Unimplemented();      // #24
}

// Determine if two geometric entities are perpendicular.
bool Perpendicular(const Plane& plane1, const Plane& plane2)
{
    throw Unimplemented();      // #25
}
