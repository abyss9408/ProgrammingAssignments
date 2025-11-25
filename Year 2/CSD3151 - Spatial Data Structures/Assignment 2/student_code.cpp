
#define _USE_MATH_DEFINES
#include <cmath>

#include "imgui.h"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#include <glu.h>                // For gluErrorString

#include <algorithm> 
#include "shader.h"
#include "object.h"
#include "student_code.h"
#include "transform.h"
#include <stdio.h>

vec3 Hdiv(const vec4& H)
{
    return H.xyz()/H.w;
}

////////////////////////////////////////////////////////////////////////
// This macro makes it easy to sprinkle checks for OpenGL errors
// throughout your code.  Most OpenGL calls can record errors, and a
// careful programmer will check the error status *often*, perhaps as
// often as after every OpenGL call.  At the very least, once per
// refresh will tell you if something is going wrong.
#define CHECKERROR {GLenum err = glGetError(); if (err != GL_NO_ERROR) { fprintf(stderr, "OpenGL error (at line scene.cpp:%d): %s\n", __LINE__, gluErrorString(err)); exit(-1);} }
//
////////////////////////////////////////////////////////////////////////

// @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
static unsigned int segmentVao;
static unsigned int triangleVao;
static unsigned int boxVao;
static unsigned int sphereVao;

void Setup(int programId, mat4& mtr, vec3& color)
{
    const int debugId = 5;
    
    int loc = glGetUniformLocation(programId, "objectId");
    glUniform1i(loc, debugId);
    
    loc = glGetUniformLocation(programId, "diffuse");
    glUniform3fv(loc, 1, &color[0]);
    
    loc = glGetUniformLocation(programId, "ModelTr");
    glUniformMatrix4fv(loc, 1, GL_FALSE, Pntr(mtr));
    
}

unsigned int VaoFromPoints(std::vector<vec4> Pnt, std::vector<int> Ind)
{
    CHECKERROR;
    //printf("VaoFromPoints %ld %ld\n", Pnt.size(), Ind.size());
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint Pbuff;
    glGenBuffers(1, &Pbuff);
    glBindBuffer(GL_ARRAY_BUFFER, Pbuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*Pnt.size(),
                 &Pnt[0][0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint Ibuff;
    glGenBuffers(1, &Ibuff);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ibuff);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*Ind.size(),
                 &Ind[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    CHECKERROR;
    return vaoID;
}

StudentCode::StudentCode()
{
    CHECKERROR;
    
    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.)
    // This creates a VAO for a generic segment from (0,0,0) to (1,1,1).
    std::vector<vec4> segVerexList = {vec4(0,0,0,1), vec4(1,1,1,1)};
    std::vector<int> segIndexList = {0,1};
    segmentVao = VaoFromPoints(segVerexList, segIndexList);

    // Triangle VAO (unit triangle)
    std::vector<vec4> triVertexList = {
        vec4(0,0,0,1), vec4(1,0,0,1), vec4(0,1,0,1)
    };
    std::vector<int> triIndexList = { 0, 1, 2 };  // Wireframe edges
    triangleVao = VaoFromPoints(triVertexList, triIndexList);

    // Box VAO (unit cube wireframe)
    std::vector<vec4> boxVertexList = {
        // Bottom face
        vec4(-1,-1,-1,1), vec4(1,-1,-1,1), vec4(1,1,-1,1), vec4(-1,1,-1,1),
        // Top face  
        vec4(-1,-1,1,1), vec4(1,-1,1,1), vec4(1,1,1,1), vec4(-1,1,1,1)
    };
    std::vector<int> boxIndexList = {
        // Bottom face
        0,1, 1,2, 2,3, 3,0,
        // Top face
        4,5, 5,6, 6,7, 7,4,
        // Vertical edges
        0,4, 1,5, 2,6, 3,7
    };
    boxVao = VaoFromPoints(boxVertexList, boxIndexList);

    // Sphere VAO
    std::vector<vec4> sphereVertexList;
    std::vector<int> sphereIndexList;
    
	// Create vertices for a sphere wireframe
    int segments = 48;

    // XY circle (around Z axis)
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        sphereVertexList.push_back(vec4(cos(angle), sin(angle), 0, 1));
    }

    // XZ circle (around Y axis) 
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        sphereVertexList.push_back(vec4(cos(angle), 0, sin(angle), 1));
    }

    // YZ circle (around X axis)
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        sphereVertexList.push_back(vec4(0, cos(angle), sin(angle), 1));
    }

    // Create indices for the 3 circles
    for (int circle = 0; circle < 3; ++circle) {
        int offset = circle * segments;
        for (int i = 0; i < segments; ++i) {
            sphereIndexList.push_back(offset + i);
            sphereIndexList.push_back(offset + (i + 1) % segments);
        }
    }

    sphereVao = VaoFromPoints(sphereVertexList, sphereIndexList);
}

