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

	if (mId == 1) {
		//Apartado 9

		GLdouble lon = 200;
		Abs_Entity* cuboRGB = new CuboRGB(lon);
		gObjects.push_back(cuboRGB);

		cuboRGB->setModelMat(translate(cuboRGB->modelMat(), dvec3(-lon/2, lon/2, lon/2)));
	}
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
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
}
void Scene::setState(int id)
{
	if (id != mId) {

		free();
		gObjects.clear();

		mId = id;
		init();
	}
}
//-------------------------------------------------------------------------


