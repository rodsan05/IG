#pragma once
#include <glm.hpp>
#include <GL/freeglut.h>

class Light { // Abstract class
protected:
	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no v�lido
	// Atributos lum�nicos y geom�trico de la fuente de luz
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };
	// A�ade setter�s para cambiar el valor de los atributos lum�nicos
public:
	Light() {
		if (cont < GL_MAX_LIGHTS) {
			id = GL_LIGHT0 + cont;
			++cont;
			glEnable(id);
		}
	};
	virtual ~Light() { disable(); }
	void uploadL();

	// M�todo abstracto
	virtual void upload(glm::dmat4 const& modelViewMat) const = 0;

	void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };
	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };
	void setAmb(glm::fvec4 amb) { ambient = amb; uploadL(); }; //setDiff(), setSpec()
};

class DirLight : public Light { 
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
};

class PosLight : public Light {
protected:
	// Factores de atenuaci�n
	GLfloat kc = 1, kl = 0, kq = 0;
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kc, GLfloat kl, GLfloat kc);
};