void StudentCode::SetTransforms(mat4& _vi, mat4& _pi)
{
    ViewInverse = _vi;
    ProjInverse = _pi;
}

bool StudentCode::IsStepLegal(vec3 eye, vec3& direction, float step)
{
	// Create the proposed movement segment
	vec3 endPoint = eye + direction * step;
	Segment movementSegment(eye, endPoint);

    for (const Triangle& triangle : triangles)
    {
        // Check if the segment intersects with any triangle
        float t;
        if (Intersects(movementSegment, triangle, &t))
        {
            // If it does, the step is not legal
            return false;
        }
    }
	return true; // If no intersections, the step is legal
}

void StudentCode::ObjectTriangles(std::vector<vec4>& Pnt,  // vertex array
                                  std::vector<vec3>&  Nrm, // Triangle index array
                                  std::vector<ivec3>& Tri, // Triangle index array
                                  mat4& iTr,               // instance transformation.
                                  Object* obj              // Object containing this triangle)
                                  )
{
    // @@ Multiple calls to this procedure (on per object) gives you
    // access to all the triangles in the scene.  You must store these
    // triangles in some (spatial) data structure.  Other calls will
    // cause you to traverse this structure of triangles to answer
    // various queries.

    // As a start, here is how to access the world coordinate vertices
    // of every triangle:
    //
    // for (ivec3 tri : Tri) {
    //     vec3 P0 = (iTr*Pnt[tri[0]]).xyz();
    //     vec3 P1 = (iTr*Pnt[tri[1]]).xyz();
    //     vec3 P2 = (iTr*Pnt[tri[2]]).xyz();
    //     ... do something with Triangle(P0,P1,P2) ... }
	objects.push_back(obj);

	std::vector<Triangle> objectTriangles;

	// Process each triangle in this object
    for (const ivec3& tri : Tri)
    {
		vec3 P0 = (iTr * Pnt[tri[0]]).xyz();
		vec3 P1 = (iTr * Pnt[tri[1]]).xyz();
		vec3 P2 = (iTr * Pnt[tri[2]]).xyz();

        // Create a triangle object and store it in the triangles vector
        Triangle triangle(P0, P1, P2);
        triangles.push_back(triangle);
		objectTriangles.push_back(triangle);
    }

	triangleByObject.push_back(objectTriangles);    
}

