
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

    
}

void StudentCode::SetTransforms(mat4& _vi, mat4& _pi)
{
    ViewInverse = _vi;
    ProjInverse = _pi;
}

bool StudentCode::IsStepLegal(vec3 eye, vec3& direction, float step)
{
    return true;
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

}

void StudentCode::EndOfTriangles()
{
    // @@ This is called when all triangles have been passed in via
    // ObjectTriangles calls. Build your spatial data structure here.
    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.)
    debugSegs.push_back(new Segment(vec3(0,0,0), vec3(1,1,1)));
    
    printf("Triangles: %ld\n", triangles.size());
}

void StudentCode::Destroy()
{
}

void StudentCode::DrawDebug(unsigned int programId)
{
    // The ray from the eye through the center pixel.
    vec3 eye = Hdiv(ViewInverse*vec4(0,0,0,1));
    vec3   T = Hdiv(ViewInverse*ProjInverse*vec4(0,0,-1,1));
    Ray ray(eye, T-eye);
    
    // @@ This is where you should debug draw the first triangle hit by the ray.
    

    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
    if (drawDebugSegs   )  for (Segment*  seg : debugSegs)    DrawDebug(programId, seg);
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


void StudentCode::DrawGui()
{
    // @@ Example debug for Segments.  (Needs Triangles, Boxes, and Spheres.) 
    ImGui::Checkbox("Draw Segments",  &drawDebugSegs);
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
