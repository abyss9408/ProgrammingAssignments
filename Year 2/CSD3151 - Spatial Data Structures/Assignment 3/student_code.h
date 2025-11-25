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
#define MAIN	SCAN_LINE

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
    static int GOAL = 4.7 * million;
#endif

static int polyCount = 1;      // Produces 4*polyCount^2 triangles per ellipsoid
static int ellipsoidCount = 0; // Produces (2*ellipsoidCount+1)^2 ellipsoids
static int grndCount = 4;      // Produces 2*groundCount^2 triangles.

#include "geomlib.h"

// TreeNode struct for BVH implementation
struct TreeNode
{
    enum NodeType : uint8_t { LEAF, INTERNAL };

    NodeType type;
    Box* aabb;                    // Axis-Aligned Bounding Box for this node
    Triangle* triangle;           // Triangle data (for leaf nodes only)
    TreeNode* leftChild;          // Left child (for internal nodes)
    TreeNode* rightChild;         // Right child (for internal nodes)
    int depth;                    // Depth in the tree (for documentation)

    // Constructor for leaf node
    TreeNode(Triangle* tri, int d = 0);

    // Constructor for internal node
    TreeNode(TreeNode* left, TreeNode* right, int d = 0);

    // Destructor
    ~TreeNode();

    // Utility function to merge two AABBs
    static void MergeAABB(Box& result, const Box& box1, const Box& box2);

    // Get the surface area of this node's AABB
    float GetSurfaceArea() const;
};

class StudentCode
{
public:
    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
    bool drawDebugSegs    = 0;
	bool drawDebugTriangles = 0;
	bool drawDebugBoxes = 0;
	bool drawDebugSpheres = 0;

    // BVH visualization controls
    bool drawBVHBoxes = 0;
    int bvhDisplayLevel = 0;      // Which level to display (0 = all levels)
    int maxBVHLevels = 0;         // Maximum depth of the BVH tree

    std::vector<Segment*>  debugSegs;
	std::vector<Triangle*> debugTriangles;
	std::vector<Box*> debugBoxes;
	std::vector<Sphere*> debugSpheres;
    
    mat4 ViewInverse, ProjInverse;
    std::vector<Triangle> triangles;
    std::vector<Box> boundingBoxes;
    std::vector<Object*> objects;
	std::vector<std::vector<Triangle>> triangleByObject;

    // BVH root and statistics
    TreeNode* bvhRoot;
    int leafNodeCount;
    int minDepth, maxDepth;
    int rayBoxIntersectionCount;
    int frameCount;
    float avgRayBoxIntersections;

    // Triangle selection
    Triangle* selectedTriangle;

    StudentCode();
    ~StudentCode();

    void SetTransforms(mat4& _vi, mat4& _pi);
    void DrawGui();
    void GenerateRayTracedImage(int width, int height, float* image, vec3& lightPos);
    void Destroy();

    bool IsStepLegal(vec3 eye, vec3& direction, float step);
    bool IsStepLegalBVH(const Segment& movementSegment, TreeNode* node);

    void ObjectTriangles(std::vector<vec4>& Pnt,
                         std::vector<vec3>&  Nrm,
                         std::vector<ivec3>& Tri,
                         mat4& iTr,
                         Object* obj);
    void EndOfTriangles();

    // BVH Construction and Traversal
    TreeNode* BuildBVH(std::vector<TreeNode*>& leafNodes);
    TreeNode* BuildBVHRecursive(std::vector<TreeNode*>& nodes, int depth);
    int GetLargestExtentAxis(const std::vector<TreeNode*>& nodes);
    void CalculateBVHStatistics(TreeNode* node, int depth = 0);

    // Triangle selection with BVH
    Triangle* SelectTriangleAtScreenCenter();
    Triangle* SelectTriangleWithBVH(const Ray& ray, TreeNode* node, float& closestT);

    void DrawDebug(unsigned int programId);
    void DrawBVHLevel(unsigned int programId, TreeNode* node, int currentLevel, int targetLevel, vec3 color);

    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
    void DrawDebug(unsigned int programId, Segment* seg, vec3 color = vec3(1, 1, 0));;
	void DrawDebug(unsigned int programId, Triangle* tri, vec3 color = vec3(1, 1, 0));
    void DrawDebug(unsigned int programId, Box* tri, vec3 color = vec3(1, 1, 0));
    void DrawDebug(unsigned int programId, Sphere* tri, vec3 color = vec3(1, 1, 0));
};
    
#endif        