void StudentCode::EndOfTriangles()
{
    // @@ This is called when all triangles have been passed in via
    // ObjectTriangles calls. Build your spatial data structure here.
    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.)
    printf("Triangles: %ld\n", triangles.size());
	printf("Bounding Boxes: %ld\n", boundingBoxes.size());
    printf("Objects: %ld\n", objects.size());

    debugSegs.clear();
    debugTriangles.clear();
    debugBoxes.clear();
    debugSpheres.clear();

    // 1. TRIANGLE NORMALS as debug segments
    // Use debugSegs to store normal visualization
    for (size_t i = 0; i < triangles.size(); ++i) {
        const Triangle& tri = triangles[i];

        // Calculate triangle center
        vec3 center = (tri[0] + tri[1] + tri[2]) / 3.0f;

        // Calculate normal vector
        vec3 edge1 = tri[1] - tri[0];
        vec3 edge2 = tri[2] - tri[0];
        vec3 normal = normalize(cross(edge1, edge2));

        // Create debug segment showing normal (length = 0.5 units)
        vec3 normalEnd = center + normal * 0.25f;
        debugSegs.push_back(new Segment(center, normalEnd));
    }

    // 2. PER-OBJECT TRIANGLES
    // Use debugTriangles to store one representative triangle per object
    // (or you could store all triangles and use object index to group them)
    for (size_t i = 0; i < triangles.size(); ++i)
    {
        debugTriangles.push_back(new Triangle(triangles[i]));
    }

    // 3. BOUNDING BOX PER OBJECT
    // Use debugBoxes to store per-object bounding boxes
    // Track triangles per object using triangle indices
    for (size_t objIdx = 0; objIdx < objects.size(); ++objIdx)
    {
		const std::vector<Triangle>& objTriangles = triangleByObject[objIdx];

        if (objTriangles.empty()) continue; // Skip empty objects

		vec3 minBounds = objTriangles[0][0];
		vec3 maxBounds = objTriangles[0][0];

        // Calculate bounding box for this object
        for (const Triangle& tri : objTriangles)
        {
            for (const vec3& point : tri.points)
            {
                minBounds = min(minBounds, point);
                maxBounds = max(maxBounds, point);
            }
        }
        // Create a bounding box from the min and max bounds
        vec3 center = (minBounds + maxBounds) * 0.5f;
        vec3 extents = (maxBounds - minBounds) * 0.5f;
		debugBoxes.push_back(new Box(center, extents));
    }

    // 4. BOUNDING SPHERE PER OBJECT
    // Use debugSpheres to store per-object bounding spheres
    for (size_t objIdx = 0; objIdx < debugBoxes.size(); ++objIdx)
    {
        const Box* box = debugBoxes[objIdx];

        // Simple sphere from bounding box
        vec3 center = box->center;
        float radius = length(box->extents); // Radius = distance to corner

        debugSpheres.push_back(new Sphere(center, radius));
    }
}

void StudentCode::Destroy()
{
    for (Segment* seg : debugSegs)
    {
        delete seg;
    }

    for (Triangle* tri : debugTriangles)
    {
        delete tri;
    }

    for (Box* box : debugBoxes)
    {
        delete box;
    }

    for (Sphere* sphere : debugSpheres)
    {
        delete sphere;
    }
}

void StudentCode::DrawDebug(unsigned int programId)
{
    // The ray from the eye through the center pixel.
    vec3 eye = Hdiv(ViewInverse*vec4(0,0,0,1));
    vec3   T = Hdiv(ViewInverse*ProjInverse*vec4(0,0,-1,1));
    Ray ray(eye, T-eye);
    
    // @@ This is where you should debug draw the first triangle hit by the ray.
	float closestDistance = std::numeric_limits<float>::max();
	Triangle* closestTriangle = nullptr;

    for (Triangle& triangle : triangles)
    {
        float t, u, v;
        if (Intersects(ray, triangle, &t, &u, &v))
        {
            // Only consider intersections in front of the camera (t > 0)
            if (t > 0.0f && t < closestDistance)
            {
                closestDistance = t;
                closestTriangle = &triangle;
            }
        }
	}

    // If we found a triangle, draw it with a special color
    if (closestTriangle != nullptr)
    {
        // Draw the selected triangle in red to make it stand out
        DrawDebug(programId, closestTriangle, vec3(1.0f, 0.0f, 0.0f)); // Red color
    }

    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
    if (drawDebugSegs)  for (Segment* seg : debugSegs) DrawDebug(programId, seg);
	if (drawDebugTriangles) for (Triangle* tri : debugTriangles) DrawDebug(programId, tri);
	if (drawDebugBoxes) for (Box* box : debugBoxes) DrawDebug(programId, box);
    if (drawDebugSpheres) for (Sphere* sphere : debugSpheres) DrawDebug(programId, sphere);
}

// @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.)
// You have access to the following functions that return 4x4 transformations:
//    mat4 Rotate(const int axis, const float theta); // axis-0,1,2;  theta in degrees
//    mat4 Scale(const float x, const float y, const float z);
//    mat4 Scale(vec3);
//    mat4 Translate(const float x, const float y, const float z);
//    mat4 Translate(vec3);
//
// Products of these 4x4 transformations will have effect right to left
//    (That's possibly backward of what you might expect.)

