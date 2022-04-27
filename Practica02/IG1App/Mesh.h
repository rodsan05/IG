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
	static Mesh* generaAlaTIEAvanzado(GLdouble l, GLdouble h, GLdouble depth);
	static Mesh* generaCabeza(GLdouble l);

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
	std::vector<glm::dvec3> vNormals;
	virtual void draw() const;
};

class IndexMesh : public Mesh {
protected:
	GLuint* vIndices = nullptr; // tabla de índices
	GLuint mNumIndices = 0;

	void buildNormalVectors(std::vector<glm::dvec3>& normals);

public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] vIndices; }
	virtual void draw() const;

	static IndexMesh* generaCuboConTapasIndexado(GLdouble lon);
};

class MbR : public IndexMesh 
{
public:
	MbR(int n_, int m_, dvec3* perfil_) : n(n_), m(m_), perfil(perfil_) {};
	~MbR() {};

	static MbR* generaMallaIndexadaPorRevolucion(int m_, int n_, glm::dvec3* perfil_);

private:
	int n; //n puntos perfil
	int m; //m rotaciones que se toman

	glm::dvec3* perfil;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_