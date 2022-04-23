#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const
{
	glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const
{
	if (vVertices.size() > 0) {  // transfer data
	  // transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());
		}
		if (vTexCoords.size() > 0) {
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}

		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}

		draw();

		glDisable(GL_ALPHA_TEST);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_FAN;
	mesh->mNumVertices = (2 * np) + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(0, 0, 0);
	for (float i = 0; i < mesh->mNumVertices - 2; ++i) {
		//rd * cos(angle), rd * sin(angle), 0)
		float angle = radians(90.0 + (i * (360.0 / (mesh->mNumVertices - 2))));
		mesh->vVertices.emplace_back(re * cos(angle), re * sin(angle), h);
		i++;
		angle = radians(90.0 + (i * (360.0 / (mesh->mNumVertices - 2))));
		mesh->vVertices.emplace_back(re / 2.0 * cos(angle), re / 2.0 * sin(angle), h);
	}
	mesh->vVertices.emplace_back(mesh->vVertices[1]);

	return mesh;
}

//-------------------------------------------------------------------------
Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 4;
	double halfWidth = w; double halfHeight = h;;
	halfWidth /= 2.0;
	halfHeight /= 2.0;
	mesh->vVertices.reserve(4);
	mesh->vVertices.emplace_back(-halfWidth, halfHeight, 0);
	mesh->vVertices.emplace_back(-halfWidth, -halfHeight, 0);
	mesh->vVertices.emplace_back(halfWidth, halfHeight, 0);
	mesh->vVertices.emplace_back(halfWidth, -halfHeight, 0);

	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
	Mesh* mesh = generaRectangulo(w, h);
	mesh->vColors.reserve(4);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1);
	mesh->vColors.emplace_back(1.0, 0.0, 1.0, 1);
	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaTrianguloRGB(GLdouble rd) {
	//TRIÁNGULO BASE
	Mesh* triangle = generaPoligono(3, rd);
	triangle->mPrimitive = GL_TRIANGLES;
	// añade el vector de colores
	triangle->vColors.reserve(3);
	triangle->vColors.emplace_back(255.0, 0.0, 0.0, 1);
	triangle->vColors.emplace_back(0.0, 255.0, 0.0, 1);
	triangle->vColors.emplace_back(0.0, 0.0, 255.0, 1);
	return triangle;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->mNumVertices = numL;
	mesh->vVertices.reserve(mesh->mNumVertices);
	for (float i = 0; i < numL; ++i) {
		float angle = radians(90 + (i * (360 / mesh->mNumVertices)));
		mesh->vVertices.emplace_back(rd * cos(angle), rd * sin(angle), 0);
		//colores??
		/*mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0)*/;
	}
	return mesh;

}
//-------------------------------------------------------------------------

Mesh* Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* m = Mesh::generaRectangulo(w, h);
	m->vTexCoords.reserve(m->mNumVertices);
	m->vTexCoords.emplace_back(0, rh);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(rw, rh);
	m->vTexCoords.emplace_back(rw, 0);
	return m;
}

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = generaEstrella3D(re, np, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.5, 0.5);

	float distance = 1 / ((float)np / 2);

	for (int i = 0; i < np / 4; i++) {

		mesh->vTexCoords.emplace_back(0.5 - distance * i, 1);
	}

	for (int i = 0; i < np / 2; i++) {

		mesh->vTexCoords.emplace_back(0, 1 - distance * i);
	}

	for (int i = 0; i < np / 2; i++) {

		mesh->vTexCoords.emplace_back(distance * i, 0);
	}

	for (int i = 0; i < np / 2; i++) {

		mesh->vTexCoords.emplace_back(1, distance * i);
	}

	for (int i = 0; i < np / 4 + 1; i++) {

		mesh->vTexCoords.emplace_back(1 - distance * i, 1);
	}

	return mesh;
}

