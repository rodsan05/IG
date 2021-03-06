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

    if (vTexCoords.size() > 0) 
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 36;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //cara delantera
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);

    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);

    //lateral derecha
    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);

    //cara trasera
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);

    //lateral izquierda
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);

    //superior
    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);

    //inferior
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);

    return mesh;
}
Mesh* Mesh::generaCuboTriangulosRGB(GLdouble lon)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 36;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //cara delantera
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);

    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);

    //lateral derecha
    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);

    //cara trasera
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);

    //lateral izquierda
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);

    //superior
    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);

    //inferior
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);

    mesh->vColors.reserve(mesh->mNumVertices);

    //cara delantera
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    //lateral derecha
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

    //cara trasera
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    //lateral izquierda
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

    //superior
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    //inferior
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}
Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vTexCoords.reserve(4);

    mesh->vTexCoords.emplace_back(0, rh);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(rw, rh);
    mesh->vTexCoords.emplace_back(rw, 0);

    return mesh;
}
Mesh* Mesh::generaContCaja(GLdouble lon)
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
Mesh* Mesh::generaContCaja(GLdouble lon, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(-lon / 2, h / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -h / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, h / 2, lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -h / 2, lon / 2);

    mesh->vVertices.emplace_back(lon / 2, h / 2, -lon / 2);
    mesh->vVertices.emplace_back(lon / 2, -h / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, h / 2, -lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -h / 2, -lon / 2);

    mesh->vVertices.emplace_back(-lon / 2, h / 2, lon / 2);
    mesh->vVertices.emplace_back(-lon / 2, -h / 2, lon / 2);

    return mesh;
}
Mesh* Mesh::generaContCajaTexCor(GLdouble lon)
{
    Mesh* mesh = generaContCaja(lon);

    mesh->vTexCoords.reserve(10);

    mesh->vTexCoords.emplace_back(0, 1);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(1, 1);
    mesh->vTexCoords.emplace_back(1, 0);

    mesh->vTexCoords.emplace_back(2, 1);
    mesh->vTexCoords.emplace_back(2, 0);

    mesh->vTexCoords.emplace_back(3, 1);
    mesh->vTexCoords.emplace_back(3, 0);

    mesh->vTexCoords.emplace_back(4, 1);
    mesh->vTexCoords.emplace_back(4, 0);

    return mesh;
}
Mesh* Mesh::generaContCajaTexCor(GLdouble lon, GLdouble h)
{
    Mesh* mesh = generaContCaja(lon, h);

    mesh->vTexCoords.reserve(10);

    mesh->vTexCoords.emplace_back(0, 1);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(1, 1);
    mesh->vTexCoords.emplace_back(1, 0);

    mesh->vTexCoords.emplace_back(2, 1);
    mesh->vTexCoords.emplace_back(2, 0);

    mesh->vTexCoords.emplace_back(3, 1);
    mesh->vTexCoords.emplace_back(3, 0);

    mesh->vTexCoords.emplace_back(4, 1);
    mesh->vTexCoords.emplace_back(4, 0);

    return mesh;
}
Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h)
{
    GLdouble ri = re / 2;
    GLdouble angle = 360.0 / np;

    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_FAN;

    mesh->mNumVertices = np*2 + 2;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0, 0, 0);
    
    GLdouble alpha = 90.0;
    for (int i = 0; i < np; i++)
    {
        mesh->vVertices.emplace_back(re * cos(radians(alpha)), re * sin(radians(alpha)), h);
        alpha += angle / 2.0;

        mesh->vVertices.emplace_back(ri * cos(radians(alpha)), ri * sin(radians(alpha)), h);
        alpha += angle / 2.0;
    }

    mesh->vVertices.emplace_back(re * cos(radians(alpha)), re * sin(radians(alpha)), h);

    return mesh;
}
Mesh* Mesh::generaEstrella3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = generaEstrella3D(re, np, h);

    mesh->vTexCoords.reserve(mesh->mNumVertices);

    mesh->vTexCoords.emplace_back(0.5, 0.5);

    float distance = 1 / ((float)np / 2);

    for (int i = 0; i < np / 4; i++) {
    
        mesh->vTexCoords.emplace_back(0.5 - distance * i, 1);
    }

    for (int i = 0; i < np / 2; i++) {

        mesh->vTexCoords.emplace_back(0, 1 - distance * i);
    }

    for (int i = 0; i < np / 2; i++) {

        mesh->vTexCoords.emplace_back(distance * i, 0);
    }

    for (int i = 0; i < np / 2; i++) {

        mesh->vTexCoords.emplace_back(1, distance * i);
    }

    for (int i = 0; i < np / 4+1; i++) {

        mesh->vTexCoords.emplace_back(1 - distance * i, 1);
    }

    return mesh;
}
//-------------------------------------------------------------------------

