//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Texture.h"
#include <functional>

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

class CompoundEntity : public Abs_Entity
{
public:
	CompoundEntity();
	~CompoundEntity();

	void addEntity(Abs_Entity* ae, bool translucent);
	void setUpdate(std::function<void()> updateFunct);

	void update() override;

	void render(glm::dmat4 const& modelViewMat) const;

protected:
	std::vector<Abs_Entity*> gObjects;
	std::vector<Abs_Entity*> gObjectsTranslucent;

	//funcion que ejecuta el update, una lambda void()
	std::function<void()> updateFuntion = nullptr;
};

class QuadricEntity : public Abs_Entity
{
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};

class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r_); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};

class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble baseR_, GLdouble topR_, GLdouble height_);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble baseR;
	GLdouble topR;
	GLdouble height;
};

class Disk : public QuadricEntity {
public:
	Disk(GLdouble innerR_, GLdouble outerR_);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerR;
	GLdouble outerR;
};

class PartialDisk : public QuadricEntity {
public:
	PartialDisk(GLdouble innerR_, GLdouble outerR_, GLdouble startAngle_, GLdouble sweepAngle_);
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerR;
	GLdouble outerR;
	GLdouble startAngle;
	GLdouble sweepAngle;
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
//Cara/Cabeza
class Cabeza : public Abs_Entity
{
public:
	explicit Cabeza();
	~Cabeza();
	virtual void render(glm::dmat4 const& modelViewMat) const;

protected:
	Sphere* cabezaSph;
	PartialDisk* barbaDsk;
	Disk* sombreroDsk;
	Cylinder* ojoIzq;
	Cylinder* ojoDer;

	glm::dmat4 mModelMatBarba;
	glm::dmat4 mModelMatSombrero;
	glm::dmat4 mModelMatOjoIzq;
	glm::dmat4 mModelMatOjoDer;
};

class AlaTIEAvanzado : public Abs_Entity 
{
public:
	explicit AlaTIEAvanzado(GLdouble l, GLdouble h, GLdouble depth, Texture* t);
	~AlaTIEAvanzado();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class TIEAvanzado : public CompoundEntity 
{
public:
	explicit TIEAvanzado(GLdouble cabinRadius, GLdouble wingW, GLdouble wingH, GLdouble wingDepth, Texture* textureWing,
		GLdouble armRadius, GLdouble armLenght, GLdouble windowRadius);
};

class Cubo : public Abs_Entity 
{
public:
	explicit Cubo(GLdouble l);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


#endif //_H_Entities_H_