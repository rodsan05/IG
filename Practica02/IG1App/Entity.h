//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Texture.h"

#include "Mesh.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(0.0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	

	void setColor(glm::dvec4 vColor) { mColor = vColor; }; 
	void setTexture(Texture* tex) { mTexture = tex; }; 

	//ejercicio 5
	virtual void update() {}

	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 

	//ejercicio 1
	glm::dvec4 mColor;
	Texture* mTexture = nullptr;
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Poligono : public Abs_Entity {
public:
	explicit Poligono(GLuint numL, GLdouble rd, glm::dvec4 color);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class TrianguloRGB : public Abs_Entity {
public:
	explicit TrianguloRGB(GLdouble rd);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	double angle, angleCircle;
};

//-------------------------------------------------------------------------

class RectanguloRGB : public Abs_Entity {
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Estrella3D : public Abs_Entity {
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	GLdouble alpha;
};

//-------------------------------------------------------------------------

class Suelo : public Abs_Entity {
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh, glm::dvec4 color);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Foto : public Abs_Entity {
public:
	explicit Foto(GLdouble width, GLdouble height);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
//-------------------------------------------------------------------------

class Cristalera : public Abs_Entity {
public:
	explicit Cristalera(GLdouble Xwidth, GLdouble Ywidth, GLdouble height);
	~Cristalera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Hierba : public Abs_Entity {
public:
	explicit Hierba(GLdouble ld);
	~Hierba();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class ContornoCaja : public Abs_Entity
{
public:
	explicit ContornoCaja(GLdouble lon, Texture* t, Texture* inText);
	~ContornoCaja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	Texture* insideText;
};

class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble lon, Texture* t, Texture* inText);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

protected:
	Texture* insideText;

	Mesh* top;
	Mesh* bottom;

	glm::dmat4 mModelMatTop;
	glm::dmat4 mModelMatBot;

	GLdouble l;
	GLdouble alpha;
	GLdouble beta;
	int dir;
};


#endif //_H_Entities_H_