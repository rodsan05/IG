#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "IG1App.h"

using namespace glm;

//-------------------------------------------------------------------------

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

Poligono::Poligono(GLuint numL, GLdouble rd, glm::dvec4 color) : Abs_Entity()
{
	mColor = color;
	mMesh = Mesh::generaPoligono(numL, rd);
}

void Poligono::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		mMesh->render();
;		glLineWidth(1);
		glColor3d(1,1,1);
	}
}
Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
};

//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble rd) : Abs_Entity()
{
	angle = angleCircle = 0;
	mMesh = Mesh::generaTrianguloRGB(rd);
}

void TrianguloRGB::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // por defecto
		glColor3d(1, 1, 1);
	}
}
TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
};

void TrianguloRGB::update() {
	angle += 3; angleCircle++;
	//controlar que no se pase del rango del double
	angle = (int)angle % 360; angleCircle = (int)angleCircle % 360;
	//primero colocamos el triangulo segun angleCircle
	setModelMat(translate(dmat4(1), dvec3(200 * cos(radians(angleCircle)), 200 * sin(radians(angleCircle)), 1)));
	//lo rotamos segun angle
	setModelMat(rotate(modelMat(), -radians(angle), glm::dvec3(0, 0, 1)));
}

//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

void RectanguloRGB::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // por defecto
		glColor3d(1, 1, 1);
	}
}
RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
};

//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h) : Abs_Entity()
{
	alpha = 0;
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
}

void Estrella3D::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) 
	{
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		mMesh->render();

		aMat = rotate(aMat, -radians(180.0), dvec3(0, 1, 0));
		upload(aMat);
		mMesh->render();
		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // por defecto
		glColor3d(1, 1, 1);
	}	
}
Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
};

void Estrella3D::update() 
{
	alpha += 2.0f;

	mModelMat = translate(dmat4(1), dvec3(-60, 70, -60));
	mModelMat = rotate(mModelMat, radians(alpha), dvec3(0, 1, 0));
	mModelMat = rotate(mModelMat, radians(alpha), dvec3(0, 0, 1));
}

//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh, glm::dvec4 color)
{
	setModelMat(rotate(dmat4(1), radians(90.0), dvec3(1, 0, 0)));
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	mColor = color;
}

void Suelo::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_MODULATE);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		mTexture->unbind();
		glColor3d(1, 1, 1);
	}
}
Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
};

Foto::Foto(GLdouble width, GLdouble height) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloTexCor(width, height, 1,1);
	mTexture = new Texture();
}

void Foto::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_MODULATE);
		mMesh->render();
		mTexture->unbind();
	}
}
Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture;
};

void Foto::update() {
	//actualizamos la textura al ultimo renderizado
	mTexture->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT);
}

Cristalera::Cristalera(GLdouble Xwidth, GLdouble Ywidth, GLdouble height) : Abs_Entity()
{
	mMesh = Mesh::generaContRectTexCor(Xwidth, Ywidth, height);
}

void Cristalera::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // por defecto
	}
}
Cristalera::~Cristalera()
{
	delete mMesh; mMesh = nullptr;
};

Hierba::Hierba(GLdouble ld) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloTexCor(ld, ld, 1, 1);
}

void Hierba::render(dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		mTexture->bind(GL_REPLACE);

		int i = 0;
		while (i < 3) {
			upload(aMat);
			mMesh->render();
			aMat = rotate(aMat, radians(45.0), dvec3(0, 1, 0));
			i++;
		}
		mTexture->unbind();
	}
}
Hierba::~Hierba()
{
	delete mMesh; mMesh = nullptr;
};

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

Caja::Caja(GLdouble lon, Texture* t, Texture* inText)
{
	mMesh = Mesh::generaContCajaTexCor(lon);

	mModelMat = translate(dmat4(1), dvec3(0, lon/2 + 2, 0));

	top = Mesh::generaRectanguloTexCor(lon, lon, 1, 1);
	
	mModelMatTop = translate(dmat4(1), dvec3(0, lon+2, 0));
	mModelMatTop = rotate(mModelMatTop, radians(-90.0), dvec3(1, 0, 0));

	bottom = Mesh::generaRectanguloTexCor(lon, lon, 1, 1);

	mModelMatBot = translate(dmat4(1), dvec3(0, 2, 0));
	mModelMatBot = rotate(mModelMatBot, radians(90.0), dvec3(1, 0, 0));

	mTexture = t;
	insideText = inText;
	l = lon;
	alpha = 180;
	beta = 0;
	dir = -1;
}

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
	delete top; top = nullptr;
	delete bottom; bottom = nullptr;
}