Mesh* Mesh::generaContCuboTexCor(GLdouble nl)
{
	Mesh* mesh = generaContCubo(nl);
	mesh->vTexCoords.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vTexCoords.emplace_back(i / 2, i % 2);
	}
	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaContCubo(GLdouble ld)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble halfLd = ld / 2.0;
	int x = -1;
	for (int z = 1; z > -2; z = z - 2) {
		for (int j = 0; j < 2; j++) {
			for (int y = 1; y > -2; y = y - 2) {
				mesh->vVertices.emplace_back(x * halfLd, y * halfLd, z * halfLd);
			}
			x = -x;
		}
		x = -x;
	}

	//se cierra la malla
	mesh->vVertices.emplace_back(mesh->vVertices[0]);
	mesh->vVertices.emplace_back(mesh->vVertices[1]);


	return mesh;
}

Mesh* Mesh::generaContornoRect(GLdouble xWidth, GLdouble yWidth, GLdouble height) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble halfX = xWidth / 2.0;
	GLdouble halfY = yWidth / 2.0;
	GLdouble halfHeight = height / 2.0;
	int x = -1;
	for (int z = 1; z > -2; z = z - 2) {
		for (int j = 0; j < 2; j++) {
			for (int y = 1; y > -2; y = y - 2) {
				mesh->vVertices.emplace_back(x * halfX, y * halfY, z * halfHeight);
			}
			x = -x;
		}
		x = -x;
	}

	//se cierra la malla
	mesh->vVertices.emplace_back(mesh->vVertices[0]);
	mesh->vVertices.emplace_back(mesh->vVertices[1]);
	return mesh;
}

Mesh* Mesh::generaContRectTexCor(GLdouble xWidth, GLdouble yWidth, GLdouble height)
{
	Mesh* mesh = generaContornoRect(xWidth, yWidth, height);
	mesh->vTexCoords.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vTexCoords.emplace_back(i / 2, i % 2);
	}
	return mesh;
}

Mesh* Mesh::generaAlaTIEAvanzado(GLdouble l, GLdouble h, GLdouble depth)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-l / 2, -h, 0);
	mesh->vVertices.emplace_back(l / 2, -h, 0);

	mesh->vVertices.emplace_back(-l / 2, -h / 2, depth);
	mesh->vVertices.emplace_back(l / 2, -h / 2, depth);

	mesh->vVertices.emplace_back(-l / 2, h / 2, depth);
	mesh->vVertices.emplace_back(l / 2, h / 2, depth);

	mesh->vVertices.emplace_back(-l / 2, h, 0);
	mesh->vVertices.emplace_back(l / 2, h, 0);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(0, 1.0 / 3);
	mesh->vTexCoords.emplace_back(1, 1.0 / 3);

	mesh->vTexCoords.emplace_back(0, 2.0 / 3);
	mesh->vTexCoords.emplace_back(1, 2.0 / 3);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(1, 1);

	return mesh;
}

