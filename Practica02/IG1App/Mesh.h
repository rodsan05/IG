//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	static Mesh* generaPoligono(GLuint numL, GLdouble rd);
	static Mesh* generaTrianguloRGB(GLdouble rd);
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
	static Mesh* generaEstrella3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCubo(GLdouble ld);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCaja(GLdouble lon);
	static Mesh* generaContCaja(GLdouble lon, GLdouble h);
	static Mesh* generaContCajaTexCor(GLdouble lon);
	static Mesh* generaContCajaTexCor(GLdouble lon, GLdouble h);
	static Mesh* generaContCuboTexCor(GLdouble nl);
	static Mesh* generaContornoRect(GLdouble xWidth, GLdouble yWidth, GLdouble height);
	static Mesh* generaContRectTexCor(GLdouble xWidth, GLdouble yWidth, GLdouble height);

	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
	std::vector<glm::dvec2> const& textures() const { return vTexCoords;  }
		
protected:
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	std::vector<glm::dvec2> vTexCoords;
	virtual void draw() const;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_