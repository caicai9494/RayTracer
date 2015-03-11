////////////////////////////////////////
// MeshObject.h
////////////////////////////////////////

#ifndef CSE168_MESHOBJECT_H
#define CSE168_MESHOBJECT_H

#include <Object/Object.h>
#include <Object/Triangle.h>
#include <Material/LambertMaterial.h>
#include <Core/Matrix34.h>

////////////////////////////////////////////////////////////////////////////////

class MeshObject:public Object {
public:
	MeshObject();
	~MeshObject();

	bool Intersect(const Ray &ray,Intersection &hit)const;

	void MakeBox(float x,float y,float z,Material *mtl=0);

private:
	int NumVertexes,NumTriangles;
	Vertex *Vertexes;
	Triangle *Triangles;
};

////////////////////////////////////////////////////////////////////////////////

#endif
