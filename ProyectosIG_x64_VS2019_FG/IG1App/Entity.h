//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//mColor get & set
	glm::dvec4 const& getMColor() const { return mColor; };
	void setMColor(glm::dvec4 const& col) { mColor = col; };
	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix

	glm::dvec4 mColor;	//mesh color
	
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class PoligonoRegular : public Abs_Entity
{
public:
	explicit PoligonoRegular(GLuint num, GLdouble r);
	~PoligonoRegular();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Cubo : public Abs_Entity
{
public:
	explicit Cubo(GLdouble lon);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;

protected:

	Mesh* tapaSup = nullptr;
	Mesh* tapaInf = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_