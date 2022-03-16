//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	virtual void update() {};

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//mColor get & set
	glm::dvec4 const& getMColor() const { return mColor; };
	void setMColor(glm::dvec4 const& col) { mColor = col; };

	void setTexture(Texture* tex);
	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	Texture* mTexture = nullptr;

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

	void update() override;

protected:
	GLdouble radius;
	GLdouble alpha;
	GLdouble rotationPerFrame;
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
};

class CuboRGB : public Abs_Entity
{
public:
	explicit CuboRGB(GLdouble lon);
	~CuboRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

protected:
	GLdouble alpha;
	GLdouble rotationPerFrame;
	int axis;
	GLdouble mLon;
};

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, Texture* t);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Hierbas : public Abs_Entity
{
public:
	explicit Hierbas(GLdouble w, GLdouble h, Texture* t);
	~Hierbas();
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

class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;
protected:
	GLdouble alpha;
};

class Cristalera : public Abs_Entity
{
public:
	explicit Cristalera(GLdouble lon, GLdouble h, Texture* t);
	~Cristalera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

protected:

	GLdouble width, height;
};
//-------------------------------------------------------------------------

#endif //_H_Entities_H_