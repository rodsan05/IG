#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

    // Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));

	//Apartado 2
	//gObjects.push_back(new PoligonoRegular(7, 100.0));

	//Apartado 4
	/*Abs_Entity* triangle = new PoligonoRegular(3, 100.0);
	triangle->setMColor({ 0.0, 1.0, 1.0, 1.0 });
	gObjects.push_back(triangle);

	Abs_Entity* circunference = new PoligonoRegular(64, 100.0);
	circunference->setMColor({ 1.0, 0.0, 1.0, 1.0 });
	gObjects.push_back(circunference);*/
	
	//Apartado 5 y 6
	//gObjects.push_back(new TrianguloRGB(100.0));

	//Apartado 7
	//gObjects.push_back(new RectanguloRGB(200, 100));

	//Apartado 8
	//gObjects.push_back(new Cubo(200));

	if (mId == 0) {
	
		GLdouble radius = 200.0;
		Abs_Entity* circunference = new PoligonoRegular(256, radius);
		circunference->setMColor({ 1.0, 0.0, 1.0, 1.0 });
		gObjects.push_back(circunference);

		gObjects.push_back(new RectanguloRGB(400, 200));

		Abs_Entity* trianguloRGB = new TrianguloRGB(50.0);
		gObjects.push_back(trianguloRGB);

		trianguloRGB->setModelMat(translate(trianguloRGB->modelMat(), dvec3(radius, 0, 0)));
	}

	else if (mId == 1) {
		//Apartado 9

		GLdouble lon = 200;
		Abs_Entity* cuboRGB = new CuboRGB(lon);
		gObjects.push_back(cuboRGB);

		cuboRGB->setModelMat(translate(cuboRGB->modelMat(), dvec3(-lon/2, lon/2, lon/2)));
	}

	else if (mId == 2) {
	
		Texture* t = new Texture();
		t->load("..\\Bmps\\baldosaC.bmp");
		gTextures.push_back(t);

		Abs_Entity* suelo = new Suelo(500, 500, t);
		gObjects.push_back(suelo);

		t = new Texture();
		t->load("..\\Bmps\\grass.bmp", u8vec3(0, 0, 0), 0);
		gTextures.push_back(t);

		Abs_Entity* hierbas = new Hierbas(100, 100, t);
		gObjects.push_back(hierbas);


		t = new Texture();
		gTextures.push_back(t);
		Abs_Entity* foto = new Foto(80, 60, t);
		gObjects.push_back(foto);
	}

	else if (mId == 3) {
	
		Texture* t = new Texture();
		t->load("..\\Bmps\\container.bmp");
		gTextures.push_back(t);

		Texture* inT = new Texture();
		inT->load("..\\Bmps\\papelE.bmp");
		gTextures.push_back(inT);

		Abs_Entity* caja = new Caja(200, t, inT);
		gObjects.push_back(caja);
	}

	else if (mId == 4) {

		Texture* t = new Texture();
		t->load("..\\Bmps\\baldosaP.bmp");
		gTextures.push_back(t);

		Abs_Entity* estrella = new Estrella3D(200, 8, 200, t);
		gObjects.push_back(estrella);
	}

	else if (mId == 5) {

		Texture* t = new Texture();
		t->load("..\\Bmps\\windowV.bmp", 80);
		gTextures.push_back(t);

		Abs_Entity* cristalera = new Cristalera(200, 100, t);
		gTranslucidObjects.push_back(cristalera);
	}
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}

	for (Abs_Entity* el : gTranslucidObjects)
	{
		delete el;  el = nullptr;
	}

	for (Texture* t : gTextures) 
	{
		delete t;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

	glEnable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	

	glDisable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	    el->render(cam.viewMat());
	}

	for (Abs_Entity* el : gTranslucidObjects)
	{
		el->render(cam.viewMat());
	}
}
void Scene::update()
{
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}

	for (Abs_Entity* el : gTranslucidObjects)
	{
		el->update();
	}
}
void Scene::setState(int id)
{
	if (id != mId) {

		free();
		gObjects.clear();
		gTranslucidObjects.clear();
		gTextures.clear();

		mId = id;
		init();
	}
}
//-------------------------------------------------------------------------