Mesh* Mesh::generaContCaja(GLdouble lon)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
	mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);
	mesh->vVertices.emplace_back(lon / 2, lon / 2, lon / 2);
	mesh->vVertices.emplace_back(lon / 2, -lon / 2, lon / 2);

	mesh->vVertices.emplace_back(lon / 2, lon / 2, -lon / 2);
	mesh->vVertices.emplace_back(lon / 2, -lon / 2, -lon / 2);

	mesh->vVertices.emplace_back(-lon / 2, lon / 2, -lon / 2);
	mesh->vVertices.emplace_back(-lon / 2, -lon / 2, -lon / 2);

	mesh->vVertices.emplace_back(-lon / 2, lon / 2, lon / 2);
	mesh->vVertices.emplace_back(-lon / 2, -lon / 2, lon / 2);

	return mesh;
}
Mesh* Mesh::generaContCaja(GLdouble lon, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-lon / 2, h / 2, lon / 2);
	mesh->vVertices.emplace_back(-lon / 2, -h / 2, lon / 2);
	mesh->vVertices.emplace_back(lon / 2, h / 2, lon / 2);
	mesh->vVertices.emplace_back(lon / 2, -h / 2, lon / 2);

	mesh->vVertices.emplace_back(lon / 2, h / 2, -lon / 2);
	mesh->vVertices.emplace_back(lon / 2, -h / 2, -lon / 2);

	mesh->vVertices.emplace_back(-lon / 2, h / 2, -lon / 2);
	mesh->vVertices.emplace_back(-lon / 2, -h / 2, -lon / 2);

	mesh->vVertices.emplace_back(-lon / 2, h / 2, lon / 2);
	mesh->vVertices.emplace_back(-lon / 2, -h / 2, lon / 2);

	return mesh;
}
Mesh* Mesh::generaContCajaTexCor(GLdouble lon)
{
	Mesh* mesh = generaContCaja(lon);

	mesh->vTexCoords.reserve(10);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(2, 1);
	mesh->vTexCoords.emplace_back(2, 0);

	mesh->vTexCoords.emplace_back(3, 1);
	mesh->vTexCoords.emplace_back(3, 0);

	mesh->vTexCoords.emplace_back(4, 1);
	mesh->vTexCoords.emplace_back(4, 0);

	return mesh;
}
Mesh* Mesh::generaContCajaTexCor(GLdouble lon, GLdouble h)
{
	Mesh* mesh = generaContCaja(lon, h);

	mesh->vTexCoords.reserve(10);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(2, 1);
	mesh->vTexCoords.emplace_back(2, 0);

	mesh->vTexCoords.emplace_back(3, 1);
	mesh->vTexCoords.emplace_back(3, 0);

	mesh->vTexCoords.emplace_back(4, 1);
	mesh->vTexCoords.emplace_back(4, 0);

	return mesh;
}

//-------------------------------------------------------------------------

void IndexMesh::buildNormalVectors(std::vector<glm::dvec3>& normals)
{
	normals.assign(normals.capacity(), dvec3(0.0, 0.0, 0.0));

	for (int i = 0; i < mNumIndices; i+=3) 
	{
		dvec3 a = vVertices.at(vIndices[i]);
		dvec3 b = vVertices.at(vIndices[i+1]);
		dvec3 c = vVertices.at(vIndices[i+2]);

		dvec3 u1 = b - a;
		dvec3 u2 = c - a;

		dvec3 n = cross(u1, u2);
		
		for (int j = 0; j < 3; j++) 
		{
			int k = vIndices[i+j];
			normals[k] += n;
		}
	}

	for (auto& v : normals) 
	{
		v = normalize(v);
	}
}

void IndexMesh::draw() const
{
	glDrawElements(mPrimitive, mNumIndices,
		GL_UNSIGNED_INT, vIndices);
}

IndexMesh* IndexMesh::generaCuboConTapasIndexado(GLdouble lon)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 8;
	mesh->mNumIndices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	GLdouble midLon = lon / 2;

	mesh->vVertices.emplace_back(-midLon, midLon, midLon);
	mesh->vVertices.emplace_back(-midLon, -midLon, midLon);
	mesh->vVertices.emplace_back(midLon, midLon, midLon);
	mesh->vVertices.emplace_back(midLon, -midLon, midLon);

	mesh->vVertices.emplace_back(midLon, midLon, -midLon);
	mesh->vVertices.emplace_back(midLon, -midLon, -midLon);
	mesh->vVertices.emplace_back(-midLon, midLon, -midLon);
	mesh->vVertices.emplace_back(-midLon, -midLon, -midLon);

	//indices
	
	mesh->vIndices = new GLuint[] { 0,1,2, 2,1,3, 2,3,4,
						   4,3,5, 4,5,6, 6,5,7,
						   6,7,0, 0,7,1, 4,6,2,
						   2,6,0, 1,7,3, 3,7,5 };

	//COLOR
	mesh->vColors.assign(mesh->mNumVertices, dvec4(0.0, 1.0, 0.0, 1.0));

	//normales
	mesh->vNormals.reserve(mesh->mNumVertices);
	mesh->buildNormalVectors(mesh->vNormals);

	return mesh;
}
