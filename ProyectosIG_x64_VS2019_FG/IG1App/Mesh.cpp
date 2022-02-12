#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligonoRegular(GLuint num, GLdouble r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = num;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble alpha = 90.0;
    for (int i = 0; i < num; i++)
    {
        mesh->vVertices.emplace_back(r * cos(radians(alpha)), r * sin(radians(alpha)), 0.0);
        alpha += 360.0 / num;
    }

    return mesh;
}

Mesh* Mesh::generaTrianguloRGB(GLdouble r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 3;
    mesh->vVertices.reserve(mesh->mNumVertices);
    
    GLdouble alpha = 90.0;
    for (int i = 0; i < 3; i++)
    {
        mesh->vVertices.emplace_back(r * cos(radians(alpha)), r * sin(radians(alpha)), 0.0);
        alpha += 360.0 / 3;
    }

    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(-w/2, h/2, 0.0);
    mesh->vVertices.emplace_back(-w / 2, -h / 2, 0.0);
    mesh->vVertices.emplace_back(w / 2, h / 2, 0.0);
    mesh->vVertices.emplace_back(w / 2, -h / 2, 0.0);

    return mesh;
}
Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = Mesh::generaRectangulo(w, h);

    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}
Mesh* Mesh::generaCubo(GLdouble lon)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);

    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);

    return mesh;
}
//-------------------------------------------------------------------------

