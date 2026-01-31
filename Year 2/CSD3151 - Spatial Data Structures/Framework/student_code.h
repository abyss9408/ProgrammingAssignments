#ifndef _STUDENTCODE
#define _STUDENTCODE

#define TEST_GEOMLIB 0
#define SCAN_LINE    1
#define RAY_TRACE    2   

#ifdef DEFMAIN
#define MAIN DEFMAIN
#else

// @@ Choose which one of three main programs to run.  Legal choices are:
// #define MAIN	TEST_GEOMLIB
// #define MAIN	SCAN_LINE
// #define MAIN	RAY_TRACE
#define MAIN	TEST_GEOMLIB

#endif

const int thousand = 1000;
const int million = 1000000;

// @@ TRIANGLE COUNT: Set GOAL to the (approximate) number of
// triangles you'd like for this run.  Here are some reasonable
// choices with frame rates (on my laptop) for project 2 using a
// linear list.
//static int GOAL = 100;     // > 144 FPS.
//static int GOAL = thousand;    // > 144 FPS.
//static int GOAL = 10*thousand;   // > 144 FPS.
//static int GOAL = 100*thousand;  // Runs at 82 FPS
//static int GOAL = million; // ~9 FPS
//static int GOAL = 2*million; // ~5 FPS
//static int GOAL = 10*million; // < 1 FPS.

#if MAIN==RAY_TRACE
    static int GOAL = 100;
#else
    static int GOAL = 10*thousand;
#endif

static int polyCount = 1;      // Produces 4*polyCount^2 triangles per ellipsoid
static int ellipsoidCount = 0; // Produces (2*ellipsoidCount+1)^2 ellipsoids
static int grndCount = 4;      // Produces 2*groundCount^2 triangles.

#include "geomlib.h"

class StudentCode {
 public:
    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
    bool drawDebugSegs    = 0;
    std::vector<Segment*>  debugSegs;
    
    mat4 ViewInverse, ProjInverse;
    std::vector<Triangle> triangles;
    std::vector<Object*> objects;

    StudentCode();

    void SetTransforms(mat4& _vi, mat4& _pi);
    void DrawGui();
    void GenerateRayTracedImage(int width, int height, float* image, vec3& lightPos);
    void Destroy();

    bool IsStepLegal(vec3 eye, vec3& direction, float step);

    void ObjectTriangles(std::vector<vec4>& Pnt,
                         std::vector<vec3>&  Nrm,
                         std::vector<ivec3>& Tri,
                         mat4& iTr,
                         Object* obj);
    void EndOfTriangles();

    void DrawDebug(unsigned int programId);

    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
    void DrawDebug(unsigned int programId, Segment*  seg, vec3 color=vec3(1,1,0));
};
    
#endif        
