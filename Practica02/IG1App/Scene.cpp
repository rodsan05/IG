#include "Scene.h"
#include "CheckML.h"
#include "IG1App.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init(int id_)
{
	mId = id_;
	setGL();// OpenGL settings
	cargarBMPs();// Textures

	// Graphics objects (entities) of the scene
	CrearEntidad(new EjesRGB(400.0), false, nullptr);

	GLfloat amb[] = { 0, 0, 0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	//ejercicio rotar Triangulo 
	if (mId == 0) {
		
		//Crear Triangulo
		CrearEntidad(new Poligono(120, 200.0, { 255,0,255,1 }), false, nullptr);

		CompoundEntity* fakeNode = new CompoundEntity();
		CompoundEntity* fakeNode2 = new CompoundEntity();

		TrianguloRGB* tr = new TrianguloRGB(40);
		fakeNode2->addEntity(tr, false);
		fakeNode->addEntity(fakeNode2, false);

		fakeNode2->setModelMat(translate(fakeNode->modelMat(), dvec3(200, 0, 0)));

		fakeNode2->setUpdate([fakeNode2] {

			fakeNode2->setModelMat(rotate(fakeNode2->modelMat(), radians(-6.0), dvec3(0, 0, 1)));
		});

		fakeNode->setUpdate([fakeNode] { 
			
			fakeNode->setModelMat(rotate(fakeNode->modelMat(), radians(3.0), dvec3(0, 0, 1)));
		});

		CrearEntidad(fakeNode, false, nullptr);
	}
	else if (mId == 1) 
	{
		//Crear Suelo
		auto suelo = new Suelo(200.0, 200.0, 8, 8, dvec4(1,1,1,1));;
		CrearEntidad(suelo, false, gTextures[0]);;

		//Crear Cristalera
		auto cr = new Cristalera(200, 50, 200);
		cr->setModelMat(translate(cr->modelMat(), dvec3(0, 25, 0)));
		CrearEntidad(cr, true, gTextures[9]);

		//Crear Caja con tapa
		auto caja = new Caja(25, gTextures[3], gTextures[7]);
		caja->setColor(dvec4(1, 1, 1, 1));
		CrearEntidad(caja, false, nullptr);

		//Crear estrella con textura
		auto estrella = new Estrella3D(20.0, 8, 15.0);
		estrella->setModelMat(translate(estrella->modelMat(), dvec3(-60, 70, -60)));
		CrearEntidad(estrella, false, gTextures[2]);

		//Setup de Foto
		auto foto = new Foto(80, 60);
		foto->setModelMat(rotate(foto->modelMat(), radians(-90.0), dvec3(1, 0, 0)));
		foto->setModelMat(translate(foto->modelMat(), dvec3(0, 0, 1)));
		CrearEntidad(foto, false, nullptr);

		//Crear Hierba
		auto hierba = new Hierba(50);
		hierba->setModelMat((translate(dmat4(1), dvec3(50, 25, -50))));
		CrearEntidad(hierba, false, gTextures[10]);
	}
	else if (mId == 2)
	{
		//Cabeza
		auto cabeza = new Cabeza();
		CrearEntidad(cabeza, false, nullptr);
	}
	else if (mId == 3)
	{
		auto planet = new Sphere(200);
		planet->setColor(dvec4(255.0 / 255, 233.0 / 255, 0.0, 1.0));

		tieSpotlight = new SpotLight();
		tieSpotlight->setPosDir({ 0.0, 0.0, 0.0 });
		tieSpotlight->setSpot({ 0.0, -1.0, 0.0 }, 100, 0);
		tieSpotlight->setAmb({ 0, 0, 0, 1 });
		tieSpotlight->setDiff({ 1, 1, 0, 1 });
		tieSpotlight->setSpec({ 0.5, 0.5, 0.5, 1 });

		CrearEntidad(planet, false, nullptr);

		fakeNodeTie_ = new CompoundEntity();

		auto tieAvanzado = new TIEAvanzado(10, 20, 15, 10, gTextures[5], 2, 7.5, 5, tieSpotlight);

		fakeNodeTie_->addEntity(tieAvanzado, false);

		tieAvanzado->setModelMat(translate(fakeNodeTie_->modelMat(), dvec3(0, 215, 0)));

		CrearEntidad(fakeNodeTie_, false, nullptr);
	}
	else if (mId == 4)
	{
		auto cubo = new Cubo(200);

		CrearEntidad(cubo, false, nullptr);
	}
	else if (mId == 5)
	{
		auto esfera = new Esfera(100, 40, 80);

		esfera->setColor(dvec4(255.0 / 255, 233.0 / 255, 0.0, 1.0));
		
		esfera->setModelMat(translate(esfera->modelMat(), dvec3(200, 0, 0)));

		CrearEntidad(esfera, false, nullptr);

		auto esfera2 = new Esfera(100, 40, 80);

		Material* mat = new Material();
		mat->setGold();

		esfera2->setMaterial(mat);

		esfera2->setModelMat(translate(esfera2->modelMat(), dvec3(0, 0, 200)));

		CrearEntidad(esfera2, false, nullptr);
	}
	else if (mId == 6)
	{
		auto toro = new Toro(100, 200, 40, 80);

		CrearEntidad(toro, false, nullptr);
	}
}	
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	//borramos las texturas
	for (Texture* t : gTextures) {
		delete t; t = nullptr; 
	}
	gObjects.clear();
	gObjectsOpaque.clear();
	gObjectsTranslucent.clear();
	gTextures.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);   // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D); //activar texturas
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D); //desactivar texturas
}