void Caja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();

		glCullFace(GL_FRONT);
		insideText->bind(GL_REPLACE);
		mMesh->render();
		insideText->unbind();

		dmat4 aMatTop = modelViewMat * mModelMatTop;
		upload(aMatTop);

		glCullFace(GL_BACK);
		mTexture->bind(GL_REPLACE);
		top->render();
		mTexture->unbind();

		glCullFace(GL_FRONT);
		insideText->bind(GL_REPLACE);
		top->render();
		insideText->unbind();

		dmat4 aMatBot = modelViewMat * mModelMatBot;
		upload(aMatBot);

		glCullFace(GL_BACK);
		mTexture->bind(GL_REPLACE);
		bottom->render();
		mTexture->unbind();

		glCullFace(GL_FRONT);
		insideText->bind(GL_REPLACE);
		bottom->render();
		insideText->unbind();

		glDisable(GL_CULL_FACE);
	}
}

void Caja::update()
{
	if (alpha > 180 || alpha < 0) dir *= -1;

	alpha += 2.0 * dir;
	beta += 2.0 * dir;
	
	mModelMatTop = translate(dmat4(1), dvec3(l / 2 * cos(radians(alpha)) + l / 2, l/2 * sin(radians(alpha)), 0));
	mModelMatTop = translate(mModelMatTop, dvec3(0, (l + 1), 0));
	mModelMatTop = rotate(mModelMatTop, radians(beta), dvec3(0, 0, 1));
	mModelMatTop = rotate(mModelMatTop, radians(-90.0), dvec3(1, 0, 0));
}

QuadricEntity::QuadricEntity()
{
	q = gluNewQuadric();
}

Sphere::Sphere(GLdouble r_)
{
	r = r_;
}

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	if (mColor != dvec4(0.0)) 
	{
		glEnable(GL_COLOR_MATERIAL);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
	}

	if (mTexture != nullptr) {
	
		mTexture->bind(GL_REPLACE);
	}
	gluSphere(q, r, 50, 50);
	if (mTexture != nullptr) {

		mTexture->unbind();
	}

	// Aquí se debe recuperar el color:
	glColor4d(1.0, 1.0, 1.0, 1.0);
}

Cylinder::Cylinder(GLdouble baseR_, GLdouble topR_, GLdouble height_)
{
	baseR = baseR_;
	topR = topR_;
	height = height_;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	
	if (mColor != dvec4(0.0))
	{
		glEnable(GL_COLOR_MATERIAL);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
	}

	if (mTexture != nullptr) {

		mTexture->bind(GL_REPLACE);
	}
	gluCylinder(q, baseR, topR, height, 50, 50);
	if (mTexture != nullptr) {

		mTexture->unbind();
	}
	
	// Aquí se debe recuperar el color:
	glColor4d(1.0, 1.0, 1.0, 1.0);
}

Disk::Disk(GLdouble innerR_, GLdouble outerR_)
{
	innerR = innerR_;
	outerR = outerR_;
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	
	if (mColor != dvec4(0.0))
	{
		glEnable(GL_COLOR_MATERIAL);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
	}

	if (mTexture != nullptr) {

		mTexture->bind(GL_REPLACE);
	}
	gluDisk(q, innerR, outerR, 50, 50);
	if (mTexture != nullptr) {

		mTexture->unbind();
	}

	// Aquí se debe recuperar el color:
	glColor4d(1.0, 1.0, 1.0, 1.0);
}

PartialDisk::PartialDisk(GLdouble innerR_, GLdouble outerR_, GLdouble startAngle_, GLdouble sweepAngle_)
{
	innerR = innerR_;
	outerR = outerR_;
	startAngle = startAngle_;
	sweepAngle = sweepAngle_;
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	
	if (mColor != dvec4(0.0))
	{
		glEnable(GL_COLOR_MATERIAL);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
	}

	if (mTexture != nullptr) {

		mTexture->bind(GL_REPLACE);
	}
	gluPartialDisk(q, innerR, outerR, 50, 50, startAngle, sweepAngle);
	if (mTexture != nullptr) {

		mTexture->unbind();
	}

	// Aquí se debe recuperar el color:
	glColor4d(1.0, 1.0, 1.0, 1.0);
}

CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	for (Abs_Entity* el : gObjectsTranslucent)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
	gObjectsTranslucent.clear();
}

void CompoundEntity::addEntity(Abs_Entity* ae, bool translucent)
{
	if (translucent) gObjectsTranslucent.push_back(ae);
	else gObjects.push_back(ae);
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	//gObjects opacos
	for (Abs_Entity* elOpaque : gObjects)
	{
		elOpaque->render(modelViewMat);
	}
	//gObjects translucidos
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (Abs_Entity* elTranslucent : gObjectsTranslucent)
	{
		elTranslucent->render(modelViewMat);
	}
	//dejamos los valores por defecto
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
