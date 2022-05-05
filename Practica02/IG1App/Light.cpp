#include "Light.h"
#include <gtc/type_ptr.hpp>

void Light::uploadL()
{
	// Transfiere las características de la luz a la GPU
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}

void DirLight::upload(glm::dmat4 const& modelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	uploadL();
}

void DirLight::setPosDir(glm::fvec3 dir)
{
	posDir = glm::fvec4(dir, 0.0);
}
