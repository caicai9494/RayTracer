////////////////////////////////////////
// MeshObject.h
////////////////////////////////////////

#ifndef CSE168_MESHOBJECT_H
#define CSE168_MESHOBJECT_H

#include <Object/Object.h>
#include <Object/Triangle.h>
#include <Material/LambertMaterial.h>
#include <Core/Matrix34.h>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////

class MeshObject:public Object {
    friend class BoxTreeObject;
public:
	MeshObject();
	~MeshObject();

	bool Intersect(const Ray &ray,Intersection &hit);

	void MakeBox(float x,float y,float z,Material *mtl=0);
	bool LoadPLY(const char *path, Material *mtl = 0);

	void Smooth();
private:
	int NumVertexes,NumTriangles;
	Vertex *Vertexes;
	Triangle *Triangles;
};

////////////////////////////////////////////////////////////////////////////////

#endif
