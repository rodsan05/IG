#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include <vector>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::setTexture(Texture* tex)
{
	mTexture = tex;
}

void Abs_Entity::upload(dmat4 const& modelViewMat) const
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
	mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

PoligonoRegular::PoligonoRegular(GLuint num, GLdouble r)
{
	mMesh = Mesh::generaPoligonoRegular(num, r);
}

PoligonoRegular::~PoligonoRegular()
{
	delete mMesh; mMesh = nullptr;
}

void PoligonoRegular::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glLineWidth(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}

TrianguloRGB::TrianguloRGB(GLdouble r)
{
	mMesh = Mesh::generaTrianguloRGB(r);
	radius = 200;
	alpha = 0.0;
	rotationPerFrame = 3.0;
}

TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

void TrianguloRGB::update()
{
	mModelMat = translate(mModelMat, dvec3(-radius * cos(radians(alpha)), -radius * sin(radians(alpha)), 0));
	mModelMat = rotate(mModelMat, radians(-rotationPerFrame), dvec3(0, 0, 1));

	alpha += rotationPerFrame + 1;
	mModelMat = translate(mModelMat, dvec3(radius * cos(radians(alpha)), radius * sin(radians(alpha)), 0));
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

Cubo::Cubo(GLdouble lon)
{
	mMesh = Mesh::generaCubo(lon);
}

Cubo::~Cubo()
{
	delete mMesh; mMesh = nullptr;
}

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

CuboRGB::CuboRGB(GLdouble lon)
{
	mMesh = Mesh::generaCuboTriangulosRGB(lon);

	axis = 0;
	alpha = 0;
	rotationPerFrame = 2.0;
	mLon = lon;
}

CuboRGB::~CuboRGB()
{
	delete mMesh; mMesh = nullptr;
}

void CuboRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

void CuboRGB::update()
{
	std::vector<dvec3> rotationVec = { dvec3(0, 1, 0), dvec3(1, 0, 0), dvec3(0, 0, 1) };

	if (alpha < 180) {

		mModelMat = translate(mModelMat, dvec3(mLon / 2, -mLon / 2, -mLon / 2));

		mModelMat = rotate(mModelMat, radians(rotationPerFrame), rotationVec[axis]);
		mModelMat = translate(mModelMat, dvec3(-mLon / 2, mLon / 2, mLon / 2));

		alpha += rotationPerFrame;
	}
	else {

		alpha = 0;

		if (axis < 2) axis++;
		else axis = 0;
	}
}

Suelo::Suelo(GLdouble w, GLdouble h, Texture* t)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, 4, 4);

	mModelMat = rotate(mModelMat, radians(-90.0), dvec3(1, 0, 0));

	mTexture = t;
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		//glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
		glColor4d(1, 1, 1, 1);
	}
}

ContornoCaja::ContornoCaja(GLdouble lon, Texture* t, Texture* inText)
{
	mMesh = Mesh::generaContCajaTexCor(lon);

	mTexture = t;
	insideText = inText;
}

ContornoCaja::~ContornoCaja()
{
	delete mMesh; mMesh = nullptr;
}

void ContornoCaja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();

		glDisable(GL_CULL_FACE);

		glEnable(GL_CULL_FACE);

		glCullFace(GL_FRONT);
		insideText->bind(GL_REPLACE);
		mMesh->render();
		insideText->unbind();

		glDisable(GL_CULL_FACE);
	}
}