void StudentCode::DrawDebug(unsigned int programId, Segment* seg, vec3 color)
{
    vec3& A = seg->point1;
    vec3& B = seg->point2;
    mat4 mtr = Translate(A)*Scale(B-A);

    Setup(programId, mtr, color);
    glBindVertexArray(segmentVao);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void StudentCode::DrawDebug(unsigned int programId, Triangle* tri, vec3 color)
{
    vec3& A = tri->points[0];
    vec3& B = tri->points[1];
    vec3& C = tri->points[2];

    // Create transformation matrix that maps the unit triangle to ABC
    // The unit triangle has vertices at (0,0,0), (1,0,0), (0,1,0)
    vec3 AB = B - A;
    vec3 AC = C - A;
    
    // Create transformation matrix [AB AC 0 A; 0 0 0 1]
    mat4 mtr = mat4(
        AB.x, AB.y, AB.z, 0.0f,
        AC.x, AC.y, AC.z, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        A.x, A.y, A.z, 1.0f
	);

	Setup(programId, mtr, color);
    glBindVertexArray(triangleVao);
    glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);  // 3 edges * 2 vertices
    glBindVertexArray(0);
}

void StudentCode::DrawDebug(unsigned int programId, Box* box, vec3 color)
{
    // Transform unit cube to box position and size
	mat4 mtr = Translate(box->center) * Scale(box->extents);

    Setup(programId, mtr, color);
    glBindVertexArray(boxVao);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);  // 12 edges * 2 vertices
    glBindVertexArray(0);
}

void StudentCode::DrawDebug(unsigned int programId, Sphere* sphere, vec3 color)
{
    // Transform unit sphere to sphere position and size
    mat4 mtr = Translate(sphere->center) * Scale(vec3(sphere->radius));

    Setup(programId, mtr, color);
    glBindVertexArray(sphereVao);
    // 3 circles * 16 segments * 2 vertices per line = 96 indices
    glDrawElements(GL_LINES, 288, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void StudentCode::DrawGui()
{
    static bool popup = false;
    if (ImGui::Checkbox("Report", &popup)) ImGui::OpenPopup("Report");
    if (ImGui::BeginPopupModal("Report", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Running in release mode on Windows.\n\
CPU is AMD Ryzen 7 4800H with Radeon Graphics @ 2.90GHz\n\
FPS = 120 with 400,000 triangles\n\
FPS = 90 with 500,000 triangles.\n\
FPS = 60 with 600,000 triangles.");
        if (ImGui::Button("Close", ImVec2(60, 0))) ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.)
    ImGui::Checkbox("Draw Segments",  &drawDebugSegs);
	ImGui::Checkbox("Draw Triangles", &drawDebugTriangles);
    ImGui::Checkbox("Draw Boxes",     &drawDebugBoxes);
    ImGui::Checkbox("Draw Spheres",  &drawDebugSpheres);
}

void StudentCode::GenerateRayTracedImage(int width, int height, float* image, vec3& lightPos)
{

    // @@ This code colors in all pixels with a test pattern.  Replace it all with ray tracing code
    for (int i=0;  i<width; i++) {
        for (int j=0;  j<height; j++) {
            vec3 color = vec3(1,1,1); // White

            if (abs(width/2 - i) <10 || abs(height/2 - j) <10)
                color = vec3(0,0,1); // Blue center lines

            if (i<10 || i>width-10 || j<10 || j>height-10)
                color = vec3(0,0,0); // Black border

            float* pixel = image + 3*(j*width + i);
            *pixel++ = color.x;
            *pixel++ = color.y;
            *pixel++ = color.z; } }
    
    // @@ Here is a start on the ray tracing code to replace the above test pattern.
    // int N=100;  // Set small if your ray tracing code is too slow to do full screen
    // vec3 eye = Hdiv(ViewInverse*vec4(0,0,0,1));

    // // i and j are pixel coordinates, 0..750 (or whatever the screen size is).
    // for (int i=width/2-N;  i<=width/2+N; i++)
    //     for (int j=height/2-N;  j<=height/2+N; j++) {
    //         float x = ;
    //         float y = ;
    //         vec3 PixelInNDC = Hdiv(ViewInverse*ProjInverse*
    //                                vec4(2.0*(i+0.5)/width  - 1, // Pixel center x coord
    //                                     2.0*(j+0.5)/height - 1, // Pixel center y coord
    //                                     -1,                     // Front of NDC
    //                                     1));
            
    //         Ray ray(eye, T-eye); // Ray from eye through pixel
    //         // ... Trace the ray and color whatever it hits.
    //         vec3 color = ... whatever ...
    //         float* pixel = image + 3*(j*width + i);
    //         *pixel++ = color.x;
    //         *pixel++ = color.y;
    //         *pixel++ = color.z;
    //     } }

}