void Scene::CrearEntidad(Abs_Entity* entity, bool esTrans, Texture* tex = nullptr)
{
	if (tex != nullptr) entity->setTexture(tex); //Se le asigna la textura a la entidad
	gObjects.push_back(entity);

	if (esTrans) gObjectsTranslucent.push_back(entity);
	else gObjectsOpaque.push_back(entity);
}

void Scene::cargarBMPs() //Cargar todas las imagenes .BMP
{
	//Se cargan las texturas normales
	for (std::pair<std::string, int> s : bmps) {
		Texture* tex = new Texture();
		tex->load(s.first, s.second);
		gTextures.push_back(tex);
	}
	//Excepcion para BMP de tipo fondo transparente (alpha test)
	Texture* t = new Texture();
	t->load("..\\Bmps\\grass.bmp", u8vec3(0, 0, 0), 255);
	gTextures.push_back(t);
}

void Scene::capturaPantalla(const std::string& BMP_Name)
{
	Texture* tex = new Texture();
	tex->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT);
	tex->save(BMP_Name);//se guarda la textura nombre save.bmp
	delete tex; //se borra la textura creada
}

void Scene::rota()
{
	fakeNodeTie_->setModelMat(rotate(fakeNodeTie_->modelMat(), radians(-3.0), dvec3(0, 1, 0)));
}

void Scene::orbita()
{
	fakeNodeTie_->setModelMat(rotate(fakeNodeTie_->modelMat(), radians(-3.0), dvec3(0, 0, 1)));
}

void Scene::setLights() {

	dirLight = new DirLight();
	dirLight->setPosDir({ 1.0, 1.0, 1.0 });
	dirLight->setAmb({ 0, 0, 0, 1 });
	dirLight->setDiff({ 1, 1, 1, 1 });
	dirLight->setSpec({ 0.5, 0.5, 0.5, 1 });

	posLight = new PosLight();
	posLight->setPosDir({ 300.0, 300.0, 0.0 });
	posLight->setAmb({ 0, 0, 0, 1 });
	posLight->setDiff({ 1, 1, 0, 1 });
	posLight->setSpec({ 0.5, 0.5, 0.5, 1 });

	spotLight = new SpotLight();
	spotLight->setPosDir({ 0.0, 0.0, 400.0 });
	spotLight->setSpot({ 0.0, 0.0, -1.0 }, 10, 0);
	spotLight->setAmb({ 0, 0, 0, 1 });
	spotLight->setDiff({ 1, 1, 0, 1 });
	spotLight->setSpec({ 0.5, 0.5, 0.5, 1 });
}

void Scene::uploadLights(Camera const& cam) const
{
	dirLight->upload(cam.viewMat());
	posLight->upload(cam.viewMat());
	spotLight->upload(cam.viewMat());
}

void Scene::enableDirLight()
{
	dirLight->enable();
}

void Scene::disableDirLight()
{
	dirLight->disable();
}

void Scene::enablePosLight()
{
	posLight->enable();
}

void Scene::disablePosLight()
{
	posLight->disable();
}

void Scene::enableSpotLight()
{
	spotLight->enable();
}

void Scene::disableSpotLight()
{
	spotLight->disable();
}

void Scene::enableTieLight()
{
	tieSpotlight->enable();
}

void Scene::disableTieLight()
{
	tieSpotlight->disable();
}


//Render editado para el Blending
void Scene::render(Camera const& cam) const 
{
	uploadLights(cam);
	cam.upload();

	//gObjects opacos
	for (Abs_Entity* elOpaque : gObjectsOpaque)
	{
	  elOpaque->render(cam.viewMat());
	}
	//gObjects translucidos
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (Abs_Entity* elTranslucent : gObjectsTranslucent)
	{
		elTranslucent->render(cam.viewMat());
	}
	//dejamos los valores por defecto
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void Scene::changeScene(int id)//Cambiar entre escenas
{
	free();
	resetGL();
	mId = id;
	init(id);
}