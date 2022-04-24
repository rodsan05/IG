//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

//Cargar bmps desde x rutas
static const std::pair<std::string, int> bmps[10] = {
	{"..\\Bmps\\baldosaC.bmp", 255}, {"..\\Bmps\\baldosaF.bmp", 255 }, {"..\\Bmps\\baldosaP.bmp", 255},
	{"..\\Bmps\\container.bmp", 255}, {"..\\Bmps\\zelda.bmp", 255}, {"..\\Bmps\\noche.bmp", 150},
	{"..\\Bmps\\papelC.bmp", 255}, { "..\\Bmps\\papelE.bmp", 255}, {"..\\Bmps\\windowC.bmp", 255},
	{"..\\Bmps\\windowV.bmp", 150}
};

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init(int id_);

    void render(Camera const& cam) const;
	void changeScene(int id);
	
	void update() { for (auto elem : gObjects) elem->update(); };
	void capturaPantalla(const std::string& BMP_Name);

	void rota();
	void orbita();

protected:
	void free();
	void setGL();
	void resetGL();

	void CrearEntidad(Abs_Entity* entity, bool translucent, Texture* tex);
	void cargarBMPs();

	void sceneDirLight(Camera const& cam) const;

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gObjectsOpaque;//Entidades opacas
	std::vector<Abs_Entity*> gObjectsTranslucent;// Entidades trans
	std::vector<Texture*> gTextures;//Texturas cargadas

	CompoundEntity* fakeNodeTie_;
	
	int mId = 0; //id scena
};
#endif //_H_Scene_H_

