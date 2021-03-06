////////////////////////////////////////
// Triangle.h
////////////////////////////////////////

#ifndef CSE168_TRIANGLE_H
#define CSE168_TRIANGLE_H

#include <Object/Vertex.h>
#include <Material/Material.h>
#include <Camera/Ray.h>
#include <Core/Matrix34.h>

////////////////////////////////////////////////////////////////////////////////

class Triangle {
    friend class MeshObject;
    friend class BoxTreeNode;
    friend class BoxTreeObject;
public:
	Triangle();
	void Init(Vertex *v0,Vertex *v1,Vertex *v2,Material *m)		{Vtx[0]=v0; Vtx[1]=v1; Vtx[2]=v2; Mtl=m;}

	bool Intersect(const Ray &ray, Intersection &hit) ;
	Vector3 ComputeCenter();

private:
	Vertex *Vtx[3];
	Material *Mtl;
};

////////////////////////////////////////////////////////////////////////////////

#endif
